/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Validaciones para el sistema bancario                    *
 * Autor:                        Diaz Stiven, Cedenio Andres                                *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <cctype>
#include <regex>

namespace Validaciones
{
    // Validar que el string contenga solo dígitos
    inline bool esNumerico(const std::string &str)
    {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
    }

    // Validar email con formato básico
    inline bool esEmailValido(const std::string &email)
    {
        std::regex emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
        return std::regex_match(email, emailRegex);
    }

    // Validar que el string tenga una longitud mínima
    inline bool longitudMinima(const std::string &str, size_t minLongitud)
    {
        return str.length() >= minLongitud;
    }

    // Validar que el string contenga solo letras y espacios
    inline bool soloLetrasYEspacios(const std::string &str)
    {
        return std::all_of(str.begin(), str.end(), [](char c)
                           { return std::isalpha(c) || std::isspace(c); });
    }

    // Validar número de teléfono (formato simple: solo dígitos, longitud 10)
    inline bool esTelefonoValido(const std::string &telefono)
    {
        return telefono.length() == 10 && esNumerico(telefono);
    }

    // Validar nombre de usuario (alfanumérico, sin espacios)
    inline bool esUsernameValido(const std::string &username)
    {
        return !username.empty() && std::all_of(username.begin(), username.end(), [](char c)
                                                { return std::isalnum(c); });
    }
}

#endif // VALIDACIONES_H