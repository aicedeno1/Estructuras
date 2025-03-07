/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación de la clase Fecha                         *
 * Autor:                           Diaz Stiven, Cedenio Andres                             *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Fecha.h"
#include <stdexcept>
#include <iostream>

using namespace std;

Fecha::Fecha() : dia(1), mes(1), anio(2025) {}

Fecha::Fecha(int dia, int mes, int anio)
{
    if (!esFechaValida(dia, mes, anio))
    {
        throw invalid_argument("Fecha inválida");
    }
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}

// Getters
int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

// Setters
void Fecha::setDia(int dia)
{
    if (!esFechaValida(dia, mes, anio))
    {
        throw invalid_argument("Día inválido");
    }
    this->dia = dia;
}

void Fecha::setMes(int mes)
{
    if (!esFechaValida(dia, mes, anio))
    {
        throw invalid_argument("Mes inválido");
    }
    this->mes = mes;
}

void Fecha::setAnio(int anio)
{
    if (!esFechaValida(dia, mes, anio))
    {
        throw invalid_argument("Año inválido");
    }
    this->anio = anio;
}

// Mostrar fecha en formato DD/MM/YYYY
string Fecha::mostrar() const
{
    stringstream ss;
    ss << setw(2) << setfill('0') << dia << "/"
       << setw(2) << setfill('0') << mes << "/"
       << anio;
    return ss.str();
}

// Convertir fecha a string con formato DD-MM-YYYY para almacenamiento
string Fecha::toString() const
{
    stringstream ss;
    ss << setw(2) << setfill('0') << dia << "-"
       << setw(2) << setfill('0') << mes << "-"
       << anio;
    return ss.str();
}

// Crear objeto Fecha a partir de una cadena con formato DD-MM-YYYY
Fecha Fecha::crearDesdeCadena(const string &fecha)
{
    int d, m, a;
    char separador1, separador2;

    stringstream ss(fecha);
    ss >> d >> separador1 >> m >> separador2 >> a;

    if (separador1 != '-' || separador2 != '-' || !esFechaValida(d, m, a))
    {
        throw invalid_argument("Formato o fecha inválida: " + fecha);
    }

    return Fecha(d, m, a);
}

// Obtener la fecha actual del sistema
Fecha Fecha::obtenerFechaActual()
{
    time_t t = time(nullptr);
    tm *ahora = localtime(&t);

    return Fecha(ahora->tm_mday, ahora->tm_mon + 1, ahora->tm_year + 1900);
}

// Comprobar si un año es bisiesto
bool Fecha::esBisiesto(int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

// Obtener el número de días en un mes
int Fecha::diasEnMes(int mes, int anio)
{
    switch (mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return esBisiesto(anio) ? 29 : 28;
    default:
        return 0;
    }
}

// Validar si una fecha es correcta
bool Fecha::esFechaValida(int dia, int mes, int anio)
{
    if (anio < 1 || mes < 1 || mes > 12)
    {
        return false;
    }

    return dia >= 1 && dia <= diasEnMes(mes, anio);
}

// Sobrecarga de operadores
bool Fecha::operator==(const Fecha &otra) const
{
    return (dia == otra.dia && mes == otra.mes && anio == otra.anio);
}

bool Fecha::operator!=(const Fecha &otra) const
{
    return !(*this == otra);
}

bool Fecha::operator<(const Fecha &otra) const
{
    if (anio < otra.anio)
        return true;
    if (anio > otra.anio)
        return false;

    if (mes < otra.mes)
        return true;
    if (mes > otra.mes)
        return false;

    return dia < otra.dia;
}

bool Fecha::operator<=(const Fecha &otra) const
{
    return (*this < otra || *this == otra);
}

bool Fecha::operator>(const Fecha &otra) const
{
    return !(*this <= otra);
}

bool Fecha::operator>=(const Fecha &otra) const
{
    return !(*this < otra);
}