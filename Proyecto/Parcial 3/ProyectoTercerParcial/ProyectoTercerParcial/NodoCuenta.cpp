/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol de cuentas                *
 * Autor:                          Diaz Stiven, Cedenio Andres                              *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "NodoCuenta.h"

// Constructor por defecto
NodoCuenta::NodoCuenta() : 
    izquierdo(nullptr), 
    derecho(nullptr), 
    padre(nullptr), 
    color(ROJO) {}

// Constructor con cuenta
NodoCuenta::NodoCuenta(const Cuenta& _cuenta) : 
    cuenta(_cuenta), 
    izquierdo(nullptr), 
    derecho(nullptr), 
    padre(nullptr), 
    color(ROJO) {}

// Constructor completo
NodoCuenta::NodoCuenta(const Cuenta& _cuenta, NodoCuenta* _izq, NodoCuenta* _der, 
                     NodoCuenta* _padre, Color _color) :
    cuenta(_cuenta),
    izquierdo(_izq),
    derecho(_der),
    padre(_padre),
    color(_color) {}

// Destructor
NodoCuenta::~NodoCuenta() {
    // No eliminamos los nodos hijos aquí para evitar eliminación en cascada no deseada
}

// Obtener tío del nodo
NodoCuenta* NodoCuenta::obtenerTio() {
    NodoCuenta* abuelo = obtenerAbuelo();
    if (!abuelo) return nullptr;

    if (padre == abuelo->izquierdo)
        return abuelo->derecho;
    else
        return abuelo->izquierdo;
}

// Obtener abuelo del nodo
NodoCuenta* NodoCuenta::obtenerAbuelo() {
    if (padre)
        return padre->padre;
    return nullptr;
}

// Obtener hermano del nodo
NodoCuenta* NodoCuenta::obtenerHermano() {
    if (!padre) return nullptr;
    
    if (this == padre->izquierdo)
        return padre->derecho;
    else
        return padre->izquierdo;
}

// Verificar si es hijo izquierdo
bool NodoCuenta::esHijoIzquierdo() {
    return padre && this == padre->izquierdo;
}

// Verificar si es hijo derecho
bool NodoCuenta::esHijoDerecho() {
    return padre && this == padre->derecho;
}

// Verificar si es raíz
bool NodoCuenta::esRaiz() {
    return padre == nullptr;
}

// Verificar si es hoja
bool NodoCuenta::esHoja() {
    return izquierdo == nullptr && derecho == nullptr;
}