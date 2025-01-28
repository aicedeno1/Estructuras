#ifndef LISTACIRCULARMENU_H
#define LISTACIRCULARMENU_H

#include "NodoMenu.h"
#include <string>

class ListaCircularMenu {
private:
    NodoMenu* cabeza;
    int tamano;

public:
    ListaCircularMenu();
    void insertar(string opcion);
    string obtenerOpcion(int indice);
    int getTamano() { return tamano; }
    NodoMenu* getPrimero() { return cabeza; }
};

#endif