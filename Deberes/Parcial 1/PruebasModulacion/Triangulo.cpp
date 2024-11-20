#include "Triangulo.h"
#include <iostream>
#include <cmath>

// Constructor
Triangulo::Triangulo(double a, double b, double c) : ladoA(a), ladoB(b), ladoC(c) {}

// Método privado para calcular el semiperímetro
double Triangulo::calcularSemiperimetro() const {
    return (ladoA + ladoB + ladoC) / 2;
}

// Método para calcular el área
double Triangulo::calcularArea() const {
    double s = calcularSemiperimetro();
    return std::sqrt(s * (s - ladoA) * (s - ladoB) * (s - ladoC));
}

// Método para mostrar los lados
void Triangulo::mostrarLados() const {
    std::cout << "Lados del triángulo: "
              << "A = " << ladoA
              << ", B = " << ladoB
              << ", C = " << ladoC << std::endl;
}
