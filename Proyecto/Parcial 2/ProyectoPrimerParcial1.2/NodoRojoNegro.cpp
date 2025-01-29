/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *            
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "NodoRojoNegro.h"

// Constructor por defecto
NodoRojoNegro::NodoRojoNegro() : 
    izquierdo(nullptr), 
    derecho(nullptr), 
    padre(nullptr), 
    color(ROJO) {}

// Constructor con libro
NodoRojoNegro::NodoRojoNegro(const Libro& _libro) : 
    libro(_libro), 
    izquierdo(nullptr), 
    derecho(nullptr), 
    padre(nullptr), 
    color(ROJO) {}

// Constructor completo
NodoRojoNegro::NodoRojoNegro(const Libro& _libro, NodoRojoNegro* _izq, NodoRojoNegro* _der, 
                             NodoRojoNegro* _padre, Color _color) :
    libro(_libro),
    izquierdo(_izq),
    derecho(_der),
    padre(_padre),
    color(_color) {}

// Destructor
NodoRojoNegro::~NodoRojoNegro() {
    // No eliminamos los nodos hijos aquí para evitar eliminación en cascada no deseada
}

// Obtener tío del nodo
NodoRojoNegro* NodoRojoNegro::obtenerTio() {
    NodoRojoNegro* abuelo = obtenerAbuelo();
    if (!abuelo) return nullptr;

    if (padre == abuelo->izquierdo)
        return abuelo->derecho;
    else
        return abuelo->izquierdo;
}

// Obtener abuelo del nodo
NodoRojoNegro* NodoRojoNegro::obtenerAbuelo() {
    if (padre)
        return padre->padre;
    return nullptr;
}

// Obtener hermano del nodo
NodoRojoNegro* NodoRojoNegro::obtenerHermano() {
    if (!padre) return nullptr;
    
    if (this == padre->izquierdo)
        return padre->derecho;
    else
        return padre->izquierdo;
}

// Verificar si es hijo izquierdo
bool NodoRojoNegro::esHijoIzquierdo() {
    return padre && this == padre->izquierdo;
}

// Verificar si es hijo derecho
bool NodoRojoNegro::esHijoDerecho() {
    return padre && this == padre->derecho;
}

// Verificar si es raíz
bool NodoRojoNegro::esRaiz() {
    return padre == nullptr;
}

// Verificar si es hoja
bool NodoRojoNegro::esHoja() {
    return izquierdo == nullptr && derecho == nullptr;
}