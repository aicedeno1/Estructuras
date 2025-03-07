/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Clase Usuario para sistema bancario                      *
 * Autor:                         Diaz Stiven, Cedenio Andres                               *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario
{
private:
    std::string username;
    std::string password;
    std::string rol; // Puede ser "ADMIN" o "CLIENTE"

public:
    // Constructores
    Usuario();
    Usuario(std::string username, std::string password, std::string rol);

    // Getters y setters
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRol() const;

    void setUsername(const std::string &username);
    void setPassword(const std::string &password);
    void setRol(const std::string &rol);

    // Métodos de autenticación
    bool validarCredenciales(const std::string &inputUsername, const std::string &inputPassword) const;

    // Método para cifrar contraseña de manera simple
    static std::string cifrarPassword(const std::string &password);
};

#endif // USUARIO_H