#include "Operaciones.h"
#include <iostream>

using namespace std;

Operaciones::Operaciones() {}

Operaciones::Operaciones(Matriz m1) : _matriz(m1) {}

// Segmentar una matriz dinámica usando new
void Operaciones::segmentarMatriz(int**& matriz) {
    int dim = _matriz.getDim();
    matriz = new int*[dim];  // Crear arreglo de punteros

    for (int i = 0; i < dim; i++) {
        matriz[i] = new int[dim];  // Crear cada fila
    }
}

// Liberar memoria dinámica de una matriz usando delete
void Operaciones::liberarMatriz(int** matriz) {
    int dim = _matriz.getDim();
    for (int i = 0; i < dim; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
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
