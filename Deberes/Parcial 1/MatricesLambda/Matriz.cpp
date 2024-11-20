#include "Matriz.h"
#include <iostream>

using namespace std;


Matriz::Matriz() : dim(3) {
    inicializarMatrices();
}


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


void Matriz::sumarMatricesRecursivo(int i, int j) {
    if (i >= dim) return;  
    if (j >= dim) {  
        sumarMatricesRecursivo(i + 1, 0);
        return;
    }
    
    
    matrizR[i][j] = matriz1[i][j] + matriz2[i][j];
    
   
    sumarMatricesRecursivo(i, j + 1);
}


void Matriz::sumarMatricesConRecursion() {
    sumarMatricesRecursivo(0, 0);  
}
