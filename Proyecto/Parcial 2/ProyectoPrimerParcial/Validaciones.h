/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Validaciones de entrada de datos           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <regex>
#include <iostream>
#include <cctype>
#include "Fecha.h"

using namespace std;

class Validaciones {
public:
    static bool validarFechaPublicacion(const string& fechaPub, const string& fechaNacAutor);
    static bool validarTituloNombre(const string& texto, const string& campo);
    static bool validarTitulo(const string& texto, const string& campo);
    static bool validarFecha(const string& fecha);
    static bool validarIsbn(const string& isbn);
    static bool validarIsni(const string& isni);
    static bool validarTextoNoVacio(const string& texto, const string& campo);
    static bool validarTexto(const string& texto, const string& campo);
    static bool validarIsbn10(const string& isbn);
    static bool validarIsbn13(const string& isbn);
    static int calcularDigitoControlIsbn10(const string& isbn);
    static int calcularDigitoControlIsbn13(const string& isbn);

private:
    static int diasEnMes(int mes, int anio);
    static bool esBisiesto(int anio);
};

#endif // VALIDACIONES_H
