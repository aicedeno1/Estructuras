#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

class Validaciones {
public:
    static int ingresar_entero(const char* mensaje);
    static std::string ingresar_string(const char* mensaje);
    static std::string ingresar_cedula(const char* mensaje);
    static std::string ingresar_string_con_mayuscula(const char* mensaje); // Nueva función
    static std::string ingresar_fecha(const char* mensaje);               // Nueva función
};

#endif
