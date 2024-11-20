#include "Operaciones.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Operaciones::Operaciones() {}

Operaciones::Operaciones(Matriz m1) {
    this->_matriz = m1;
}

// Segmentar una matriz dinámica
void Operaciones::segmentarMatriz(int**& matriz) {
    int dim = _matriz.getDim();
    matriz = (int**)malloc(dim * sizeof(int*));
    for (int i = 0; i < dim; i++) {
        matriz[i] = (int*)malloc(dim * sizeof(int));
    }
}

// Liberar memoria dinámica de una matriz
void Operaciones::liberarMatriz(int** matriz) {
    int dim = _matriz.getDim();
    for (int i = 0; i < dim; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Inicializar matriz en ceros (opcional)
void Operaciones::inicializarMatriz(int**& matriz) {
    int dim = _matriz.getDim();
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matriz[i][j] = 0;
        }
    }
}

// Imprimir matriz
void Operaciones::imprimirMatriz(int** matriz) {
    int dim = _matriz.getDim();
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}
