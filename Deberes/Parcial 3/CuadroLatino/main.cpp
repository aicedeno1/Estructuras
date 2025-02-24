#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <conio.h>
#include <graphics.h>
#include <windows.h>

class CuadroLatino {
private:
    int n;
    std::vector<std::vector<int>> matriz;
    
    // Métodos de validación
    static void validarTamano(int tamano) {
        if (tamano <= 0 || tamano > 14) {
            throw std::invalid_argument("El número debe estar entre 1 y 14.");
        }
    }
    
    static std::string leerEntrada() {
        std::string input;
        char ch;
        while ((ch = _getch()) != '\r') { // Leer hasta presionar Enter
            // Acepta dígitos del 1 al 14 y la letra 'X' o 'x'
            if ((isdigit(ch) && (input.empty() || (input.size() == 1 && input[0] == '1' && ch <= '4'))) || 
                 ch == 'X' || ch == 'x') {
                std::cout << ch;
                input += ch;
            } else if (ch == '\b' && !input.empty()) { // Permitir backspace
                std::cout << "\b \b";
                input.pop_back();
            }
        }
        std::cout << std::endl;
        return input;
    }

public:
    // Constructor
    CuadroLatino(int tamano) : n(tamano) {
        try {
            validarTamano(tamano);
            matriz.resize(n, std::vector<int>(n, 0));
        } catch (const std::exception& e) {
            throw std::runtime_error("Error al inicializar la matriz: " + std::string(e.what()));
        }
    }
    
    // Genera el cuadro latino
    void generar() {
        try {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    matriz[i][j] = ((i + j) % n) + 1;
        } catch (const std::exception& e) {
            throw std::runtime_error("Error al generar el cuadro latino: " + std::string(e.what()));
        }
    }
    
    // Muestra el cuadro en consola
    void mostrarEnConsola() const {
        std::cout << "Cuadro Latino generado:\n";
        for (const auto& fila : matriz) {
            for (int num : fila) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }
    
    // Dibuja el cuadro con gráficos
    void dibujar() const {
        try {
            int cellSize = 50;  // Tamaño de celdas
            int padding = 50;   // Espaciado interno
            int width = n * cellSize + 2 * padding;
            int height = n * cellSize + 2 * padding + 50; // Espacio extra para el título
            
            // Inicializar ventana con el tamaño adecuado
            initwindow(width, height, "Cuadro Latino");

            // Fondo blanco
            setbkcolor(WHITE);
            cleardevice();

            // Dibujar título centrado
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
            setcolor(BLACK);
            outtextxy(width / 2, 20, "Cuadro Latino");

            int startX = padding;
            int startY = padding + 30; // Ajuste por el título

            // Dibujar la matriz con colores diferenciados
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int x1 = startX + j * cellSize;
                    int y1 = startY + i * cellSize;
                    int x2 = x1 + cellSize;
                    int y2 = y1 + cellSize;

                    // Alternar colores para mejor visibilidad
                    int color = (i + j) % 2 == 0 ? LIGHTCYAN : LIGHTGRAY;
                    setfillstyle(SOLID_FILL, color);
                    bar(x1, y1, x2, y2);

                    // Bordes negros para mejor contraste
                    setcolor(BLACK);
                    rectangle(x1, y1, x2, y2);

                    // Centrar los números sin fondo, solo color fuerte
                    char num[2];
                    sprintf(num, "%d", matriz[i][j]);

                    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
                    setcolor(BLUE); // Números azules para alto contraste
                    settextjustify(CENTER_TEXT, CENTER_TEXT);
                    outtextxy(x1 + cellSize / 2, y1 + cellSize / 2, num);
                }
            }

            getch(); // Esperar tecla para cerrar
            closegraph();
        } catch (const std::exception& e) {
            throw std::runtime_error("Error al dibujar el cuadro latino: " + std::string(e.what()));
        }
    }
    
    // Método para ejecutar el programa completo
    static void ejecutar() {
        // Establecer la configuración regional a UTF-8
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        while (true) {
            std::cout << "=============================\n\tCuadro Latino\n=============================\n";
            std::cout << "Ingrese el tamaño del cuadro latino (1-14) o 'X' para salir: ";
            
            std::string input = leerEntrada();

            if (input == "X" || input == "x") {
                std::cout << "Saliendo del programa." << std::endl;
                break;
            }

            try {
                int tamano = std::stoi(input);
                CuadroLatino cuadro(tamano);
                cuadro.generar();
                cuadro.mostrarEnConsola();
                cuadro.dibujar();

                // Limpiar la consola después de cada gráfico
                system("cls");
                
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
};

// Función principal
int main() {
    CuadroLatino::ejecutar();
    return 0;
}