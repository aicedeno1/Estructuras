/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación de la clase Cliente                       *
 * Autor:                          Diaz Stiven, Cedenio andres                              *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Cliente.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Cliente::Cliente() : Usuario() {}

Cliente::Cliente(string cedula, string nombre, string apellido,
                 string direccion, string telefono, string email,
                 Fecha fechaNacimiento, string username, string password)
    : Usuario(username, password, "CLIENTE"),
      cedula(cedula), nombre(nombre), apellido(apellido),
      direccion(direccion), telefono(telefono),
      email(email), fechaNacimiento(fechaNacimiento) {}

// Getters
string Cliente::getCedula() const { return cedula; }
string Cliente::getNombre() const { return nombre; }
string Cliente::getApellido() const { return apellido; }
string Cliente::getNombreCompleto() const { return nombre + " " + apellido; }
string Cliente::getDireccion() const { return direccion; }
string Cliente::getTelefono() const { return telefono; }
string Cliente::getEmail() const { return email; }
Fecha Cliente::getFechaNacimiento() const { return fechaNacimiento; }

// Setters
void Cliente::setCedula(const string &cedula) { this->cedula = cedula; }
void Cliente::setNombre(const string &nombre) { this->nombre = nombre; }
void Cliente::setApellido(const string &apellido) { this->apellido = apellido; }
void Cliente::setDireccion(const string &direccion) { this->direccion = direccion; }
void Cliente::setTelefono(const string &telefono) { this->telefono = telefono; }
void Cliente::setEmail(const string &email) { this->email = email; }
void Cliente::setFechaNacimiento(const Fecha &fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }

// Método para mostrar información del cliente
void Cliente::mostrar() const
{
    cout << "Cédula: " << cedula << endl;
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Fecha de nacimiento: " << fechaNacimiento.mostrar() << endl;
    cout << "Dirección: " << direccion << endl;
    cout << "Teléfono: " << telefono << endl;
    cout << "Email: " << email << endl;
    cout << "Usuario: " << getUsername() << endl;
}

string Cliente::toString() const
{
    stringstream ss;
    ss << cedula << ";"
       << nombre << ";"
       << apellido << ";"
       << direccion << ";"
       << telefono << ";"
       << email << ";"
       << fechaNacimiento.toString() << ";"
       << getUsername() << ";"
       << getPassword() << ";"
       << getRol();
    return ss.str();
}

// Método para validar cédula ecuatoriana
bool Cliente::validarCedula(const std::string &cedula)
{
    if (cedula.length() != 10)
    {
        return false;
    }

    // Verificar que todos los caracteres sean dígitos
    for (char c : cedula)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    // Obtener el dígito de la provincia
    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24)
    {
        return false;
    }

    // Algoritmo de validación
    int suma = 0;
    for (int i = 0; i < 9; i++)
    {
        int digit = cedula[i] - '0';
        if (i % 2 == 0)
        {
            digit *= 2;
            if (digit > 9)
                digit -= 9;
        }
        suma += digit;
    }

    int verificador = (10 - (suma % 10)) % 10;
    return verificador == (cedula[9] - '0');
}