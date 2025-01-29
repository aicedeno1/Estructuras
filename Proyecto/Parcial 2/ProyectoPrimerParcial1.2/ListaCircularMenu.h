/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef LISTACIRCULARMENU_H
#define LISTACIRCULARMENU_H

#include "NodoMenu.h"
#include <string>

class ListaCircularMenu
{
private:
    NodoMenu *cabeza;
    int tamano;

public:
    ListaCircularMenu();
    void insertar(std::string opcion);
    std::string obtenerOpcion(int indice);
    int getTamano() const { return tamano; }
    NodoMenu *getPrimero() const { return cabeza; }
};

#endif // LISTACIRCULARMENU_H