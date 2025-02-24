#include "Cuenta.h"
#include <iostream>
#include <ctime>
#include <iomanip>

Cuenta::Cuenta(std::string numeroCuenta, double saldoInicial, TipoCuenta tipo)
    : numeroCuenta(numeroCuenta), saldo(saldoInicial), tipo(tipo), activa(true) {
    // Registrar transacción inicial
    if (saldoInicial > 0) {
        Transaccion transInicial("APERTURA", saldoInicial, saldo, "Depósito inicial");
        historialTransacciones.push_back(transInicial);
    }
}

std::string Cuenta::getNumeroCuenta() const {
    return numeroCuenta;
}

double Cuenta::getSaldo() const {
    return saldo;
}

TipoCuenta Cuenta::getTipo() const {
    return tipo;
}

std::string Cuenta::getTipoString() const {
    return (tipo == AHORROS) ? "Ahorros" : "Corriente";
}

std::vector<Transaccion> Cuenta::getHistorialTransacciones() const {
    return historialTransacciones;
}

bool Cuenta::isActiva() const {
    return activa;
}

bool Cuenta::depositar(double monto, std::string descripcion) {
    if (!activa) {
        std::cout << "Error: La cuenta está inactiva." << std::endl;
        return false;
    }
    
    if (monto <= 0) {
        std::cout << "Error: El monto debe ser positivo." << std::endl;
        return false;
    }
    
    saldo += monto;
    Transaccion trans("DEPOSITO", monto, saldo, descripcion);
    historialTransacciones.push_back(trans);
    return true;
}

bool Cuenta::retirar(double monto, std::string descripcion) {
    if (!activa) {
        std::cout << "Error: La cuenta está inactiva." << std::endl;
        return false;
    }
    
    if (monto <= 0) {
        std::cout << "Error: El monto debe ser positivo." << std::endl;
        return false;
    }
    
    if (tipo == AHORROS && saldo - monto < 0) {
        std::cout << "Error: Fondos insuficientes en cuenta de ahorros." << std::endl;
        return false;
    }
    
    // Para cuentas corrientes, se puede permitir sobregiro hasta cierto límite
    if (tipo == CORRIENTE && saldo - monto < -500) { // Límite de sobregiro de $500
        std::cout << "Error: Se excede el límite de sobregiro." << std::endl;
        return false;
    }
    
    saldo -= monto;
    Transaccion trans("RETIRO", -monto, saldo, descripcion);
    historialTransacciones.push_back(trans);
    return true;
}

bool Cuenta::transferir(Cuenta& destino, double monto, std::string descripcion) {
    if (!activa) {
        std::cout << "Error: La cuenta origen está inactiva." << std::endl;
        return false;
    }
    
    if (!destino.isActiva()) {
        std::cout << "Error: La cuenta destino está inactiva." << std::endl;
        return false;
    }
    
    if (retirar(monto, "Transferencia a cuenta " + destino.getNumeroCuenta())) {
        destino.depositar(monto, "Transferencia desde cuenta " + numeroCuenta);
        return true;
    }
    
    return false;
}

void Cuenta::agregarTransaccion(const Transaccion& transaccion) {
    historialTransacciones.push_back(transaccion);
}

void Cuenta::desactivar() {
    activa = false;
}

void Cuenta::activar() {
    activa = true;
}

void Cuenta::mostrarDetalles() const {
    std::cout << "Número de cuenta: " << numeroCuenta << std::endl;
    std::cout << "Tipo: " << getTipoString() << std::endl;
    std::cout << "Saldo actual: $" << std::fixed << std::setprecision(2) << saldo << std::endl;
    std::cout << "Estado: " << (activa ? "Activa" : "Inactiva") << std::endl;
}

void Cuenta::mostrarHistorialTransacciones() const {
    std::cout << "===== HISTORIAL DE TRANSACCIONES =====" << std::endl;
    std::cout << std::left << std::setw(20) << "FECHA" 
              << std::setw(15) << "TIPO" 
              << std::setw(15) << "MONTO" 
              << std::setw(15) << "SALDO"
              << "DESCRIPCIÓN" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (const auto& trans : historialTransacciones) {
        trans.mostrar();
    }
}