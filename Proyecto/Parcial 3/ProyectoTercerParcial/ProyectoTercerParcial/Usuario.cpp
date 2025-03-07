/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación de la clase Usuario                       *
 * Autor:                          Diaz Stiven, Cedenio Andres                               *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Usuario.h"
#include <iostream>

using namespace std;

Usuario::Usuario() : rol("CLIENTE") {}

Usuario::Usuario(string username, string password, string rol)
    : username(username), password(password), rol(rol) {}

// Getters
string Usuario::getUsername() const { return username; }
string Usuario::getPassword() const { return password; }
string Usuario::getRol() const { return rol; }

// Setters
void Usuario::setUsername(const string &username) { this->username = username; }
void Usuario::setPassword(const string &password) { this->password = password; }
void Usuario::setRol(const string &rol) { this->rol = rol; }

// Método para validar credenciales
bool Usuario::validarCredenciales(const string &inputUsername, const string &inputPassword) const
{
    return (username == inputUsername && password == cifrarPassword(inputPassword));
}

// Método para cifrar contraseña de manera simple (XOR con clave fija)
string Usuario::cifrarPassword(const string &password)
{
    const string clave = "BancoESPE2025"; // Clave de cifrado
    string result = password;

    for (size_t i = 0; i < result.length(); ++i)
    {
        result[i] = result[i] ^ clave[i % clave.length()];
    }

    // Convertir a representación hexadecimal para almacenamiento
    string hexResult = "";
    for (unsigned char c : result)
    {
        char hex[3];
        sprintf(hex, "%02x", c);
        hexResult += hex;
    }

    return hexResult;
}