#ifndef TRANSACCION_H
#define TRANSACCION_H

#include <string>
#include <ctime>

class Transaccion {
private:
    std::string tipo;         // DEPOSITO, RETIRO, TRANSFERENCIA, etc.
    double monto;             // Positivo para depósitos, negativo para retiros
    double saldoResultante;   // Saldo después de la transacción
    std::string descripcion;  // Descripción de la transacción
    time_t fechaHora;         // Fecha y hora de la transacción

public:
    // Constructor
    Transaccion(std::string tipo, double monto, double saldoResultante, std::string descripcion);
    
    // Métodos getter
    std::string getTipo() const;
    double getMonto() const;
    double getSaldoResultante() const;
    std::string getDescripcion() const;
    time_t getFechaHora() const;
    
    // Método para mostrar los detalles de la transacción
    void mostrar() const;
};

#endif