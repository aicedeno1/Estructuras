/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Fecha
{
private:
    int dia;
    int mes;
    int anio;

    // Métodos privados para validar si el año es bisiesto
    static bool esBisiesto(int anio);
    static int diasEnMes(int mes, int anio);

public:
    // Constructor
    Fecha(int d = 1, int m = 1, int a = 1900);

    // Getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // Setters
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    // Método para mostrar la fecha
    string mostrar() const;
    string toString() const;
    bool esAnterior(const Fecha &otra) const;

    // Método para validar si una fecha es válida
    static bool esFechaValida(int dia, int mes, int anio);

    // Método para crear un objeto Fecha desde una cadena con formato "DD-MM-YYYY"
    static Fecha crearDesdeCadena(const string &fechaStr);
};

#endif
