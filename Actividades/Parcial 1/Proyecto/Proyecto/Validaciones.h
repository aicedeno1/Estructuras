#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

class Validaciones {
public:
    // Convierte la cadena a minúsculas
    static std::string convertirMinusculas(const std::string& cadena);
    
    // Elimina los espacios en blanco de una cadena
    static std::string eliminarEspacios(const std::string& cadena);

    // Valida que la cadena contenga solo letras y espacios
    static bool esCadenaValida(const std::string& cadena);

    // Valida que la cadena contenga solo números
    static bool esNumeroValido(const std::string& numero);

    // Valida si la fecha es correcta
    static bool esFechaValida(int dia, int mes, int año);
};

#endif
