#include <iostream>
#include <windows.h>
#include "Matriz.h"

typedef int (__cdecl* ValidarEntero)(const char*);

int main() {
    // Cargar la DLL
    HINSTANCE hDLL = LoadLibrary("Validaciones.dll");
    if (!hDLL) {
        std::cerr << "No se pudo cargar la DLL" << std::endl;
        return 1;
    }

    // Obtener la función de validación
    ValidarEntero ingresarEntero = (ValidarEntero)GetProcAddress(hDLL, "ingresarEntero");
    if (!ingresarEntero) {
        std::cerr << "No se encontró la función 'ingresarEntero' en la DLL" << std::endl;
        FreeLibrary(hDLL);
        return 1;
    }

    int dim;

    // Solicitar al usuario la dimensión de las matrices
    dim = ingresarEntero("Ingrese la dimensión de las matrices (máximo 3x3): ");
    if (dim > 3) {
        std::cout << "La dimensión no puede ser mayor que 3x3" << std::endl;
        FreeLibrary(hDLL);
        return 1;
    }

    // Crear las matrices
    Matriz<int> m1(dim);
    Matriz<int> m2(dim);

    // Solicitar los elementos de la primera matriz
    std::cout << "Ingrese los elementos de la primera matriz:" << std::endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            int valor = ingresarEntero(("Elemento [" + std::to_string(i) + "][" + std::to_string(j) + "]: ").c_str());
            m1.setElemento(i, j, valor);
        }
    }

    // Solicitar los elementos de la segunda matriz
    std::cout << "Ingrese los elementos de la segunda matriz:" << std::endl;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            int valor = ingresarEntero(("Elemento [" + std::to_string(i) + "][" + std::to_string(j) + "]: ").c_str());
            m2.setElemento(i, j, valor);
        }
    }

    // Mostrar las matrices
    std::cout << "Primera matriz:" << std::endl;
    m1.imprimir();
    std::cout << "Segunda matriz:" << std::endl;
    m2.imprimir();

    // Sumar las matrices
    Matriz<int> resultado = m1.sumar(m2);

    // Mostrar el resultado
    std::cout << "Resultado de la suma de matrices:" << std::endl;
    resultado.imprimir();

    // Liberar la DLL
    FreeLibrary(hDLL);

    return 0;
}
