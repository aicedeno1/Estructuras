#pragma once
#include "Matriz.h"

class Operaciones {
public:
    Operaciones();
    Operaciones(Matriz);
    void segmentarMatriz(int**&);
    void inicializarMatriz(int**&);
    void generarMatriz(int**&);
    void procesarMultiplicacion();
    void imprimirMatriz(int**);
    void procesarPotencia(int exp);

private:
    Matriz _matriz;
};
