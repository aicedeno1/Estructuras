#ifndef Calculo_h
#define Calculo_h

#include "Fraccion1.h"

template <typename T>
class Calculo {
public:
    Calculo(Fraccion<T> a, Fraccion<T> b) : a(a), b(b) {}

    Fraccion<T> sumar();

private:
    Fraccion<T> a;
    Fraccion<T> b;
};
template <typename T>
Fraccion<T> Calculo<T>::sumar() {
    T numerador = (a.numerador * b.denominador) + (b.numerador * a.denominador);
    T denominador = a.denominador * b.denominador;
    return Fraccion<T>(numerador, denominador);
}
#endif
