#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include <iostream>
#include <functional>
#include <vector>
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
    int tamano;  // Variable que almacena el tamaño actual de la lista

public:
    // Constructor y Destructor
    ListaCircularDoble() : cabeza(nullptr), tamano(0) {}
    ~ListaCircularDoble() { limpiar(); }

    // Métodos principales
    void agregar(const T& elemento);  // Agregar un libro o autor
    bool eliminarPorCodigo(const std::string& codigo);  // Eliminar un libro por su código
    void imprimir(const std::function<void(const T&)>& accion) const;  // Imprimir lista
    void limpiar();  // Limpiar la lista
    void ordenarShell(const std::function<bool(const T&, const T&)>& comparador);
    int obtenerTamano() const;  // Obtener el tamaño de la lista

    // Métodos auxiliares
    template <typename U, typename F>
    bool existe(const U& elemento, F comparador) const;  // Verificar existencia en la lista
};

// Implementaciones de los métodos

template <typename T>
void ListaCircularDoble<T>::agregar(const T& elemento) {
    Nodo<T>* nuevoNodo = new Nodo<T>(elemento);
    std::cout << "Agregando nuevo elemento a la lista" << std::endl;  // Debug

    if (!cabeza) {
        std::cout << "Lista vacía, creando primer nodo" << std::endl;  // Debug
        cabeza = nuevoNodo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        std::cout << "Agregando nodo a lista existente" << std::endl;  // Debug
        Nodo<T>* ultimo = cabeza->anterior;
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
        nuevoNodo->siguiente = cabeza;
        cabeza->anterior = nuevoNodo;
    }

    tamano++;  // Aumentamos el tamaño de la lista
}

template <typename T>
bool ListaCircularDoble<T>::eliminarPorCodigo(const std::string& codigo) {
    if (!cabeza) return false;  // Si la lista está vacía

    Nodo<T>* actual = cabeza;
    do {
        if (actual->dato.obtenerCodigo() == codigo) {  // Si el código coincide
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
            tamano--;  // Disminuimos el tamaño de la lista
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
    tamano = 0;  // Reseteamos el tamaño
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
void ListaCircularDoble<T>::ordenarShell(const std::function<bool(const T&, const T&)>& comparador) {
    if (!cabeza || tamano <= 1) return; // Si la lista está vacía o tiene un solo elemento, no hay nada que ordenar

    // Convertir la lista a un vector temporal
    std::vector<Nodo<T>*> nodos;
    Nodo<T>* actual = cabeza;
    do {
        nodos.push_back(actual);
        actual = actual->siguiente;
    } while (actual != cabeza);

    // Aplicar ShellSort al vector
    int n = nodos.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Nodo<T>* temp = nodos[i];
            int j;
            for (j = i; j >= gap && comparador(temp->dato, nodos[j - gap]->dato); j -= gap) {
                nodos[j] = nodos[j - gap];
            }
            nodos[j] = temp;
        }
    }

    // Reconstruir la lista desde el vector ordenado
    for (size_t i = 0; i < nodos.size(); ++i) {
        nodos[i]->siguiente = nodos[(i + 1) % n];
        nodos[i]->anterior = nodos[(i + n - 1) % n];
    }
    cabeza = nodos[0]; // Actualizar la cabeza
}

template <typename T>
int ListaCircularDoble<T>::obtenerTamano() const {
    return tamano;  // Retornar el tamaño almacenado
}

#endif
