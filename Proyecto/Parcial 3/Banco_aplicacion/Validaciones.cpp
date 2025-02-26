#include "Validaciones.h"
#include <cctype>
#include <iostream>

bool validarNumero(const std::string &str)
{
    if (str.empty())
    {
        return false;
    }

    size_t i = 0;
    if (str[0] == '-' || str[0] == '+')
    {
        i = 1;
        if (str.size() == 1)
        {
            return false;
        }
    }

    bool puntoEncontrado = false;

    for (; i < str.size(); ++i)
    {
        if (str[i] == '.' && !puntoEncontrado)
        {
            puntoEncontrado = true;
        }
        else if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

bool validarSoloLetras(const std::string &str) 
{
    if (str.empty()) 
    {
        return false;
    }
    
    for (char c : str) 
    {
        if (!isalpha(c)) 
        {
            return false;
        }
    }
    
    return true;
}

bool validarCedula(const std::string &cedula)
{
    // Validación básica: solo números y longitud adecuada
    if (cedula.empty() || cedula.length() < 5 || cedula.length() > 15)
    {
        return false;
    }

    for (char c : cedula)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

bool validarCorreo(const std::string &correo)
{
    // Validación básica: debe contener @ y un punto después
    size_t posArroba = correo.find('@');
    if (posArroba == std::string::npos || posArroba == 0) 
    {
        return false;
    }
    
    // Verificar que haya caracteres antes del @
    if (posArroba < 1) 
    {
        return false;
    }
    
    // Verificar que haya un dominio después del @
    size_t posPunto = correo.find('.', posArroba);
    if (posPunto == std::string::npos || posPunto == correo.length() - 1 || posPunto == posArroba + 1) 
    {
        return false;
    }
    
    // Verificar que haya caracteres entre @ y .
    if (posPunto - posArroba <= 1) 
    {
        return false;
    }
    
    // Verificar caracteres válidos
    for (char c : correo) 
    {
        if (!isalnum(c) && c != '@' && c != '.' && c != '_' && c != '-') 
        {
            return false;
        }
    }
    
    return true;
}

bool validarTelefono(const std::string &telefono)
{
    // Nueva validación: exactamente 10 dígitos, sin otros caracteres
    if (telefono.length() != 10)
    {
        return false;
    }

    for (char c : telefono)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

bool validarContrasena(const std::string &contrasena)
{
    // Validación básica: longitud mínima
    if (contrasena.length() < 6)
    {
        return false;
    }
    
    // Aquí se pueden añadir más criterios de seguridad si se desea
    // Por ejemplo, exigir al menos una mayúscula, un número, etc.
    
    return true;
}

bool validarDireccion(const std::string &direccion)
{
    // Validación de dirección: solo letras y máximo un espacio
    if (direccion.empty())
    {
        return false;
    }
    
    int espaciosEncontrados = 0;
    
    for (char c : direccion)
    {
        if (c == ' ')
        {
            espaciosEncontrados++;
            if (espaciosEncontrados > 1)
            {
                return false;
            }
        }
        else if (!isalpha(c))
        {
            return false;
        }
    }
    
    return true;
}

bool validarNoVacio(const std::string &str)
{
    return !str.empty();
}