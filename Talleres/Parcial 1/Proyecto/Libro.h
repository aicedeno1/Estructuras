#ifndef LIBRO_H
#define LIBRO_H

#include <string>
#include "Autor.h"
#include "Fecha.h"

class Libro {
private:
    std::string codigo;  // Código único del libro
    std::string titulo;
    Autor autor;
    Fecha fechaPublicacion;
    std::string editorial;
    static int contador;  // Contador estático para generar códigos

public:
    // Constructor normal para nuevos libros
    Libro(const std::string& titulo, const Autor& autor, const Fecha& fecha, const std::string& editorial);

    // Constructor especial para restaurar desde backup
    Libro(const std::string& codigo, const std::string& titulo, const Autor& autor, 
          const Fecha& fecha, const std::string& editorial);

    // Métodos
    std::string obtenerCodigo() const;  // Obtener el código del libro
    std::string obtenerInformacion() const;
    bool operator==(const Libro& other) const;
   
    // Getters
    std::string getTitulo() const;
    Autor getAutor() const;
    Fecha getFechaPublicacion() const;
    std::string getEditorial() const;
};

#endif
