/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Clase persona                              *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include "Fecha.h"

using namespace std;

class Persona {
private:
    string nombre;
    string isni; // ISNI añadido
    Fecha fechaNacimiento;

public:
    Persona(string n = "", string isni = "", Fecha fn = Fecha());
    string getNombre() const;
    string getIsni() const; // Getter para ISNI
    Fecha getFechaNacimiento() const;
    void setNombre(const string& n);
    void setIsni(const string& isni); // Setter para ISNI
    void setFechaNacimiento(const Fecha& fn);
    void mostrar() const;
};


#endif // PERSONA_H
