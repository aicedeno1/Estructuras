#include "Banco.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>

Banco::Banco(const std::string& nombre) : nombre(nombre), ultimoNumeroCuenta(1000) {
}

std::string Banco::generarNumeroCuenta() {
    // Generar un número de cuenta único
    ultimoNumeroCuenta++;
    std::stringstream ss;
    ss << "10" << std::setw(8) << std::setfill('0') << ultimoNumeroCuenta;
    return ss.str();
}

bool Banco::registrarCliente(const std::string& cedula, const std::string& nombres, 
                            const std::string& apellidos, const std::string& correo, 
                            const std::string& telefono, const std::string& direccion,
                            const std::string& contrasena) {
    // Verificar si ya existe un cliente con esa cédula
    if (clientes.find(cedula) != clientes.end()) {
        std::cout << "Error: Ya existe un cliente con la cédula " << cedula << std::endl;
        return false;
    }
    
    // Crear nuevo cliente
    auto nuevoCliente = std::make_shared<Cliente>(cedula, nombres, apellidos, 
                                                  correo, telefono, direccion, 
                                                  contrasena);
    
    // Agregar al mapa de clientes
    clientes[cedula] = nuevoCliente;
    
    std::cout << "Cliente registrado exitosamente." << std::endl;
    return true;
}

std::shared_ptr<Cliente> Banco::buscarClientePorCedula(const std::string& cedula) {
    auto it = clientes.find(cedula);
    if (it != clientes.end()) {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<Cliente> Banco::autenticarCliente(const std::string& cedula, const std::string& contrasena) {
    auto cliente = buscarClientePorCedula(cedula);
    
    if (cliente && cliente->verificarContrasena(contrasena) && cliente->isActivo()) {
        return cliente;
    }
    
    return nullptr;
}

void Banco::listarClientes() const {
    std::cout << "===== LISTA DE CLIENTES =====" << std::endl;
    std::cout << std::left << std::setw(15) << "CÉDULA" 
              << std::setw(30) << "NOMBRE" 
              << std::setw(25) << "CORREO" 
              << "ESTADO" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (const auto& par : clientes) {
        const auto& cliente = par.second;
        std::cout << std::left << std::setw(15) << cliente->getCedula() 
                  << std::setw(30) << cliente->getNombreCompleto() 
                  << std::setw(25) << cliente->getCorreo() 
                  << (cliente->isActivo() ? "Activo" : "Inactivo") << std::endl;
    }
}

bool Banco::crearCuenta(const std::string& cedulaCliente, TipoCuenta tipo, double saldoInicial) {
    auto cliente = buscarClientePorCedula(cedulaCliente);
    
    if (!cliente) {
        std::cout << "Error: Cliente no encontrado." << std::endl;
        return false;
    }
    
    if (!cliente->isActivo()) {
        std::cout << "Error: El cliente está inactivo." << std::endl;
        return false;
    }
    
    if (saldoInicial < 0) {
        std::cout << "Error: El saldo inicial no puede ser negativo." << std::endl;
        return false;
    }
    
    // Generar número de cuenta
    std::string numeroCuenta = generarNumeroCuenta();
    
    // Crear la cuenta
    auto nuevaCuenta = std::make_shared<Cuenta>(numeroCuenta, saldoInicial, tipo);
    
    // Agregar la cuenta al cliente
    cliente->agregarCuenta(nuevaCuenta);
    
    std::cout << "Cuenta creada exitosamente: " << numeroCuenta << std::endl;
    return true;
}

std::shared_ptr<Cuenta> Banco::buscarCuentaPorNumero(const std::string& numeroCuenta) {
    // Buscar en todos los clientes
    for (const auto& par : clientes) {
        auto cuenta = par.second->buscarCuentaPorNumero(numeroCuenta);
        if (cuenta) {
            return cuenta;
        }
    }
    
    return nullptr;
}

bool Banco::realizarTransferencia(const std::string& numeroCuentaOrigen, 
                                 const std::string& numeroCuentaDestino, 
                                 double monto, 
                                 const std::string& descripcion) {
    if (monto <= 0) {
        std::cout << "Error: El monto debe ser positivo." << std::endl;
        return false;
    }
    
    auto cuentaOrigen = buscarCuentaPorNumero(numeroCuentaOrigen);
    auto cuentaDestino = buscarCuentaPorNumero(numeroCuentaDestino);
    
    if (!cuentaOrigen) {
        std::cout << "Error: Cuenta origen no encontrada." << std::endl;
        return false;
    }
    
    if (!cuentaDestino) {
        std::cout << "Error: Cuenta destino no encontrada." << std::endl;
        return false;
    }
    
    return cuentaOrigen->transferir(*cuentaDestino, monto, descripcion);
}

bool Banco::pagarServicio(const std::string& numeroCuenta, const std::string& tipoServicio, 
                         double monto, const std::string& referencia) {
    auto cuenta = buscarCuentaPorNumero(numeroCuenta);
    
    if (!cuenta) {
        std::cout << "Error: Cuenta no encontrada." << std::endl;
        return false;
    }
    
    std::string descripcion = "Pago de " + tipoServicio + " - Ref: " + referencia;
    return cuenta->retirar(monto, descripcion);
}

bool Banco::guardarDatos(const std::string& rutaArchivo) const {
    // Implementación básica para guardar datos
    // En un sistema real, se utilizaría una base de datos o un formato más robusto
    std::ofstream archivo(rutaArchivo);
    
    if (!archivo.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo para guardar los datos." << std::endl;
        return false;
    }
    
    // Guardar información del banco
    archivo << nombre << "\n";
    archivo << ultimoNumeroCuenta << "\n";
    
    // Guardar número de clientes
    archivo << clientes.size() << "\n";
    
    // Guardar información de cada cliente
    for (const auto& par : clientes) {
        const auto& cliente = par.second;
        
        // Datos básicos del cliente
        archivo << cliente->getCedula() << ";"
                << cliente->getNombres() << ";"
                << cliente->getApellidos() << ";"
                << cliente->getCorreo() << ";"
                << cliente->getTelefono() << ";"
                << cliente->getDireccion() << ";"
                << (cliente->isActivo() ? "1" : "0") << "\n";
        
        // Número de cuentas
        const auto& cuentas = cliente->getCuentas();
        archivo << cuentas.size() << "\n";
        
        // Información de cada cuenta
        for (const auto& cuenta : cuentas) {
            archivo << cuenta->getNumeroCuenta() << ";"
                    << cuenta->getTipo() << ";"
                    << cuenta->getSaldo() << ";"
                    << (cuenta->isActiva() ? "1" : "0") << "\n";
            
            // Guardar transacciones (simplificado)
            const auto& transacciones = cuenta->getHistorialTransacciones();
            archivo << transacciones.size() << "\n";
            
            for (const auto& trans : transacciones) {
                archivo << trans.getTipo() << ";"
                        << trans.getMonto() << ";"
                        << trans.getSaldoResultante() << ";"
                        << trans.getDescripcion() << ";"
                        << trans.getFechaHora() << "\n";
            }
        }
    }
    
    archivo.close();
    std::cout << "Datos guardados exitosamente." << std::endl;
    return true;
}

bool Banco::cargarDatos(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    
    if (!archivo.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo para cargar los datos." << std::endl;
        return false;
    }
    
    // Aquí iría la implementación de carga de datos
    // Por simplicidad, este método no está completamente implementado
    
    archivo.close();
    std::cout << "Datos cargados exitosamente." << std::endl;
    return true;
}