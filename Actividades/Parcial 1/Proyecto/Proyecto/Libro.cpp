#include "Libro.h"

Libro::Libro(const std::string& titulo, const Autor& autor, const Fecha& fecha, const std::string& editorial)
    : titulo(titulo), autor(autor), fechaPublicacion(fecha), editorial(editorial) {
    // Generación automática del código del libro, por ejemplo
    static int contador = 1;  // Generador de códigos únicos
    codigo = contador++;
}

int Libro::obtenerCodigo() const {
    return codigo;  // Devuelve el código como un entero
}

std::string Libro::obtenerInformacion() const {
    return "Codigo: " + std::to_string(codigo) + " | Titulo: " + titulo + 
           " | Autor: " + autor.obtenerNombreCompleto() + 
           " | Fecha: " + fechaPublicacion.obtenerFecha() + 
           " | Editorial: " + editorial;
}

bool Libro::operator==(const Libro& other) const {
    return codigo == other.codigo;  // Compara códigos como enteros
}

// Getters
std::string Libro::getTitulo() const { return titulo; }
Autor Libro::getAutor() const { return autor; }
Fecha Libro::getFechaPublicacion() const { return fechaPublicacion; }
std::string Libro::getEditorial() const { return editorial; }
