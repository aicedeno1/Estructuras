#include <iostream>
#include "Operaciones.h"

Operaciones::Operaciones() {}

Operaciones::Operaciones(Matriz m1) {
    this->_matriz = m1;
}

// Suma recursiva de las matrices
int Operaciones::sumaRecursivaMatrices(int** mat1, int** mat2, int f, int c) {
    if (f == 0 && c == 0) {
        return mat1[f][c] + mat2[f][c];  // Caso base: suma las primeras posiciones
    } else {
        if (c > -1) {
            c--;  // Recursivamente mueve las columnas hacia la izquierda
            return mat1[f][c + 1] + mat2[f][c + 1] + sumaRecursivaMatrices(mat1, mat2, f, c);  // Recursión en columnas
        } else {
            return sumaRecursivaMatrices(mat1, mat2, f - 1, MAX - 1);  // Cuando se llega al final de la fila, se avanza a la siguiente fila
        }
    }
}
