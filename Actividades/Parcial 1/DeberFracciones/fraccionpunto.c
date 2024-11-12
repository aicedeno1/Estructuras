#include <iostream>
using namespace std;

template <typename T>
struct Fraccion {
    T numerador;
    T denominador;

    Fraccion(T num, T den) : numerador(num), denominador(den) {}
};

template <typename T>
class Calculo {
public:
    Calculo(Fraccion<T> a, Fraccion<T> b) : a(a), b(b) {}

    Fraccion<T> sumar();
    


private:
    Fraccion<T> a;
    Fraccion<T> b;
};
