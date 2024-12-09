#ifndef LIBRO_H
#define LIBRO_H

#include <string>
#include "Autor.h"
#include "Fecha.h"

class Libro {
private:
    int codigo;  // Código único del libro, ahora es un entero
    std::string titulo;
    Autor autor;
    Fecha fechaPublicacion;
    std::string editorial;

public:
    // Constructor
    Libro(const std::string& titulo, const Autor& autor, const Fecha& fecha, const std::string& editorial);

    // Métodos
    int obtenerCodigo() const;  // Obtener el código del libro (ahora devuelve un entero)
    std::string obtenerInformacion() const;
    bool operator==(const Libro& other) const;  

    // Getters
    std::string getTitulo() const;
    Autor getAutor() const;
    Fecha getFechaPublicacion() const;
    std::string getEditorial() const;
};

#endif
