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
    // Solo permite letras y espacios
    return std::regex_match(cadena, std::regex("^[a-zA-Z ]+$"));
}

bool Validaciones::esNumeroValido(const std::string& numero) {
    // Solo permite números positivos
    return std::regex_match(numero, std::regex("^\\d+$"));
}

bool Validaciones::esFechaValida(int dia, int mes, int año) {
    // Verifica que los valores de la fecha sean válidos (esto no es exhaustivo, solo básico)
    if (mes < 1 || mes > 12 || dia < 1 || año < 1000 || año > 9999) return false;

    // Días máximos por mes
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((mes == 2 && ((año % 4 == 0 && año % 100 != 0) || (año % 400 == 0))) // Bisiesto
        && dia > 29) return false;
    else if (dia > diasPorMes[mes - 1]) return false;

    return true;
}
