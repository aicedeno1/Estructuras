#include "Validaciones.h"
#include <algorithm>
#include <cctype>
#include <regex>

std::string Validaciones::convertirMinusculas(const std::string& cadena) {
    std::string resultado = cadena;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
    return resultado;
}

std::string Validaciones::eliminarEspacios(const std::string& cadena) {
    std::string resultado = cadena;
    resultado.erase(remove_if(resultado.begin(), resultado.end(), isspace), resultado.end());
    return resultado;
}

bool Validaciones::esCadenaValida(const std::string& cadena) {
    // Valida que solo contenga letras y espacios
    return std::regex_match(cadena, std::regex("^[a-zA-Z ]+$"));
}

bool Validaciones::esNumeroValido(const std::string& numero) {
    // Valida que sea un número positivo
    return std::regex_match(numero, std::regex("^\\d+$"));
}
