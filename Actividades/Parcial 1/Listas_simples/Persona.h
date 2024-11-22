#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>

class Persona {
private:
    std::string nombre;
    std::string apellido;
    std::string cedula;

public:
    // Constructor
    Persona(const std::string& nombre, const std::string& apellido, const std::string& cedula)
        : nombre(nombre), apellido(apellido), cedula(cedula) {}

    // Getters
    std::string getNombre() const { return nombre; }
    std::string getApellido() const { return apellido; }
    std::string getCedula() const { return cedula; }

    // Setters
    void setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }
    void setApellido(const std::string& nuevoApellido) { apellido = nuevoApellido; }
    void setCedula(const std::string& nuevaCedula) { cedula = nuevaCedula; }

    // Sobrecarga del operador ==
    bool operator==(const Persona& otra) const {
        return cedula == otra.cedula; // Compara por cédula
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream& os, const Persona& persona) {
        os << "Nombre: " << persona.nombre << ", Apellido: " << persona.apellido
           << ", Cedula: " << persona.cedula;
        return os;
    }
};

#endif


