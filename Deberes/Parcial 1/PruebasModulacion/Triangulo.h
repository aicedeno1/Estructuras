#pragma once

class Triangulo {
private:
    double ladoA;
    double ladoB;
    double ladoC;

    // Método privado para calcular el semiperímetro
    double calcularSemiperimetro() const;

public:
    // Constructor
    Triangulo(double a, double b, double c);

    // Método para calcular el área
    double calcularArea() const;

    // Método para mostrar los lados
    void mostrarLados() const;
};


