

#ifndef CUENTA_H
#define CUENTA_H

#include <string>
#include "Fecha.h"
#include "Cliente.h"
#include <vector>
#include "Transaccion.h"

enum TipoCuenta
{
    AHORRO,
    CORRIENTE,
    PLAZO_FIJO
};

class Cuenta
{
private:
    std::string numeroCuenta;
    Cliente titular;
    double saldo;
    Fecha fechaApertura;
    TipoCuenta tipo;
    std::vector<Transaccion> historialTransacciones;
    std::string estadoPersonalizado;
    bool activa;

public:
    // Constructores
    Cuenta();
    Cuenta(std::string numeroCuenta, Cliente titular, double saldoInicial,
           Fecha fechaApertura, TipoCuenta tipo);

    // Getters y setters
    std::string getNumeroCuenta() const;
    Cliente getTitular() const;
    double getSaldo() const;
    Fecha getFechaApertura() const;
    TipoCuenta getTipo() const;
    std::string getTipoString() const;
    bool isActiva() const;
    std::vector<Transaccion> getHistorialTransacciones() const;

    void setNumeroCuenta(const std::string &numeroCuenta);
    void setTitular(const Cliente &titular);
    void setSaldo(double saldo);
    void setFechaApertura(const Fecha &fechaApertura);
    void setTipo(TipoCuenta tipo);
    void setActiva(bool activa);

    // Métodos de operaciones bancarias
    bool depositar(double monto, const std::string &concepto);
    bool retirar(double monto, const std::string &concepto);
    bool transferir(Cuenta &destino, double monto, const std::string &concepto);
    void registrarTransaccion(const Transaccion &transaccion);

    // Método para mostrar detalles de la cuenta
    void mostrarDetalles() const;
    std::string toString() const;
    void setEstadoPersonalizado(const std::string &estado);
    std::string getEstadoPersonalizado() const;
    std::string toStringConEstado() const;
};

#endif // CUENTA_H