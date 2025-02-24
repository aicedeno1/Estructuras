#include "Transaccion.h"
#include <iostream>
#include <iomanip>
#include <ctime>

Transaccion::Transaccion(std::string tipo, double monto, double saldoResultante, std::string descripcion)
    : tipo(tipo), monto(monto), saldoResultante(saldoResultante), descripcion(descripcion) {
    // Registrar la fecha y hora actual
    fechaHora = time(nullptr);
}

std::string Transaccion::getTipo() const {
    return tipo;
}

double Transaccion::getMonto() const {
    return monto;
}

double Transaccion::getSaldoResultante() const {
    return saldoResultante;
}

std::string Transaccion::getDescripcion() const {
    return descripcion;
}

time_t Transaccion::getFechaHora() const {
    return fechaHora;
}

void Transaccion::mostrar() const {
    // Convertir time_t a estructura tm para formatear la fecha
    struct tm* timeinfo = localtime(&fechaHora);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    
    std::cout << std::left << std::setw(20) << buffer 
              << std::setw(15) << tipo 
              << std::setw(15) << std::fixed << std::setprecision(2) << monto 
              << std::setw(15) << saldoResultante
              << descripcion << std::endl;
}