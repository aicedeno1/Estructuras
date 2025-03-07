/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Clase Fecha para sistema bancario                        *
 * Autor:                              Diaz Stiven, Cedenio Andres                          *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

class Fecha
{
private:
    int dia;
    int mes;
    int anio;

public:
    // Constructores
    Fecha();
    Fecha(int dia, int mes, int anio);

    // Getters y setters
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    // Métodos de utilidad
    std::string mostrar() const;
    std::string toString() const;

    static Fecha crearDesdeCadena(const std::string &fecha);
    static Fecha obtenerFechaActual();

    // Validaciones
    static bool esBisiesto(int anio);
    static int diasEnMes(int mes, int anio);
    static bool esFechaValida(int dia, int mes, int anio);

    // Sobrecarga de operadores
    bool operator==(const Fecha &otra) const;
    bool operator!=(const Fecha &otra) const;
    bool operator<(const Fecha &otra) const;
    bool operator<=(const Fecha &otra) const;
    bool operator>(const Fecha &otra) const;
    bool operator>=(const Fecha &otra) const;
};

#endif // FECHA_H