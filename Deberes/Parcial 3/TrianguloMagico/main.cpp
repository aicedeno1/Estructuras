
#include <graphics.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

class TrianguloMagico {
private:
    struct Solucion {
        vector<int> esquinas;
        vector<int> lado1;
        vector<int> lado2;
        vector<int> lado3;
        bool encontrada;
    };

    int orden;
    int sumaObjetivo;
    Solucion solucion;

    // Método para validar y capturar entrada del usuario
    static string capturarEntrada() {
        string entrada;
        char tecla;
        while (true) {
            tecla = _getch();
            if ((tecla >= '0' && tecla <= '9') || tecla == '\b' || tecla == '\r') {
                if (tecla == '\r') {
                    cout << endl;
                    break;
                } else if (tecla == '\b') {
                    if (!entrada.empty()) {
                        cout << "\b \b";
                        entrada.pop_back();
                    }
                } else if (entrada.size() < 2) {
                    cout << tecla;
                    entrada.push_back(tecla);
                }
            } else {
                cout << "\a"; // Sonido para entrada inválida
            }
        }
        return entrada;
    }

    // Método para obtener una tecla válida
    static char obtenerEntradaValidada() {
        char tecla;
        while (true) {
            tecla = _getch();
            if ((tecla >= '0' && tecla <= '9') || tecla == '\b' || tecla == '\r' || tecla == 'x' || tecla == 'X') {
                return tecla;
            } else {
                cout << "\a"; // Sonido para entrada inválida
            }
        }
    }

    // Método auxiliar para el backtracking
    static bool backtrackCombination(int needed, int count, int start, vector<bool>& used,
                       vector<int>& resultado, int maxDigit) {
        if (count == 0)
            return (needed == 0);
        if (start > maxDigit)
            return false;
        for (int dig = start; dig <= maxDigit; dig++) {
            if (!used[dig] && dig <= needed) {
                used[dig] = true;
                resultado.push_back(dig);
                if (backtrackCombination(needed - dig, count - 1, dig + 1, used, resultado, maxDigit))
                    return true;
                used[dig] = false;
                resultado.pop_back();
            }
        }
        return false;
    }

    // Método para dibujar un nodo en el gráfico
    void dibujarNodo(int x, int y, int radio, int numero) const {
        // Colores más vibrantes
        setcolor(YELLOW);
        circle(x, y, radio);
        setfillstyle(SOLID_FILL, LIGHTGREEN);
        floodfill(x, y, YELLOW);
        
        // Formato para el número
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        
        char buffer[10];
        sprintf(buffer, "%d", numero);
        outtextxy(x, y, buffer);
    }

    // Método para generar solución
    Solucion generarSolucion() {
        Solucion sol;
        sol.encontrada = false;

        if(orden < 3 || orden > 10) {
            cout << "Orden no soportado. Debe estar entre 3 y 10." << endl;
            return sol;
        }

        // Determinamos el rango de dígitos:
        int maxDigit = 3 * (orden - 1);
        // Suma total de los dígitos del 1 a maxDigit:
        int T = maxDigit * (maxDigit + 1) / 2;
        // La suma de las 3 esquinas debe ser:
        int sumaEsquinas = 3 * sumaObjetivo - T;
        
        // Verificamos que la suma de esquinas esté en el rango posible:
        int minEsquinas = 1 + 2 + 3;  // 6
        int maxEsquinas = (maxDigit) + (maxDigit - 1) + (maxDigit - 2); // los 3 mayores
        if (sumaEsquinas < minEsquinas || sumaEsquinas > maxEsquinas) {
            return sol;
        }
        
        // Recorrer combinaciones para las esquinas (a, b, c) de 1 a maxDigit:
        for (int a = 1; a <= maxDigit; a++) {
            for (int b = a + 1; b <= maxDigit; b++) {
                for (int c = b + 1; c <= maxDigit; c++) {
                    if (a + b + c == sumaEsquinas) {
                        // Usamos un vector<bool> para llevar el control de los dígitos ya usados.
                        vector<bool> used(maxDigit + 1, false);
                        used[a] = used[b] = used[c] = true;
                        
                        // Para cada lado, se deben llenar (orden - 2) nodos intermedios.
                        int cant = orden - 2;
                        // Lado 1: entre esquinas a y b
                        int resto1 = sumaObjetivo - (a + b);
                        // Lado 2: entre esquinas b y c
                        int resto2 = sumaObjetivo - (b + c);
                        // Lado 3: entre esquinas c y a
                        int resto3 = sumaObjetivo - (c + a);
                        
                        vector<int> lado1, lado2, lado3;
                        
                        // Se busca una combinación para cada lado sin reutilizar dígitos.
                        if (!backtrackCombination(resto1, cant, 1, used, lado1, maxDigit))
                            continue;
                        if (!backtrackCombination(resto2, cant, 1, used, lado2, maxDigit))
                            continue;
                        if (!backtrackCombination(resto3, cant, 1, used, lado3, maxDigit))
                            continue;
                        
                        sol.esquinas = {a, b, c};
                        sol.lado1 = lado1;
                        sol.lado2 = lado2;
                        sol.lado3 = lado3;
                        sol.encontrada = true;
                        return sol;
                    }
                }
            }
        }
        return sol;
    }

    // Método para dibujar el triángulo mágico
    void dibujar() const {
        int gd = DETECT, gm;
        char initPath[] = "";
        initgraph(&gd, &gm, initPath);
        setbkcolor(BLACK);
        cleardevice();
        
        // Coordenadas de los vértices (con ligeros ajustes para centrar mejor)
        int x1 = 320, y1 = 80;  // Vértice superior (centrado)
        int x2 = 100, y2 = 420; // Vértice inferior izquierdo
        int x3 = 540, y3 = 420; // Vértice inferior derecho
        int radio = 22;         // Radio ligeramente más grande
        
        // Esquinas
        int A = solucion.esquinas[0];
        int B = solucion.esquinas[1];
        int C = solucion.esquinas[2];
        
        // Dibujar fondo decorativo
        setcolor(LIGHTRED);
        setfillstyle(SOLID_FILL, BLUE);
        fillellipse(320, 240, 250, 200);
        
        // Dibujar líneas del triángulo con un efecto de degradado
        for (int i = 0; i < 5; i++) {
            setcolor(RGB(255 - i*30, 0, 255 - i*20)); // Degradado de púrpura a azul
            line(x1 - i, y1 - i, x2 - i, y2 + i);
            line(x2 - i, y2 + i, x3 + i, y3 + i);
            line(x3 + i, y3 + i, x1 - i, y1 - i);
        }
        
        dibujarNodo(x1, y1, radio, A);
        dibujarNodo(x2, y2, radio, B);
        dibujarNodo(x3, y3, radio, C);
        
        int numIntermedios = orden - 2;
        auto dibujarLado = [&](int xIni, int yIni, int xFin, int yFin, const vector<int> &valores) {
            for (int i = 0; i < (int)valores.size(); i++) {
                float t = (float)(i + 1) / (numIntermedios + 1);
                int x = xIni + t * (xFin - xIni);
                int y = yIni + t * (yFin - yIni);
                dibujarNodo(x, y, radio, valores[i]);
            }
        };
        
        dibujarLado(x1, y1, x2, y2, solucion.lado1);
        dibujarLado(x2, y2, x3, y3, solucion.lado2);
        dibujarLado(x3, y3, x1, y1, solucion.lado3);
        
        // Título y mensajes con estilo mejorado
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(WHITE);
        
        char titulo[] = "TRIANGULO MAGICO";
        outtextxy(320 - textwidth(titulo)/2, 20, titulo);
        
        char mensaje[50];
        sprintf(mensaje, "Suma por lado: %d", sumaObjetivo);
        outtextxy(320 - textwidth(mensaje)/2, 50, mensaje);
        
        // Instrucción adicional
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        char instruccion[] = "Presione cualquier tecla para continuar...";
        outtextxy(320 - textwidth(instruccion)/2, 450, instruccion);
        
        getch();
        closegraph();
    }

public:
    // Constructor
    TrianguloMagico(int _orden) : orden(_orden) {
        // Calcular rango de valores posibles para la suma objetivo
        int maxDigit = 3 * (orden - 1);
        int T = maxDigit * (maxDigit + 1) / 2;
        
        int minEsquinas = 1 + 2 + 3;  // 6
        int maxEsquinas = maxDigit + (maxDigit - 1) + (maxDigit - 2);
        
        int minS = (T + minEsquinas) / 3;
        int maxS = (T + maxEsquinas) / 3;
        
        // Seleccionar aleatoriamente la suma objetivo dentro del rango permitido
        sumaObjetivo = rand() % (maxS - minS + 1) + minS;
        
        // Generar la solución
        solucion = generarSolucion();
    }
    
    // Método para mostrar la solución y dibujar el triángulo
    bool mostrarSolucion() {
        cout << "La suma objetivo para cada lado del triangulo magico es: " << sumaObjetivo << endl;
        
        if (!solucion.encontrada) {
            cout << "No se encontro una solucion sin repetir numeros para esos datos." << endl;
            return false;
        } else {
            cout << "Solución encontrada. Mostrando gráficamente..." << endl;
            dibujar();
            return true;
        }
    }
    
    // Método principal para ejecutar la aplicación
    static void ejecutar() {
        // Inicializar la semilla para números aleatorios
        srand(time(0));
        
        cout << "====================================================" << endl;
        cout << "              TRIANGULO MAGICO                      " << endl;
        cout << "====================================================" << endl;
        
        while (true) {
            int orden;
            cout << "Nivel del triangulo magico (3 a 10): ";
            string entrada = capturarEntrada();
            try {
                orden = stoi(entrada);
            } catch (invalid_argument&) {
                cout << "Entrada no valida. Debe ser un numero entre 3 y 10." << endl;
                continue;
            }
            
            if (orden < 3 || orden > 10) {
                cout << "Nivel no soportado. Debe estar entre 3 y 10." << endl;
                continue;
            }
            
            TrianguloMagico triangulo(orden);
            triangulo.mostrarSolucion();
            
            cout << "Presione 'x' para salir o cualquier otra tecla para continuar..." << endl;
            char opcion = obtenerEntradaValidada();
            if (opcion == 'x' || opcion == 'X') {
                break;
            }
            system("cls"); // Limpiar pantalla
        }
    }
};

int main() {
    TrianguloMagico::ejecutar();
    return 0;
}