#include "Validaciones.h"
#include <iostream>

int main() {
    Validaciones val;1

    int entero = val.ingresarEntero("Ingrese un numero entero: ");
    std::cout << "Entero ingresado: " << entero << std::endl;

    float flotante = val.ingresarFloat("Ingrese un numero flotante: ");
    std::cout << "Flotante ingresado: " << flotante << std::endl;

    double doble = val.ingresarDouble("Ingrese un numero double: ");
    std::cout << "Double ingresado: " << doble << std::endl;

    std::string letras = val.ingresarLetras("Ingrese una cadena de letras: ");
    std::cout << "Letras ingresadas: " << letras << std::endl;

    std::string texto = val.ingresarString("Ingrese una cadena alfanumerica: ");
    std::cout << "Cadena ingresada: " << texto << std::endl;

    return 0;
}
