#ifndef LIBRO_H
#define LIBRO_H

#include <string>
#include "Autor.h"
#include "Fecha.h"  // Asegúrate de incluir la clase Fecha

class Libro {
private:
    int codigo;            // Código único del libro
    std::string titulo;
    Autor autor;
    Fecha fechaPublicacion; // Fecha de publicación
    std::string editorial;

public:
    static int contadorCodigo; // Contador estático para generar el código

    // Constructor con código generado automáticamente
    Libro(const std::string& titulo, const Autor& autor, const Fecha& fechaPublicacion, const std::string& editorial);
    
    int getCodigo() const; // Obtiene el código del libro
    std::string obtenerInformacion() const;
    
    bool operator==(const Libro& otro) const;
};

#endif
