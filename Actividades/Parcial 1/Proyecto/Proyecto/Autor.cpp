#include "Autor.h"

Autor::Autor(const std::string& nombre, const std::string& apellido, const Fecha& fechaNacimiento)
    : nombre(nombre), apellido(apellido), fechaNacimiento(fechaNacimiento) {}

std::string Autor::obtenerNombreCompleto() const {
    return nombre + " " + apellido;
}

bool Autor::operator==(const Autor& other) const {
    return (nombre == other.nombre && apellido == other.apellido);
}

std::string Autor::getNombre() const {
    return nombre;
}

std::string Autor::getApellido() const {
    return apellido;
}

Fecha Autor::getFechaNacimiento() const {
    return fechaNacimiento; // Retorna el objeto Fecha
}

std::string Autor::obtenerFechaNacimiento() const {
    return fechaNacimiento.obtenerFecha(); // Devuelve la fecha como string en formato DD/MM/AAAA
}
