#ifndef Fraccion1_h
#define Fraccion1_h

template <typename T>
struct Fraccion {
    T numerador;
    T denominador;

    Fraccion(T num, T den) : numerador(num), denominador(den) {}
};

#endif
