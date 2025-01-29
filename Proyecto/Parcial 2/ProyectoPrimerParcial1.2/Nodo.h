/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef NODOMENU_H
#define NODOMENU_H

#include <string>

class NodoMenu
{
public:
    std::string dato;
    NodoMenu *siguiente;
    NodoMenu *anterior;

    NodoMenu(std::string valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

#endif // NODOMENU_H
