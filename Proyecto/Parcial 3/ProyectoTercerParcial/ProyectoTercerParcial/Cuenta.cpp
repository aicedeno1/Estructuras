/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación de la clase Cuenta                        *
 * Autor:                           Diaz Stiven, Cedenio Andres                             *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Cuenta.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Cuenta::Cuenta() : saldo(0.0), activa(true) {}

Cuenta::Cuenta(string numeroCuenta, Cliente titular, double saldoInicial,
               Fecha fechaApertura, TipoCuenta tipo)
    : numeroCuenta(numeroCuenta), titular(titular), saldo(saldoInicial),
      fechaApertura(fechaApertura), tipo(tipo), activa(true) {}

// Getters
string Cuenta::getNumeroCuenta() const { return numeroCuenta; }
Cliente Cuenta::getTitular() const { return titular; }
double Cuenta::getSaldo() const { return saldo; }
Fecha Cuenta::getFechaApertura() const { return fechaApertura; }
TipoCuenta Cuenta::getTipo() const { return tipo; }
bool Cuenta::isActiva() const { return activa; }
std::vector<Transaccion> Cuenta::getHistorialTransacciones() const { return historialTransacciones; }

// Convertir enum TipoCuenta a string
string Cuenta::getTipoString() const
{
    switch (tipo)
    {
    case AHORRO:
        return "Ahorro";
    case CORRIENTE:
        return "Corriente";
    case PLAZO_FIJO:
        return "Plazo Fijo";
    default:
        return "Desconocido";
    }
}

// Setters
void Cuenta::setNumeroCuenta(const string &numeroCuenta) { this->numeroCuenta = numeroCuenta; }
void Cuenta::setTitular(const Cliente &titular) { this->titular = titular; }
void Cuenta::setSaldo(double saldo) { this->saldo = saldo; }
void Cuenta::setFechaApertura(const Fecha &fechaApertura) { this->fechaApertura = fechaApertura; }
void Cuenta::setTipo(TipoCuenta tipo) { this->tipo = tipo; }
void Cuenta::setActiva(bool activa) { this->activa = activa; }

// Métodos de operaciones bancarias
bool Cuenta::depositar(double monto, const string &concepto)
{
    if (monto <= 0)
    {
        return false;
    }

    saldo += monto;

    // Registrar la transacción
    Transaccion transaccion;
    transaccion.setFecha(Fecha::obtenerFechaActual());
    transaccion.setTipo(DEPOSITO);
    transaccion.setMonto(monto);
    transaccion.setConcepto(concepto);
    transaccion.setCuentaOrigen("");
    transaccion.setCuentaDestino(numeroCuenta);

    registrarTransaccion(transaccion);

    return true;
}

bool Cuenta::retirar(double monto, const string &concepto)
{
    if (monto <= 0 || monto > saldo)
    {
        return false;
    }

    saldo -= monto;

    // Registrar la transacción
    Transaccion transaccion;
    transaccion.setFecha(Fecha::obtenerFechaActual());
    transaccion.setTipo(RETIRO);
    transaccion.setMonto(monto);
    transaccion.setConcepto(concepto);
    transaccion.setCuentaOrigen(numeroCuenta);
    transaccion.setCuentaDestino("");

    registrarTransaccion(transaccion);

    return true;
}

bool Cuenta::transferir(Cuenta &destino, double monto, const string &concepto)
{
    if (monto <= 0 || monto > saldo)
    {
        return false;
    }

    saldo -= monto;
    destino.saldo += monto;

    // Registrar la transacción en la cuenta origen
    Transaccion transaccion;
    transaccion.setFecha(Fecha::obtenerFechaActual());
    transaccion.setTipo(TRANSFERENCIA);
    transaccion.setMonto(monto);
    transaccion.setConcepto(concepto);
    transaccion.setCuentaOrigen(numeroCuenta);
    transaccion.setCuentaDestino(destino.getNumeroCuenta());

    registrarTransaccion(transaccion);

    // Registrar la transacción en la cuenta destino
    Transaccion transaccionDestino = transaccion;
    transaccionDestino.setTipo(DEPOSITO);

    destino.registrarTransaccion(transaccionDestino);

    return true;
}

void Cuenta::registrarTransaccion(const Transaccion &transaccion)
{
    historialTransacciones.push_back(transaccion);
}

// Mostrar detalles de la cuenta
void Cuenta::mostrarDetalles() const
{
    cout << "=========================================================" << endl;
    cout << "            DETALLES DE LA CUENTA BANCARIA               " << endl;
    cout << "=========================================================" << endl;
    cout << "Número de cuenta: " << numeroCuenta << endl;
    cout << "Tipo de cuenta: " << getTipoString() << endl;
    cout << "Fecha de apertura: " << fechaApertura.mostrar() << endl;
    cout << "Estado: " << (activa ? "Activa" : "Inactiva") << endl;
    cout << endl;

    cout << "DATOS DEL TITULAR" << endl;
    cout << "---------------------------------------------------------" << endl;
    titular.mostrar();
    cout << endl;

    cout << "INFORMACIÓN FINANCIERA" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Saldo actual: $" << fixed << setprecision(2) << saldo << endl;
    cout << "=========================================================" << endl;
}

string Cuenta::toString() const
{
    stringstream ss;
    ss << numeroCuenta << ";"
       << titular.getCedula() << ";"
       << saldo << ";"
       << fechaApertura.toString() << ";"
       << tipo << ";"
       << (activa ? "1" : "0");
    return ss.str();
}
// Añadir implementaciones de los métodos:
void Cuenta::setEstadoPersonalizado(const std::string &estado)
{
    this->estadoPersonalizado = estado;
}

std::string Cuenta::getEstadoPersonalizado() const
{
    return !estadoPersonalizado.empty() ? estadoPersonalizado : (activa ? "Activa" : "Inactiva");
}

std::string Cuenta::toStringConEstado() const
{
    stringstream ss;
    ss << numeroCuenta << ";"
       << titular.getCedula() << ";"
       << saldo << ";"
       << fechaApertura.toString() << ";"
       << tipo << ";"
       << (activa ? "1" : "0") << ";";

    // Añadir estado personalizado solo si existe
    if (!estadoPersonalizado.empty())
    {
        ss << estadoPersonalizado;
    }

    return ss.str();
}
