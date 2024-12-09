#ifndef AUTOR_H
#define AUTOR_H

#include <string>
#include <iostream>
#include "Fecha.h"

class Autor {
private:
    std::string nombre;
    std::string apellido;
    Fecha fechaNacimiento;

public:
    // Constructor por defecto (necesario para el std::map)
    Autor() : nombre(""), apellido(""), fechaNacimiento(0, 0, 0) {}
    
    // Constructor con parámetros
    Autor(const std::string& nombre, const std::string& apellido, const Fecha& fechaNac);

    // Métodos
    std::string obtenerNombreCompleto() const;
    std::string obtenerFechaNacimiento() const;
    bool operator==(const Autor& other) const;

    // Getters
    std::string getNombre() const;
    std::string getApellido() const;
};

#endif
