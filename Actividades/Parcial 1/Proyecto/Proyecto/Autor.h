#ifndef AUTOR_H
#define AUTOR_H

#include <string>
#include <iostream>

class Autor {
private:
    std::string nombre;
    std::string apellido;

public:
    // Constructor
    Autor(const std::string& nombre, const std::string& apellido);

    // Métodos
    std::string obtenerNombreCompleto() const;
    bool operator==(const Autor& other) const;
};

#endif
