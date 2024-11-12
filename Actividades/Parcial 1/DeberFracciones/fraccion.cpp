#include "Fraccion.h"
#include <iostream>
#include <conio.h>
using namespace std;

template <typename T>
Fraccion<T> Calculo<T>::sumar() {
    T numerador = (a.numerador * b.denominador) + (b.numerador * a.denominador);
    T denominador = a.denominador * b.denominador;
    return Fraccion<T>(numerador, denominador);
}
