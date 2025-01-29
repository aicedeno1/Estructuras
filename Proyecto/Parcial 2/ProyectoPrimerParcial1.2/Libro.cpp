/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include "Libro.h"
#include <iostream>

Libro::Libro(string t, string i, Persona a, Fecha fp)
    : titulo(t), isbn(i), autor(a), fechaPublicacion(fp) {}

string Libro::getTitulo() const { return titulo; }
string Libro::getIsbn() const { return isbn; }
Persona Libro::getAutor() const { return autor; }
Fecha Libro::getFechaPublicacion() const { return fechaPublicacion; }

void Libro::setTitulo(const string &t) { titulo = t; }
void Libro::setIsbn(const string &i) { isbn = i; }
void Libro::setAutor(const Persona &a) { autor = a; }
void Libro::setFechaPublicacion(const Fecha &fp) { fechaPublicacion = fp; }

void Libro::mostrar() const
{
    cout << left << setw(41) << "Título"
         << setw(25) << "Autor"
         << setw(25) << "ISNI"
         << setw(20) << "ISBN"
         << setw(15) << "Publicación"
         << setw(15) << "Nac. Autor" << endl;
    cout << string(140, '-') << endl;
    cout << left << setw(40) << titulo
         << setw(25) << autor.getNombre()
         << setw(25) << autor.getIsni()
         << setw(20) << isbn
         << setw(15) << fechaPublicacion.mostrar()
         << setw(15) << autor.getFechaNacimiento().mostrar() << endl;
}
