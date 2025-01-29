/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Persona.h"
#include <iostream>

Persona::Persona(string n, string isni, Fecha fn) : nombre(n), isni(isni), fechaNacimiento(fn) {}

string Persona::getNombre() const { return nombre; }

string Persona::getIsni() const { return isni; }

Fecha Persona::getFechaNacimiento() const { return fechaNacimiento; }

void Persona::setNombre(const string &n) { nombre = n; }

void Persona::setIsni(const string &isni) { this->isni = isni; }

void Persona::setFechaNacimiento(const Fecha &fn) { fechaNacimiento = fn; }

void Persona::mostrar() const
{
    cout << "Nombre: " << nombre
         << ", ISNI: " << isni
         << ", Fecha de nacimiento: " << fechaNacimiento.mostrar() << endl;
}
