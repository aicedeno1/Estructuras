#include "Autor.h"

// Constructor de Autor
Autor::Autor(const std::string& nombre, const std::string& apellido)
    : nombre(nombre), apellido(apellido) {}

// Método para obtener el nombre completo
std::string Autor::obtenerNombreCompleto() const {
    return nombre + " " + apellido;
}

// Sobrecarga del operador '==' para comparar autores
bool Autor::operator==(const Autor& other) const {
    return nombre == other.nombre && apellido == other.apellido;
}

// Getters
std::string Autor::getNombre() const {
    return nombre;
}

std::string Autor::getApellido() const {
    return apellido;
}
