#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include <iostream>
#include <functional>
#include "Fecha.h"

template <typename T>
class Nodo {
public:
    T dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(const T& valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaCircularDoble {
private:
    Nodo<T>* cabeza;

public:
    ListaCircularDoble() : cabeza(nullptr) {}
    ~ListaCircularDoble() { limpiar(); }

    void agregar(const T& elemento);
    bool eliminar(const std::string& criterio, bool porCodigo);
    
    template <typename U, typename F>
    bool existe(const U& elemento, F comparador) const;
    
    void imprimir(const std::function<void(const T&)>& accion) const;
    void limpiar();
};

template <typename T>
void ListaCircularDoble<T>::agregar(const T& elemento) {
    Nodo<T>* nuevoNodo = new Nodo<T>(elemento);
    if (!cabeza) {
        cabeza = nuevoNodo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        Nodo<T>* ultimo = cabeza->anterior;
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
        nuevoNodo->siguiente = cabeza;
        cabeza->anterior = nuevoNodo;
    }
}

template <typename T>
bool ListaCircularDoble<T>::eliminar(const std::string& criterio, bool porCodigo) {
    if (!cabeza) return false;

    Nodo<T>* actual = cabeza;
    Nodo<T>* anterior = nullptr;

    do {
        if (porCodigo && actual->dato.obtenerCodigo() == criterio) {
            if (anterior) {
                anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = anterior;
            } else {
                cabeza = actual->siguiente;
                cabeza->anterior = actual->anterior;
            }
            delete actual;
            return true;
        } else if (!porCodigo && actual->dato.obtenerInformacion().find(criterio) != std::string::npos) {
            if (anterior) {
                anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = anterior;
            } else {
                cabeza = actual->siguiente;
                cabeza->anterior = actual->anterior;
            }
            delete actual;
            return true;
        }

        anterior = actual;
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

template <typename T>
template <typename U, typename F>
bool ListaCircularDoble<T>::existe(const U& elemento, F comparador) const {
    Nodo<T>* actual = cabeza;
    if (!actual) return false;

    do {
        if (comparador(actual->dato, elemento)) {
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

template <typename T>
void ListaCircularDoble<T>::imprimir(const std::function<void(const T&)>& accion) const {
    Nodo<T>* actual = cabeza;
    if (!actual) return;

    do {
        accion(actual->dato);
        actual = actual->siguiente;
    } while (actual != cabeza);
}

template <typename T>
void ListaCircularDoble<T>::limpiar() {
    if (!cabeza) return;

    Nodo<T>* actual = cabeza;
    do {
        Nodo<T>* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);

    cabeza = nullptr;
}

#endif
