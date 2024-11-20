#include "Calculo.h"

template <typename T>
Fraccion<T> Calculo<T>::sumar() {
    T numerador = (a.numerador * b.denominador) + (b.numerador * a.denominador);
    T denominador = a.denominador * b.denominador;
    return Fraccion<T>(numerador, denominador);
}

// Necesitamos instanciar las plantillas en el .cpp para que el compilador las entienda
template class Calculo<float>;
template class Calculo<double>;
