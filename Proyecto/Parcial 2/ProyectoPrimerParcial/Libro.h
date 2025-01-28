/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Gestionar Libros                           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef LIBRO_H
#define LIBRO_H

#include <string>
#include <iostream>
#include "Persona.h"
#include "Fecha.h"
using namespace std;

class Libro {
private:
    string titulo;
    string isbn;
    Persona autor;
    Fecha fechaPublicacion;

public:
    Libro(string t = "", string i = "", Persona a = Persona(), Fecha fp = Fecha());
    string getTitulo() const;
    string getIsbn() const;
    Persona getAutor() const;
    Fecha getFechaPublicacion() const;
    void setTitulo(const string& t);
    void setIsbn(const string& i);
    void setAutor(const Persona& a);
    void setFechaPublicacion(const Fecha& fp);
    void mostrar() const;
};

#endif
