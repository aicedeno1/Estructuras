/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación clase Transaccion                         *
 * Autor:                        Diaz Stiven, Cedenio Andres                                *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Transaccion.h"
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor por defecto
Transaccion::Transaccion() : tipo(DEPOSITO), monto(0.0) {}

// Constructor con parámetros
Transaccion::Transaccion(Fecha fecha, TipoTransaccion tipo, double monto,
                         string concepto, string cuentaOrigen, string cuentaDestino)
    : fecha(fecha), tipo(tipo), monto(monto),
      concepto(concepto), cuentaOrigen(cuentaOrigen), cuentaDestino(cuentaDestino) {}

// Getters
Fecha Transaccion::getFecha() const
{
    return fecha;
}

TipoTransaccion Transaccion::getTipo() const
{
    return tipo;
}

string Transaccion::getTipoString() const
{
    switch (tipo)
    {
    case DEPOSITO:
        return "Depósito";
    case RETIRO:
        return "Retiro";
    case TRANSFERENCIA:
        return "Transferencia";
    case INTERESES:
        return "Intereses";
    case COMISION:
        return "Comisión";
    default:
        return "Desconocido";
    }
}

double Transaccion::getMonto() const
{
    return monto;
}

string Transaccion::getConcepto() const
{
    return concepto;
}

string Transaccion::getCuentaOrigen() const
{
    return cuentaOrigen;
}

string Transaccion::getCuentaDestino() const
{
    return cuentaDestino;
}

// Setters
void Transaccion::setFecha(const Fecha &fecha)
{
    this->fecha = fecha;
}

void Transaccion::setTipo(TipoTransaccion tipo)
{
    this->tipo = tipo;
}

void Transaccion::setMonto(double monto)
{
    this->monto = monto;
}

void Transaccion::setConcepto(const string &concepto)
{
    this->concepto = concepto;
}

void Transaccion::setCuentaOrigen(const string &cuentaOrigen)
{
    this->cuentaOrigen = cuentaOrigen;
}

void Transaccion::setCuentaDestino(const string &cuentaDestino)
{
    this->cuentaDestino = cuentaDestino;
}

// Método para convertir a cadena
string Transaccion::toString() const
{
    stringstream ss;
    ss << fecha.toString() << ";"
       << tipo << ";"
       << fixed << setprecision(2) << monto << ";"
       << concepto << ";"
       << cuentaOrigen << ";"
       << cuentaDestino;
    return ss.str();
}