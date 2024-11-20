#include <iostream>
#include "Matriz.h"

using namespace std;

int main() {
    Matriz m(3);  

    int** matriz1 = m.getMatriz1();
    int** matriz2 = m.getMatriz2();

    // Rellenar las matrices con valores
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

    // Sumar las matrices de forma recursiva
    m.sumarMatricesConRecursion();

    // Obtener la matriz resultado
    int** matrizResultado = m.getMatrizR();

    // Imprimir las matrices
    cout << "\nMatriz 1:" << endl;
    m.imprimirMatriz(matriz1);

    cout << "\nMatriz 2:" << endl;
    m.imprimirMatriz(matriz2);

    cout << "\nMatriz Resultado (Suma de Matrices con Recursion):" << endl;
    m.imprimirMatriz(matrizResultado);

    return 0;
}
