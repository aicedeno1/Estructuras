#pragma once
#include "Matriz.h"

class Operaciones {
private:
    Matriz _matriz;

public:
    Operaciones();
    Operaciones(Matriz m1);

    void segmentarMatriz(int**& matriz);
    void liberarMatriz(int** matriz);
    void inicializarMatriz(int**& matriz);
    void imprimirMatriz(int** matriz);
};
