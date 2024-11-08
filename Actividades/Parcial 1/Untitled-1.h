
#ifndef INGRESAR_DATOS_H
#define INGRESAR_DATOS_H

#include <iostream>
#include <string>
#include <stdexcept>

class IngresarDatos {
public:
    static char ingresarEntero(const std::string &mensaje);
    static char ingresarFlotante(const std::string &mensaje);
    static char ingresarDouble(const std::string &mensaje);
};

#endif // INGRESAR_DATOS_H
