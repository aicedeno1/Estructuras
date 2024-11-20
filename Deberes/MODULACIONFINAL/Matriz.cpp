#include "Matriz.h"

Matriz::Matriz() {}

Matriz::Matriz(int** matriz1, int** matriz2, int** matrizR, int dim) {
    this->matriz1 = matriz1;
    this->matriz2 = matriz2;
    this->matrizR = matrizR;
    this->dim = dim;
}

int Matriz::getDim() {
    return dim;
}

void Matriz::setDim(int dim) {
    this->dim = dim;
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
