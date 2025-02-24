#ifndef CUENTA_H
#define CUENTA_H

#include <string>
#include <vector>
#include "Transaccion.h"

enum TipoCuenta {
    AHORROS,
    CORRIENTE
};

class Cuenta {
private:
    std::string numeroCuenta;
    double saldo;
    TipoCuenta tipo;
    std::vector<Transaccion> historialTransacciones;
    bool activa;

public:
    // Constructor
    Cuenta(std::string numeroCuenta, double saldoInicial, TipoCuenta tipo);
    
    // Métodos getter
    std::string getNumeroCuenta() const;
    double getSaldo() const;
    TipoCuenta getTipo() const;
    std::string getTipoString() const;
    std::vector<Transaccion> getHistorialTransacciones() const;
    bool isActiva() const;
    
    // Métodos operativos
    bool depositar(double monto, std::string descripcion);
    bool retirar(double monto, std::string descripcion);
    bool transferir(Cuenta& destino, double monto, std::string descripcion);
    void agregarTransaccion(const Transaccion& transaccion);
    void desactivar();
    void activar();
    
    // Métodos para visualizar información
    void mostrarDetalles() const;
    void mostrarHistorialTransacciones() const;
};

#endif