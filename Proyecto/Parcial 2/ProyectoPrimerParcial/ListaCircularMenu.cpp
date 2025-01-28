#include "ListaCircularMenu.h"

ListaCircularMenu::ListaCircularMenu() : cabeza(nullptr), tamano(0) {}

void ListaCircularMenu::insertar(string opcion) {
    NodoMenu* nuevo = new NodoMenu(opcion);
    
    if (!cabeza) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        NodoMenu* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        cabeza->anterior = nuevo;
    }
    tamano++;
}

string ListaCircularMenu::obtenerOpcion(int indice) {
    if (!cabeza) return "";
    NodoMenu* actual = cabeza;
    for (int i = 0; i < indice; i++) {
        actual = actual->siguiente;
    }
    return actual->dato;
}