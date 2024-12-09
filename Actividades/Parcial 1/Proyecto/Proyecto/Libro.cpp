#include "Libro.h"

int Libro::contadorCodigo = 1;  // Inicializamos el contador a 1

// Constructor
Libro::Libro(const std::string& titulo, const Autor& autor, const Fecha& fechaPublicacion, const std::string& editorial)
    : codigo(contadorCodigo++), titulo(titulo), autor(autor), fechaPublicacion(fechaPublicacion), editorial(editorial) {}

// Obtiene el código del libro
int Libro::getCodigo() const {
    return codigo;
}

// Muestra la información del libro
std::string Libro::obtenerInformacion() const {
    return "Código: " + std::to_string(codigo) + ", Titulo: " + titulo + ", Autor: " + autor.obtenerNombreCompleto() +
           ", Publicado: " + fechaPublicacion.obtenerFecha() + ", Editorial: " + editorial;
}

// Sobrecarga del operador '==' para comparar libros
bool Libro::operator==(const Libro& otro) const {
    return codigo == otro.codigo;
}
