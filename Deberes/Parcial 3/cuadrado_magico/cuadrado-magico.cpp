#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <string>
#include <sstream>
#include <cstring> // Para strcpy

using namespace std;

// Función para generar un cuadrado mágico de tamaño impar
void generarCuadradoMagico(int** cuadrado, int n) {
    // Inicializar todas las celdas con 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cuadrado[i][j] = 0;
        }
    }

    // Posición inicial (primera fila, columna central)
    int i = 0;
    int j = n / 2;
    
    // Llenar el cuadrado
    for (int num = 1; num <= n * n; num++) {
        cuadrado[i][j] = num;
        
        // Calcular la nueva posición (diagonal arriba-derecha)
        int nuevaI = (i - 1 + n) % n;
        int nuevaJ = (j + 1) % n;
        
        // Si la celda ya está ocupada, ir a la celda debajo
        if (cuadrado[nuevaI][nuevaJ] != 0) {
            i = (i + 1) % n;
        } else {
            i = nuevaI;
            j = nuevaJ;
        }
    }
}

// Función auxiliar para convertir string a char*
char* stringToChar(const string& str) {
    char* charArray = new char[str.length() + 1];
    strcpy(charArray, str.c_str());
    return charArray;
}

// Función para dibujar el cuadrado mágico gráficamente
void dibujarCuadradoMagico(int** cuadrado, int n) {
    // Obtener la resolución máxima de la pantalla
    int maxX = getmaxx();
    int maxY = getmaxy();
    
    // Calcular el tamaño de cada celda
    int tamCelda = min(maxX, maxY) / (n + 2); // Dejar un margen
    
    // Calcular la posición inicial (centrado)
    int inicioX = (maxX - n * tamCelda) / 2;
    int inicioY = (maxY - n * tamCelda) / 2;
    
    // Configurar color y estilo
    setcolor(WHITE);
    setbkcolor(BLACK);
    cleardevice();
    
    // Dibujar el título
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    string tituloStr = "Cuadrado Magico de orden " + to_string(n);
    char* titulo = stringToChar(tituloStr);
    outtextxy((maxX - textwidth(titulo)) / 2, inicioY - tamCelda, titulo);
    delete[] titulo;
    
    // Calcular la constante mágica
    int constMagica = n * (n * n + 1) / 2;
    string infoConstanteStr = "Constante magica: " + to_string(constMagica);
    char* infoConstante = stringToChar(infoConstanteStr);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy((maxX - textwidth(infoConstante)) / 2, inicioY - tamCelda / 2, infoConstante);
    delete[] infoConstante;
    
    // Dibujar la cuadrícula y los números
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Calcular coordenadas de la celda
            int x = inicioX + j * tamCelda;
            int y = inicioY + i * tamCelda;
            
            // Dibujar el rectángulo de la celda
            rectangle(x, y, x + tamCelda, y + tamCelda);
            
            // Convertir el número a texto
            stringstream ss;
            ss << cuadrado[i][j];
            string numeroStr = ss.str();
            char* numero = stringToChar(numeroStr);
            
            // Calcular la posición del texto (centrado en la celda)
            int textX = x + (tamCelda - textwidth(numero)) / 2;
            int textY = y + (tamCelda - textheight(numero)) / 2;
            
            // Mostrar el número
            outtextxy(textX, textY, numero);
            delete[] numero;
        }
    }
    
    // Mostrar instrucciones
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(10, maxY - 30, (char*)"Presione cualquier tecla para salir...");
}

int main() {
    int n;
    
    // Pedir el tamaño del cuadrado mágico
    cout << "Ingrese el tamano del cuadrado magico (debe ser impar): ";
    cin >> n;
    
    // Validar que el tamaño sea impar
    if (n % 2 == 0 || n < 3) {
        cout << "Error: El tamano debe ser un numero impar mayor o igual a 3." << endl;
        cout << "Presione cualquier tecla para salir...";
        getch();
        return 1;
    }
    
    // Asignar memoria para el cuadrado mágico
    int** cuadrado = new int*[n];
    for (int i = 0; i < n; i++) {
        cuadrado[i] = new int[n];
    }
    
    // Generar el cuadrado mágico
    generarCuadradoMagico(cuadrado, n);
    
    // Inicializar el modo gráfico
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, (char*)"");
    
    // Dibujar el cuadrado mágico
    dibujarCuadradoMagico(cuadrado, n);
    
    // Esperar a que el usuario presione una tecla
    getch();
    
    // Cerrar el modo gráfico
    closegraph();
    
    // Liberar la memoria
    for (int i = 0; i < n; i++) {
        delete[] cuadrado[i];
    }
    delete[] cuadrado;
    
    return 0;
}