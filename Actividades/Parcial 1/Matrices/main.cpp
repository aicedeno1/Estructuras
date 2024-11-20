#include <iostream>
#include "Matriz.h"

using namespace std;

int main() {
    // Crear una matriz de tamaño 3x3
    Matriz m(3);

    // Asignar valores a las matrices
    int** matriz1 = m.getMatriz1();
    int** matriz2 = m.getMatriz2();

    // Rellenar las matrices con valores (puedes modificar este código según lo que necesites)
    cout << "Ingrese los elementos para la Matriz 1 (3x3): " << endl;
    for (int i = 0; i < m.getDim(); ++i) {
        for (int j = 0; j < m.getDim(); ++j) {
            cin >> matriz1[i][j];
        }
    }

    cout << "Ingrese los elementos para la Matriz 2 (3x3): " << endl;
    for (int i = 0; i < m.getDim(); ++i) {
        for (int j = 0; j < m.getDim(); ++j) {
            cin >> matriz2[i][j];
        }
    }

    // Sumar las matrices
    m.sumarMatrices();

    // Obtener la matriz resultado
    int** matrizResultado = m.getMatrizR();

    // Imprimir las matrices
    cout << "\nMatriz 1:" << endl;
    m.imprimirMatriz(matriz1);

    cout << "\nMatriz 2:" << endl;
    m.imprimirMatriz(matriz2);

    cout << "\nMatriz Resultado (Suma de Matrices):" << endl;
    m.imprimirMatriz(matrizResultado);

    // Liberar las matrices
    m.liberarMatriz(matriz1);
    m.liberarMatriz(matriz2);
    m.liberarMatriz(matrizResultado);

    return 0;
}
