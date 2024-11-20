#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "Matriz.h"

#define MAX 3  // Definir el tamaño de la matriz

class Operaciones {
private:
    Matriz _matriz;  // Usamos la clase Matriz para almacenar la matriz

public:
    Operaciones();
    Operaciones(Matriz m1);

    int sumaRecursivaMatrices(int** mat1, int** mat2, int f, int c);
};

#endif
