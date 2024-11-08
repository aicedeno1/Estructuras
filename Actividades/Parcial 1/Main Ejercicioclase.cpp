
#include <iostream>
#include "IngresarDatos.h"

int main() {
    char valorEntero = IngresarDatos::ingresarEntero("Ingrese un valor entero: ");
    std::cout << "Valor ingresado como entero (convertido a char): " << valorEntero << std::endl;

    char valorFlotante = IngresarDatos::ingresarFlotante("Ingrese un valor flotante: ");
    std::cout << "Valor ingresado como flotante (convertido a char): " << valorFlotante << std::endl;

    char valorDouble = IngresarDatos::ingresarDouble("Ingrese un valor double: ");
    std::cout << "Valor ingresado como double (convertido a char): " << valorDouble << std::endl;

    return 0;
}

}