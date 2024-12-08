#include "Libro.h"

Libro::Libro(const std::string& titulo, const Autor& autor) 
    : titulo(titulo), autor(autor) {}

std::string Libro::obtenerInformacion() const {
    return "Titulo: " + titulo + ", Autor: " + autor.obtenerNombreCompleto();
}

bool Libro::operator==(const Libro& otro) const {
    return titulo == otro.titulo && autor == otro.autor;
}
