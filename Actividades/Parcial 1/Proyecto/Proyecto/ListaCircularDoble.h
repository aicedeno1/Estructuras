#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include <iostream>
#include <functional>

// Clase Nodo
template <typename T>
class Nodo {
public:
    T dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(const T& valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

// Clase ListaCircularDoble
template <typename T>
class ListaCircularDoble {
private:
    Nodo<T>* cabeza;

public:
    ListaCircularDoble() : cabeza(nullptr) {}
    ~ListaCircularDoble() { limpiar(); }

    void agregar(const T& elemento);
    
    template <typename U, typename F>
    bool existe(const U& elemento, F comparador) const;
    
    void imprimir(const std::function<void(const T&)>& accion) const;
    void limpiar();

    // Otros métodos según necesidad
};

// Implementaciones de los métodos

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
template <typename U, typename F>
bool ListaCircularDoble<T>::existe(const U& elemento, F comparador) const {
    if (!cabeza) return false;

    Nodo<T>* actual = cabeza;
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
    if (!cabeza) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    Nodo<T>* actual = cabeza;
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

    cabeza = nullptr;  // Aseguramos que 'cabeza' sea nulo después de limpiar la lista
}

#endif
