#include "Matriz.h"
#include <iostream>

using namespace std;

// Constructor por defecto
Matriz::Matriz() : dim(3) {
    inicializarMatrices();
}

// Constructor con dimensión
Matriz::Matriz(int dim) : dim(dim) {
    if (dim > 3) {
        cout << "Error: La matriz no debe ser mayor a 3x3." << endl;
        matriz1 = matriz2 = matrizR = nullptr;
        return;
    }
    inicializarMatrices();
}

// Destructor
Matriz::~Matriz() {
    liberarMatriz(matriz1);
    liberarMatriz(matriz2);
    liberarMatriz(matrizR);
}

// Inicializar las matrices con new
void Matriz::inicializarMatrices() {
    matriz1 = new int*[dim];
    matriz2 = new int*[dim];
    matrizR = new int*[dim];
    for (int i = 0; i < dim; ++i) {
        matriz1[i] = new int[dim];
        matriz2[i] = new int[dim];
        matrizR[i] = new int[dim];
    }
}

// Getters y Setters
int Matriz::getDim() const {
    return dim;
}

int** Matriz::getMatriz1() {
    return matriz1;
}

int** Matriz::getMatriz2() {
    return matriz2;
}

int** Matriz::getMatrizR() {
    return matrizR;
}

// Métodos para imprimir y liberar memoria
void Matriz::imprimirMatriz(int** matriz) {
    auto imprimir = [this](int** matriz) {
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }
    };
    imprimir(matriz);
}

void Matriz::liberarMatriz(int** matriz) {
    for (int i = 0; i < dim; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

// Sumar matrices de forma recursiva
void Matriz::sumarMatricesRecursivo(int i, int j) {
    if (i >= dim) return;  // Base case: Si hemos llegado al final de las filas, salimos
    if (j >= dim) {  // Si hemos llegado al final de una fila, pasamos a la siguiente fila
        sumarMatricesRecursivo(i + 1, 0);
        return;
    }
    
    // Sumar los elementos correspondientes
    matrizR[i][j] = matriz1[i][j] + matriz2[i][j];
    
    // Llamada recursiva a la siguiente columna
    sumarMatricesRecursivo(i, j + 1);
}

// Método para iniciar la suma
void Matriz::sumarMatricesConRecursion() {
    sumarMatricesRecursivo(0, 0);  // Comenzar desde la primera fila y primera columna
}
