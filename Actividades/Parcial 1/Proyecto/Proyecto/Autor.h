#ifndef AUTOR_H
#define AUTOR_H

#include <string>
#include <iostream>
#include "Fecha.h"

class Autor {
private:
    std::string nombre;
    std::string apellido;
    Fecha fechaNacimiento; // Fecha de nacimiento

public:
    // Constructor
    Autor(const std::string& nombre, const std::string& apellido, const Fecha& fechaNacimiento);

    // Métodos
    std::string obtenerNombreCompleto() const;
    bool operator==(const Autor& other) const;

    // Getters
    std::string getNombre() const;
    std::string getApellido() const;
    Fecha getFechaNacimiento() const; // Método para obtener la fecha de nacimiento
    std::string obtenerFechaNacimiento() const; // Método para obtener la fecha de nacimiento como string
};

#endif
