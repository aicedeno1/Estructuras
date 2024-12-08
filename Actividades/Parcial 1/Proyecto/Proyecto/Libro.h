#ifndef LIBRO_H
#define LIBRO_H

#include <string>
#include "Autor.h"

class Libro {
private:
    std::string titulo;
    Autor autor;

public:
    // Solo declaración de los métodos, no sus implementaciones
    Libro(const std::string& titulo, const Autor& autor);
    bool operator==(const Libro& other) const;
    std::string obtenerInformacion() const;
};

#endif
