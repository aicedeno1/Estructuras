#include "Libro.h"

// Inicialización del contador estático
int Libro::contador = 1;

// Constructor normal para nuevos libros
Libro::Libro(const std::string& titulo, const Autor& autor, const Fecha& fecha, const std::string& editorial)
    : titulo(titulo), autor(autor), fechaPublicacion(fecha), editorial(editorial) {
    codigo = std::to_string(contador++);
}

// Constructor especial para restaurar desde backup
Libro::Libro(const std::string& codigo, const std::string& titulo, const Autor& autor, 
             const Fecha& fecha, const std::string& editorial)
    : codigo(codigo), titulo(titulo), autor(autor), fechaPublicacion(fecha), editorial(editorial) {
    // Actualizar el contador si es necesario
    try {
        int codigoNum = std::stoi(codigo);
        if (codigoNum >= contador) {
            contador = codigoNum + 1;
        }
    } catch (...) {
        // Si hay error al convertir el código, simplemente continuamos
    }
}

std::string Libro::obtenerCodigo() const {
    return codigo;
}

std::string Libro::obtenerInformacion() const {
    return "Código: " + codigo + " | Título: " + titulo + " | Autor: " + 
           autor.obtenerNombreCompleto() + " | Fecha: " + 
           fechaPublicacion.obtenerFecha() + " | Editorial: " + editorial;
}

bool Libro::operator==(const Libro& other) const {
    return codigo == other.codigo;
}

// Getters
std::string Libro::getTitulo() const { 
    return titulo; 
}

Autor Libro::getAutor() const { 
    return autor; 
}

Fecha Libro::getFechaPublicacion() const { 
    return fechaPublicacion; 
}

std::string Libro::getEditorial() const { 
    return editorial; 
}