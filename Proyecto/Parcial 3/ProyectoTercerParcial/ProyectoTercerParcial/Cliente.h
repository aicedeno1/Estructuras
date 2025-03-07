/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Clase Cliente para sistema bancario                      *
 * Autor:                          Diaz Stiven, Cedenio Andres                              *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include "Fecha.h"
#include "Usuario.h"

class Cliente : public Usuario
{
private:
    std::string cedula;
    std::string nombre;
    std::string apellido;
    std::string direccion;
    std::string telefono;
    std::string email;
    Fecha fechaNacimiento;

public:
    // Constructores
    Cliente();
    Cliente(std::string cedula, std::string nombre, std::string apellido,
            std::string direccion, std::string telefono, std::string email,
            Fecha fechaNacimiento, std::string username, std::string password);

    // Getters y setters
    std::string getCedula() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getNombreCompleto() const;
    std::string getDireccion() const;
    std::string getTelefono() const;
    std::string getEmail() const;
    Fecha getFechaNacimiento() const;

    void setCedula(const std::string &cedula);
    void setNombre(const std::string &nombre);
    void setApellido(const std::string &apellido);
    void setDireccion(const std::string &direccion);
    void setTelefono(const std::string &telefono);
    void setEmail(const std::string &email);
    void setFechaNacimiento(const Fecha &fechaNacimiento);

    // Método para mostrar la información del cliente
    void mostrar() const;
    std::string toString() const;

    // Método para validar cédula ecuatoriana
    static bool validarCedula(const std::string &cedula);
};

#endif // CLIENTE_H
