#include "Operaciones.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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

// Inicializar matriz en ceros
void Operaciones::inicializarMatriz(int**& matriz) {
    int dim = _matriz.getDim();
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matriz[i][j] = 0;
        }
    }
}

// Generar matriz con valores aleatorios
void Operaciones::generarMatriz(int**& matriz) {
    int dim = _matriz.getDim();
    srand(time(NULL));
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matriz[i][j] = rand() % 3;  // Valores entre 0 y 2
        }
    }
}

// Imprimir matriz
void Operaciones::imprimirMatriz(int** matriz) {
    int dim = _matriz.getDim();
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Multiplicar matrices
void Operaciones::procesarMultiplicacion() {
    int dim = _matriz.getDim();
    inicializarMatriz(_matriz.getMatrizR());

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            for (int k = 0; k < dim; k++) {
                _matriz.getMatrizR()[i][j] += _matriz.getMatriz1()[i][k] * _matriz.getMatriz2()[k][j];
            }
        }
    }
}

// Elevar matriz a una potencia