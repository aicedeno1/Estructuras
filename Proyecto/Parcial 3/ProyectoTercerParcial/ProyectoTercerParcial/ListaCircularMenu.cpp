/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación de Lista Circular para menú               *
 * Autor:                         Diaz Stiven, Cedenio Andres                               *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "ListaCircularMenu.h"

// Constructor
ListaCircularMenu::ListaCircularMenu() : cabeza(nullptr), tamano(0) {}

// Destructor
ListaCircularMenu::~ListaCircularMenu()
{
    vaciar();
}

// Insertar una nueva opción en la lista
void ListaCircularMenu::insertar(std::string opcion)
{
    NodoMenu *nuevo = new NodoMenu(opcion);

    if (!cabeza)
    {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    }
    else
    {
        NodoMenu *ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        cabeza->anterior = nuevo;
    }
    tamano++;
}

// Obtener una opción por su índice
std::string ListaCircularMenu::obtenerOpcion(int indice)
{
    if (!cabeza)
        return "";

    // Asegurarse de que el índice sea válido
    indice = indice % tamano;
    if (indice < 0)
        indice += tamano;

    NodoMenu *actual = cabeza;
    for (int i = 0; i < indice; i++)
    {
        actual = actual->siguiente;
    }
    return actual->dato;
}

// Obtener el primer nodo
NodoMenu *ListaCircularMenu::getPrimero() const
{
    return cabeza;
}

// Obtener el tamaño de la lista
int ListaCircularMenu::getTamano() const
{
    return tamano;
}

// Vaciar la lista (liberar memoria)
void ListaCircularMenu::vaciar()
{
    if (!cabeza)
        return;

    NodoMenu *actual = cabeza;
    NodoMenu *siguiente;

    do
    {
        siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);

    cabeza = nullptr;
    tamano = 0;
}