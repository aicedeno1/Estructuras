#include <graphics.h>
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 8;
const int BASE_CELL_SIZE = 40;
const int MARGIN = 30;
const int SOLUTIONS_PER_ROW = 3;

struct Solucion {
    vector<int> tablero;
};

vector<Solucion> soluciones;

// Función para determinar número de soluciones por página basado en N
int getSolucionesPorPagina(int n) {
    if (n >= 7) {
        return 6;  // 2 filas de 3 para tableros grandes
    }
    return 9;  // 3 filas de 3 para tableros pequeños
}

// Función para calcular el tamaño óptimo de celda basado en N
int calcularTamanioCelda(int n) {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN) - 100;
    int maxBoardWidth = (screenWidth - (MARGIN * (SOLUTIONS_PER_ROW + 1))) / SOLUTIONS_PER_ROW;
    return min(BASE_CELL_SIZE, maxBoardWidth / n);
}

// Función para dibujar un tablero individual
void dibujarTablero(int n, int startX, int startY, const vector<int>& tablero, int cellSize) {
    setcolor(WHITE);
    // Dibujar cuadrícula
    for(int i = 0; i <= n; i++) {
        line(startX, startY + i * cellSize, 
             startX + n * cellSize, startY + i * cellSize);
        line(startX + i * cellSize, startY, 
             startX + i * cellSize, startY + n * cellSize);
    }
    
    // Colorear casillas y dibujar reinas
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            // Colorear casillas alternadas
            if((i + j) % 2 == 0) {
                setfillstyle(SOLID_FILL, DARKGRAY);
                bar(startX + j * cellSize + 1,
                    startY + i * cellSize + 1,
                    startX + (j + 1) * cellSize - 1,
                    startY + (i + 1) * cellSize - 1);
            }
            
            // Dibujar reina si corresponde
            if(tablero[j] == i) {
                setcolor(YELLOW);
                setfillstyle(SOLID_FILL, YELLOW);
                fillellipse(startX + j * cellSize + cellSize/2,
                          startY + i * cellSize + cellSize/2,
                          cellSize/3, cellSize/3);
                
                // Agregar corona si hay espacio suficiente
                if(cellSize >= 30) {
                    setcolor(RED);
                    line(startX + j * cellSize + cellSize/3,
                         startY + i * cellSize + cellSize/3,
                         startX + j * cellSize + 2*cellSize/3,
                         startY + i * cellSize + cellSize/3);
                }
            }
        }
    }
}

bool esSeguro(const vector<int>& tablero, int fila, int col, int n) {
    for(int i = 0; i < col; i++) {
        if(tablero[i] == fila || 
           abs(tablero[i] - fila) == abs(i - col)) {
            return false;
        }
    }
    return true;
}

void encontrarSoluciones(vector<int>& tablero, int col, int n) {
    if(col >= n) {
        Solucion sol;
        sol.tablero = tablero;
        soluciones.push_back(sol);
        return;
    }
    
    for(int i = 0; i < n; i++) {
        if(esSeguro(tablero, i, col, n)) {
            tablero[col] = i;
            encontrarSoluciones(tablero, col + 1, n);
        }
    }
}

// Función para dibujar todas las soluciones
void dibujarSoluciones(int n, int cellSize) {
    cleardevice();
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    
    int boardSize = n * cellSize;
    int spacingX = boardSize + MARGIN * 2;
    int spacingY = boardSize + MARGIN * 2;
    
    int solucionesPorPagina = getSolucionesPorPagina(n);
    int filasPorPagina = solucionesPorPagina / SOLUTIONS_PER_ROW;
    int currentPage = 0;
    int totalPaginas = (soluciones.size() + solucionesPorPagina - 1) / solucionesPorPagina;
    
    while(true) {
        cleardevice();
        int startIndex = currentPage * solucionesPorPagina;
        int endIndex = min(startIndex + solucionesPorPagina, (int)soluciones.size());
        
        for(int i = startIndex; i < endIndex; i++) {
            int localIndex = i - startIndex;
            int row = localIndex / SOLUTIONS_PER_ROW;
            int col = localIndex % SOLUTIONS_PER_ROW;
            
            int startX = MARGIN + col * spacingX;
            int startY = MARGIN + row * spacingY;
            
            // Dibujar número de solución
            char numText[20];
            sprintf(numText, "Solucion %d", i + 1);
            outtextxy(startX, startY - 15, numText);
            
            dibujarTablero(n, startX, startY, soluciones[i].tablero, cellSize);
        }
        
        // Mostrar información de navegación
        char pageText[50];
        sprintf(pageText, "Pagina %d/%d - Total soluciones: %d", 
                currentPage + 1, totalPaginas, (int)soluciones.size());
        outtextxy(MARGIN, getmaxy() - 30, pageText);
        
        if(totalPaginas > 1) {
            outtextxy(MARGIN, getmaxy() - 15, "Use <- -> para navegar, ESC para salir");
        } else {
            outtextxy(MARGIN, getmaxy() - 15, "Presione ESC para salir");
        }
        
        // Esperar input
        char key = getch();
        if(key == 27) break; // ESC
        if(key == 0) { // Teclas especiales
            key = getch();
            if(key == 75 && currentPage > 0) currentPage--; // Flecha izquierda
            if(key == 77 && currentPage < totalPaginas - 1) currentPage++; // Flecha derecha
        }
    }
}

int main() {
    int n;
    cout << "Ingrese el tamaño del tablero (maximo 8): ";
    cin >> n;
    
    if(n < 1 || n > MAX_N) {
        cout << "Tamaño invalido. Debe ser entre 1 y 8." << endl;
        return 1;
    }
    
    // Encontrar todas las soluciones
    vector<int> tablero(n, -1);
    encontrarSoluciones(tablero, 0, n);
    
    // Calcular tamaño óptimo de celda
    int cellSize = calcularTamanioCelda(n);
    
    // Calcular dimensiones de la ventana basadas en el número de filas por página
    int filasPorPagina = (n >= 7) ? 2 : 3;
    int windowWidth = (n * cellSize + MARGIN * 2) * SOLUTIONS_PER_ROW + MARGIN;
    int windowHeight = (n * cellSize + MARGIN * 2) * filasPorPagina + MARGIN * 2;
    
    // Inicializar modo gráfico
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    initwindow(windowWidth, windowHeight);
    
    dibujarSoluciones(n, cellSize);
    
    closegraph();
    return 0;
}