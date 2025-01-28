/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Gestionar Fechas                           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> // Para std::setw y std::setfill
using namespace std;

// Clase para representar una fecha
class Fecha {
private:
    int dia;
    int mes;
    int anio;

    // Método privado para validar si el año es bisiesto
    static bool esBisiesto(int anio) {
        return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    }

    // Método privado para obtener los días máximos de un mes
    static int diasEnMes(int mes, int anio) {
        switch (mes) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                return 31;
            case 4: case 6: case 9: case 11:
                return 30;
            case 2:
                return esBisiesto(anio) ? 29 : 28;
            default:
                return 0;
        }
    }

public:
// Constructor por defectostring toString() const {
    string toString() const {
        stringstream ss;
        ss << setw(2) << setfill('0') << dia << "-"
           << setw(2) << setfill('0') << mes << "-"
           << anio;
        return ss.str();
    }
    // Método para comparar si una fecha es anterior a otra
    bool esAnterior(const Fecha& otra) const {
        return anio < otra.anio;
    }
    // Constructor por defecto y parametrizado
    Fecha(int d = 1, int m = 1, int a = 1900) {
        if (!esFechaValida(d, m, a)) {
            throw invalid_argument("Fecha invalida");
        }
        dia = d;
        mes = m;
        anio = a;
    }

    // Métodos para acceder a los atributos
    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAnio() const { return anio; }

    // Métodos para modificar los atributos
    void setDia(int d) {
        if (!esFechaValida(d, mes, anio)) {
            throw invalid_argument("Dia invalido");
        }
        dia = d;
    }

    void setMes(int m) {
        if (!esFechaValida(dia, m, anio)) {
            throw invalid_argument("Mes invalido");
        }
        mes = m;
    }

    void setAnio(int a) {
        if (!esFechaValida(dia, mes, a)) {
            throw invalid_argument("Año invalido");
        }
        anio = a;
    }

    // Método para mostrar la fecha
    string mostrar() const {
        stringstream ss;
        ss << setw(2) << setfill('0') << dia << "/"
        << setw(2) << setfill('0') << mes << "/"
        << anio;
        return ss.str();
    }

    // Método para validar si una fecha es válida
    static bool esFechaValida(int dia, int mes, int anio) {
        if (anio < 1 || mes < 1 || mes > 12) {
            return false;
        }
        int diasMax = diasEnMes(mes, anio);
        return dia >= 1 && dia <= diasMax;
    }

    // Método para crear un objeto Fecha desde una cadena con formato "DD-MM-YYYY"
    static Fecha crearDesdeCadena(const string& fechaStr) {
        int d, m, a;
        char separador1, separador2;
        stringstream ss(fechaStr);

        ss >> d >> separador1 >> m >> separador2 >> a;

        if ((separador1 != '-' && separador1 != '/') || (separador2 != '-' && separador2 != '/') || !esFechaValida(d, m, a)) {
        throw invalid_argument("Formato o fecha invalida: " + fechaStr);
    }

        return Fecha(d, m, a);
    }
};

#endif
