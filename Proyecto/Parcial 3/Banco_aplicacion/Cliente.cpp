#include "Cliente.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Cliente::Cliente(std::string cedula, std::string nombres, std::string apellidos, 
                 std::string correo, std::string telefono, std::string direccion,
                 std::string contrasena)
    : cedula(cedula), nombres(nombres), apellidos(apellidos), correo(correo), 
      telefono(telefono), direccion(direccion), contrasena(contrasena), activo(true) {
}

std::string Cliente::getCedula() const {
    return cedula;
}

std::string Cliente::getNombres() const {
    return nombres;
}

std::string Cliente::getApellidos() const {
    return apellidos;
}

std::string Cliente::getNombreCompleto() const {
    return nombres + " " + apellidos;
}

std::string Cliente::getCorreo() const {
    return correo;
}

std::string Cliente::getTelefono() const {
    return telefono;
}

std::string Cliente::getDireccion() const {
    return direccion;
}

bool Cliente::isActivo() const {
    return activo;
}

std::vector<std::shared_ptr<Cuenta>> Cliente::getCuentas() const {
    return cuentas;
}

void Cliente::setCorreo(const std::string& nuevoCorreo) {
    correo = nuevoCorreo;
}

void Cliente::setTelefono(const std::string& nuevoTelefono) {
    telefono = nuevoTelefono;
}

void Cliente::setDireccion(const std::string& nuevaDireccion) {
    direccion = nuevaDireccion;
}

void Cliente::setContrasena(const std::string& nuevaContrasena) {
    contrasena = nuevaContrasena;
}

void Cliente::agregarCuenta(std::shared_ptr<Cuenta> cuenta) {
    cuentas.push_back(cuenta);
}

std::shared_ptr<Cuenta> Cliente::buscarCuentaPorNumero(const std::string& numeroCuenta) {
    auto it = std::find_if(cuentas.begin(), cuentas.end(), 
                           [&numeroCuenta](const std::shared_ptr<Cuenta>& cuenta) {
                               return cuenta->getNumeroCuenta() == numeroCuenta;
                           });
    
    if (it != cuentas.end()) {
        return *it;
    }
    
    return nullptr;
}

void Cliente::mostrarCuentas() const {
    std::cout << "===== CUENTAS DEL CLIENTE =====" << std::endl;
    std::cout << std::left << std::setw(15) << "NÚMERO" 
              << std::setw(12) << "TIPO" 
              << std::setw(15) << "SALDO" 
              << "ESTADO" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (const auto& cuenta : cuentas) {
        std::cout << std::left << std::setw(15) << cuenta->getNumeroCuenta() 
                  << std::setw(12) << cuenta->getTipoString() 
                  << std::setw(15) << std::fixed << std::setprecision(2) << cuenta->getSaldo() 
                  << (cuenta->isActiva() ? "Activa" : "Inactiva") << std::endl;
    }
}

void Cliente::activar() {
    activo = true;
}

void Cliente::desactivar() {
    activo = false;
}

bool Cliente::verificarContrasena(const std::string& intentoContrasena) const {
    return contrasena == intentoContrasena;
}

void Cliente::mostrarInformacion() const {
    std::cout << "===== INFORMACIÓN DEL CLIENTE =====" << std::endl;
    std::cout << "Cédula: " << cedula << std::endl;
    std::cout << "Nombre completo: " << getNombreCompleto() << std::endl;
    std::cout << "Correo electrónico: " << correo << std::endl;
    std::cout << "Teléfono: " << telefono << std::endl;
    std::cout << "Dirección: " << direccion << std::endl;
    std::cout << "Estado: " << (activo ? "Activo" : "Inactivo") << std::endl;
    std::cout << "Número de cuentas: " << cuentas.size() << std::endl;
}