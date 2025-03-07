

#ifndef TRANSACCION_H
#define TRANSACCION_H

#include <string>
#include "Fecha.h"

enum TipoTransaccion
{
    DEPOSITO,
    RETIRO,
    TRANSFERENCIA,
    INTERESES,
    COMISION
};

class Transaccion
{
private:
    Fecha fecha;
    TipoTransaccion tipo;
    double monto;
    std::string concepto;
    std::string cuentaOrigen;
    std::string cuentaDestino;

public:
    // Constructores
    Transaccion();
    Transaccion(Fecha fecha, TipoTransaccion tipo, double monto,
                std::string concepto, std::string cuentaOrigen, std::string cuentaDestino);

    // Getters
    Fecha getFecha() const;
    TipoTransaccion getTipo() const;
    std::string getTipoString() const;
    double getMonto() const;
    std::string getConcepto() const;
    std::string getCuentaOrigen() const;
    std::string getCuentaDestino() const;

    // Setters
    void setFecha(const Fecha &fecha);
    void setTipo(TipoTransaccion tipo);
    void setMonto(double monto);
    void setConcepto(const std::string &concepto);
    void setCuentaOrigen(const std::string &cuentaOrigen);
    void setCuentaDestino(const std::string &cuentaDestino);

    // Método para convertir a cadena
    std::string toString() const;
};

#endif // TRANSACCION_H