#ifndef BANCO_H
#define BANCO_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Cliente.h"

class Banco {
private:
    std::unordered_map<std::string, std::shared_ptr<Cliente>> clientes; // Cédula -> Cliente
    int ultimoNumeroCuenta;
    
    // Método para generar un nuevo número de cuenta
    std::string generarNumeroCuenta();

public:
    std::string nombre; // Hacemos público el nombre para poder acceder desde el main

public:
    // Constructor
    Banco(const std::string& nombre);
    
    // Métodos para gestión de clientes
    bool registrarCliente(const std::string& cedula, const std::string& nombres, 
                          const std::string& apellidos, const std::string& correo, 
                          const std::string& telefono, const std::string& direccion,
                          const std::string& contrasena);
                          
    std::shared_ptr<Cliente> buscarClientePorCedula(const std::string& cedula);
    std::shared_ptr<Cliente> autenticarCliente(const std::string& cedula, const std::string& contrasena);
    void listarClientes() const;
    
    // Métodos para gestión de cuentas
    bool crearCuenta(const std::string& cedulaCliente, TipoCuenta tipo, double saldoInicial);
    std::shared_ptr<Cuenta> buscarCuentaPorNumero(const std::string& numeroCuenta);
    bool realizarTransferencia(const std::string& numeroCuentaOrigen, 
                             const std::string& numeroCuentaDestino, 
                             double monto, 
                             const std::string& descripcion);
    
    // Métodos para servicios bancarios
    bool pagarServicio(const std::string& numeroCuenta, const std::string& tipoServicio, 
                      double monto, const std::string& referencia);
    
    // Métodos para guardado/carga de datos
    bool guardarDatos(const std::string& rutaArchivo) const;
    bool cargarDatos(const std::string& rutaArchivo);
};

#endif