#include <graphics.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_N = 8;
const int BASE_CELL_SIZE = 60;
const int MARGIN = 30;

// Estructura para representar una posición
struct Position
{
    int row;
    int col;
    Position(int r, int c) : row(r), col(c) {}
};

// Variables globales
vector<Position> possibleMoves;
Position *knightPos = nullptr;
ofstream logFile;

// Función para dibujar el tablero en modo texto
void dibujarTableroTexto(int n, ofstream &file)
{
    file << "\nEstado actual del tablero:\n";
    file << "   ";
    // Imprimir números de columna
    for (int i = 0; i < n; i++)
    {
        file << setw(3) << i;
    }
    file << "\n";

    // Imprimir línea superior
    file << "  +";
    for (int i = 0; i < n; i++)
    {
        file << "---";
    }
    file << "+\n";

    // Imprimir contenido del tablero
    for (int i = 0; i < n; i++)
    {
        file << setw(2) << i << "|"; // Número de fila
        for (int j = 0; j < n; j++)
        {
            char celda = '.'; // Celda vacía

            // Verificar si hay un caballo en esta posición
            if (knightPos && knightPos->row == i && knightPos->col == j)
            {
                celda = 'N'; // 'N' por "Knight"
            }
            else
            {
                // Verificar si es un movimiento posible
                for (const Position &move : possibleMoves)
                {
                    if (move.row == i && move.col == j)
                    {
                        celda = '*'; // Movimiento posible
                        break;
                    }
                }
            }
            file << " " << celda << " ";
        }
        file << "|\n";
    }

    // Imprimir línea inferior
    file << "  +";
    for (int i = 0; i < n; i++)
    {
        file << "---";
    }
    file << "+\n\n";

    // Imprimir leyenda
    file << "Leyenda:\n";
    file << "N = Posición actual del caballo\n";
    file << "* = Movimiento posible\n";
    file << ". = Celda vacía\n\n";
}

// Función para calcular el tamaño óptimo de celda basado en N
int calcularTamanioCelda(int n)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN) - 100;
    return min(BASE_CELL_SIZE, (screenWidth - 2 * MARGIN) / n);
}

// Función para verificar si una posición está dentro del tablero
bool esValida(int row, int col, int n)
{
    return row >= 0 && row < n && col >= 0 && col < n;
}

// Función para calcular los movimientos posibles del caballo
vector<Position> calcularMovimientos(int row, int col, int n)
{
    vector<Position> moves;
    // Los 8 posibles movimientos del caballo
    int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 8; i++)
    {
        int newRow = row + dr[i];
        int newCol = col + dc[i];
        if (esValida(newRow, newCol, n))
        {
            moves.push_back(Position(newRow, newCol));
        }
    }
    return moves;
}

// Función para registrar movimiento en el archivo
void registrarMovimiento(int fromRow, int fromCol, int toRow, int toCol, int n)
{
    logFile << "\nMovimiento desde (" << fromRow << "," << fromCol << ") ";
    logFile << "hasta (" << toRow << "," << toCol << ")\n";
    dibujarTableroTexto(n, logFile);
}

// Función para dibujar el tablero y el caballo en modo gráfico
void dibujarTablero(int n, int cellSize)
{
    cleardevice();
    setcolor(WHITE);

    // Dibujar cuadrícula
    for (int i = 0; i <= n; i++)
    {
        line(MARGIN, MARGIN + i * cellSize,
             MARGIN + n * cellSize, MARGIN + i * cellSize);
        line(MARGIN + i * cellSize, MARGIN,
             MARGIN + i * cellSize, MARGIN + n * cellSize);
    }

    // Colorear casillas
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i + j) % 2 == 0)
            {
                setfillstyle(SOLID_FILL, DARKGRAY);
                bar(MARGIN + j * cellSize + 1,
                    MARGIN + i * cellSize + 1,
                    MARGIN + (j + 1) * cellSize - 1,
                    MARGIN + (i + 1) * cellSize - 1);
            }
        }
    }

    // Dibujar movimientos posibles
    if (knightPos != nullptr)
    {
        possibleMoves = calcularMovimientos(knightPos->row, knightPos->col, n);
        setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
        for (const Position &move : possibleMoves)
        {
            circle(MARGIN + move.col * cellSize + cellSize / 2,
                   MARGIN + move.row * cellSize + cellSize / 2,
                   cellSize / 6);
        }

        // Dibujar caballo
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        fillellipse(MARGIN + knightPos->col * cellSize + cellSize / 2,
                    MARGIN + knightPos->row * cellSize + cellSize / 2,
                    cellSize / 3, cellSize / 3);

        // Dibujar símbolo del caballo
        setcolor(RED);
        line(MARGIN + knightPos->col * cellSize + cellSize / 3,
             MARGIN + knightPos->row * cellSize + cellSize / 3,
             MARGIN + knightPos->col * cellSize + 2 * cellSize / 3,
             MARGIN + knightPos->row * cellSize + cellSize / 3);
    }

    // Instrucciones
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    char msg1[] = "Haga clic para colocar el caballo";
    char msg2[] = "Haga clic en un punto verde para mover el caballo";
    char msg3[] = "Presione ESC para salir";

    if (knightPos == nullptr)
    {
        outtextxy(MARGIN, getmaxy() - 30, msg1);
    }
    else
    {
        outtextxy(MARGIN, getmaxy() - 30, msg2);
        outtextxy(MARGIN, getmaxy() - 15, msg3);
    }
}

int main()
{
    int n;
    cout << "Ingrese el tamaño del tablero (maximo 8): ";
    cin >> n;

    if (n < 1 || n > MAX_N)
    {
        cout << "Tamaño invalido. Debe ser entre 1 y 8." << endl;
        return 1;
    }

    // Abrir archivo de registro
    logFile.open("movimientos_caballo.txt");
    if (!logFile.is_open())
    {
        cout << "Error al abrir el archivo de registro." << endl;
        return 1;
    }

    // Escribir encabezado en el archivo
    logFile << "Registro de movimientos del caballo\n";
    logFile << "Tamaño del tablero: " << n << "x" << n << "\n";

    // Calcular tamaño óptimo de celda
    int cellSize = calcularTamanioCelda(n);

    // Inicializar modo gráfico
    int gd = DETECT, gm;
    char driverPath[] = "";
    initgraph(&gd, &gm, driverPath);
    int windowWidth = n * cellSize + 2 * MARGIN;
    int windowHeight = n * cellSize + 3 * MARGIN;
    initwindow(windowWidth, windowHeight);

    // Loop principal
    bool running = true;
    while (running)
    {
        dibujarTablero(n, cellSize);

        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            // Convertir coordenadas del mouse a posición en el tablero
            int col = (x - MARGIN) / cellSize;
            int row = (y - MARGIN) / cellSize;

            if (esValida(row, col, n))
            {
                if (knightPos == nullptr)
                {
                    // Primera colocación del caballo
                    knightPos = new Position(row, col);
                    logFile << "\nCaballo colocado en posición inicial (" << row << "," << col << ")\n";
                    possibleMoves = calcularMovimientos(row, col, n);
                    dibujarTableroTexto(n, logFile);
                }
                else
                {
                    // Verificar si el movimiento es válido
                    bool movimientoValido = false;
                    for (const Position &move : possibleMoves)
                    {
                        if (move.row == row && move.col == col)
                        {
                            movimientoValido = true;
                            registrarMovimiento(knightPos->row, knightPos->col, row, col, n);
                            knightPos->row = row;
                            knightPos->col = col;
                            possibleMoves = calcularMovimientos(row, col, n);
                            break;
                        }
                    }
                }
            }
        }

        if (kbhit() && getch() == 27)
        { // ESC
            running = false;
        }

        delay(50);
    }

    // Limpieza
    if (knightPos != nullptr)
    {
        delete knightPos;
    }
    logFile.close();
    closegraph();
    return 0;
}