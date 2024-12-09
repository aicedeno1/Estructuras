#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include <iostream>
#include <functional>
#include "Libro.h"  // Asegúrate de incluir las clases necesarias

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
    // Constructor y Destructor
    ListaCircularDoble() : cabeza(nullptr) {}
    ~ListaCircularDoble() { limpiar(); }

    // Métodos principales
    void agregar(const T& elemento);  // Agregar un libro o autor
   bool eliminarPorCodigo(int codigo);
  // Eliminar un libro por su código
    void imprimir(const std::function<void(const T&)>& accion) const;  // Imprimir lista
    void limpiar();  // Limpiar la lista

    // Métodos auxiliares
    template <typename U, typename F>
    bool existe(const U& elemento, F comparador) const;  // Verificar existencia en la lista
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
bool ListaCircularDoble<T>::eliminarPorCodigo(int codigo) {
    if (!cabeza) return false;  // Si la lista está vacía

    Nodo<T>* actual = cabeza;
    do {
        if (actual->dato.obtenerCodigo() == codigo) {  // Comparación con el entero
            // Si es el único nodo
            if (actual->siguiente == actual) {
                delete actual;
                cabeza = nullptr;  // La lista queda vacía
            } else {
                // Si no es el único nodo, actualizamos los punteros
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;

                if (actual == cabeza) {
                    cabeza = actual->siguiente;  // Si eliminamos la cabeza, actualizamos la cabeza
                }
                delete actual;
            }
            return true;  // Libro eliminado
        }
        actual = actual->siguiente;
    } while (actual != cabeza);  // Recorrer hasta la cabeza nuevamente

    return false;  // No se encontró el libro con el código
}



template <typename T>
void ListaCircularDoble<T>::imprimir(const std::function<void(const T&)>& accion) const {
    if (!cabeza) {
        std::cout << "La lista está vacía.\n";
        return;
    }

    Nodo<T>* actual = cabeza;
    do {
        accion(actual->dato);  // Ejecutamos la acción proporcionada
        actual = actual->siguiente;
    } while (actual != cabeza);  // Recorrer hasta el principio
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

    cabeza = nullptr;  // Aseguramos que 'cabeza' sea nulo después de limpiar
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

#endif
