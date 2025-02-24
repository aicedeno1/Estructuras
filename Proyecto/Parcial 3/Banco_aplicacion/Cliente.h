#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <vector>
#include <memory>
#include "Cuenta.h"

class Cliente {
private:
    std::string cedula;
    std::string nombres;
    std::string apellidos;
    std::string correo;
    std::string telefono;
    std::string direccion;
    std::string contrasena;
    std::vector<std::shared_ptr<Cuenta>> cuentas;
    bool activo;

public:
    // Constructor
    Cliente(std::string cedula, std::string nombres, std::string apellidos, 
            std::string correo, std::string telefono, std::string direccion,
            std::string contrasena);
    
    // Métodos getter
    std::string getCedula() const;
    std::string getNombres() const;
    std::string getApellidos() const;
    std::string getNombreCompleto() const;
    std::string getCorreo() const;
    std::string getTelefono() const;
    std::string getDireccion() const;
    bool isActivo() const;
    std::vector<std::shared_ptr<Cuenta>> getCuentas() const;
    
    // Métodos setter
    void setCorreo(const std::string& correo);
    void setTelefono(const std::string& telefono);
    void setDireccion(const std::string& direccion);
    void setContrasena(const std::string& contrasena);
    
    // Métodos para gestión de cuentas
    void agregarCuenta(std::shared_ptr<Cuenta> cuenta);
    std::shared_ptr<Cuenta> buscarCuentaPorNumero(const std::string& numeroCuenta);
    void mostrarCuentas() const;
    
    // Métodos para activar/desactivar el cliente
    void activar();
    void desactivar();
    
    // Método para verificar la contraseña
    bool verificarContrasena(const std::string& contrasena) const;
    
    // Método para mostrar información del cliente
    void mostrarInformacion() const;
};

#endif