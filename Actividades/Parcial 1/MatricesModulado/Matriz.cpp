#include <iostream>
#include "Matriz.h"

Matriz::Matriz() {
    // Inicializar la matriz a cero
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matriz[i][j] = 0;
        }
    }
}

void Matriz::ingresarMatrizPorTeclado() {
    std::cout << "Ingrese los elementos de la matriz: " << std::endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            std::cout << "Elemento [" << i << "][" << j << "]: ";
            std::cin >> matriz[i][j];
        }
    }
}

void Matriz::imprimirMatriz() const {
    std::cout << "Matriz:" << std::endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Para devolver las matrices como punteros
int** Matriz::getMatriz1() const {
    return const_cast<int**>(reinterpret_cast<const int*>(matriz));
}

int** Matriz::getMatriz2() const {
    return const_cast<int**>(reinterpret_cast<const int*>(matriz));
}
