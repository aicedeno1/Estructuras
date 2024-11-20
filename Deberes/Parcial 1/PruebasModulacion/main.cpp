#include <iostream>
#include "Triangulo.h"

// Función para leer los lados desde la entrada del usuario
Triangulo leerTriangulo() {
    double a, b, c;
    std::cout << "Ingrese los tres lados del triángulo:" << std::endl;
    std::cin >> a >> b >> c;
    return Triangulo(a, b, c);
}

int main() {
    // Crear un triángulo leyendo los datos del usuario
    Triangulo triangulo = leerTriangulo();

    // Mostrar los lados del triángulo
    triangulo.mostrarLados();

    // Calcular y mostrar el área
    double area = triangulo.calcularArea();
    std::cout << "El área del triángulo es: " << area << std::endl;

    return 0;
}
