#include <iostream>
#include "Matriz.h"
#include "Validaciones.h"

using namespace std;

int main() {
    Matriz m(3);  
    Validaciones val;

    int** matriz1 = m.getMatriz1();
    int** matriz2 = m.getMatriz2();

    
    cout << "Ingrese los elementos para la Matriz 1 (3x3): " << endl;
    for (int i = 0; i < m.getDim(); ++i) {
        for (int j = 0; j < m.getDim(); ++j) {
            matriz1[i][j] = val.ingresarEntero("Ingrese un numero entero: ");
        }
    }

    cout << "Ingrese los elementos para la Matriz 2 (3x3): " << endl;
    for (int i = 0; i < m.getDim(); ++i) {
        for (int j = 0; j < m.getDim(); ++j) {
            matriz2[i][j] = val.ingresarEntero("Ingrese un numero entero: ");
        }
    }

    
    m.sumarMatricesConRecursion();

    
    int** matrizResultado = m.getMatrizR();

    
    cout << "\nMatriz 1:" << endl;
    m.imprimirMatriz(matriz1);

    cout << "\nMatriz 2:" << endl;
    m.imprimirMatriz(matriz2);

    cout << "\nMatriz Resultado :" << endl;
    m.imprimirMatriz(matrizResultado);

    return 0;
}
