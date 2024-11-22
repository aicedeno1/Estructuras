/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Implementación de Nodo para lista simple            *
 * Autor:                          Josue Chango, Adonny Calero, Eduardo Altamirano     *
 * Fecha de creación:              18/11/2024                                          *
 * Fecha de modificación:          18/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC:                            1978                                                *
 **************************************************************************************/
#pragma once

#include <iostream> // Para entrada y salida estándar

template <typename T>
class Nodo {
private:
    T dato;            // Dato que almacena el nodo
    Nodo* siguiente;   // Puntero al siguiente nodo de la lista

public:
    // Constructor: inicializa el nodo con un dato y un puntero siguiente nulo
    Nodo(T _dato) : dato(_dato), siguiente(nullptr) {}

    // Métodos para acceder y modificar el dato
    T& getDato() { return dato; }                          // Devuelve una referencia al dato
    void setDato(const T& _dato) { dato = _dato; }         // Asigna un nuevo valor al dato

    // Métodos para acceder y modificar el puntero siguiente
    Nodo* getSiguiente() { return siguiente; }             // Devuelve el puntero al siguiente nodo
    void setSiguiente(Nodo* _siguiente) { siguiente = _siguiente; } // Asigna el puntero siguiente
};


