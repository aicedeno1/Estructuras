#include "Matriz.h"
#include <iostream>

using namespace std;

// Constructor por defecto
Matriz::Matriz() : dim(3) {  // Por defecto, la dimensión es 3x3
    // Reserva de memoria dinámica para las matrices
    matriz1 = new int*[dim];
    matriz2 = new int*[dim];
    matrizR = new int*[dim];
    for (int i = 0; i < dim; ++i) {
        matriz1[i] = new int[dim];
        matriz2[i] = new int[dim];
        matrizR[i] = new int[dim];
    }
}

// Constructor con dimensiones y matrices
Matriz::Matriz(int dim) : dim(dim) {
    if (dim > 3) {
        cout << "Error: La matriz no debe ser mayor a 3x3." << endl;
        return;
    }

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

void Matriz::setDim(int dim) {
    if (dim <= 3) {
        this->dim = dim;
    } else {
        cout << "La dimensión no puede ser mayor que 3." << endl;
    }
}

int** Matriz::getMatriz1() {
    return matriz1;
}

void Matriz::setMatriz1(int** matriz1) {
    this->matriz1 = matriz1;
}

int** Matriz::getMatriz2() {
    return matriz2;
}

void Matriz::setMatriz2(int** matriz2) {
    this->matriz2 = matriz2;
}

int** Matriz::getMatrizR() {
    return matrizR;
}

void Matriz::setMatrizR(int** matrizR) {
    this->matrizR = matrizR;
}

// Métodos para imprimir y liberar memoria
void Matriz::imprimirMatriz(int** matriz) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void Matriz::liberarMatriz(int** matriz) {
    for (int i = 0; i < dim; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

// Método para sumar las matrices
void Matriz::sumarMatrices() {
    // Sumar matriz1 y matriz2 y guardar el resultado en matrizR
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            matrizR[i][j] = matriz1[i][j] + matriz2[i][j];
        }
    }
}
