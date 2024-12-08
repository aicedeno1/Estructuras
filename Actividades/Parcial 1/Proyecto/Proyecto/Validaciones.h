#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

class Validaciones {
public:
    static std::string convertirMinusculas(const std::string& cadena);
    static std::string eliminarEspacios(const std::string& cadena);
    static bool esCadenaValida(const std::string& cadena);
    static bool esNumeroValido(const std::string& numero);
};

#endif
