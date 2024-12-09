#include "Autor.h"

Autor::Autor(const std::string& nombre, const std::string& apellido, const Fecha& fechaNac)
    : nombre(nombre), apellido(apellido), fechaNacimiento(fechaNac) {}

std::string Autor::obtenerNombreCompleto() const {
    return nombre + " " + apellido;
}

std::string Autor::obtenerFechaNacimiento() const {
    return fechaNacimiento.obtenerFecha();
}

bool Autor::operator==(const Autor& other) const {
    return nombre == other.nombre && apellido == other.apellido;
}

std::string Autor::getNombre() const {
    return nombre;
}

std::string Autor::getApellido() const {
    return apellido;
}
