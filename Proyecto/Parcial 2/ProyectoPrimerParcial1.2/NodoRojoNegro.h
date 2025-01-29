/**********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef NODOROJONEGRO_H
#define NODOROJONEGRO_H

#include "Libro.h"

enum Color
{
    ROJO,
    NEGRO
};

class NodoRojoNegro
{
public:
    Libro libro;
    NodoRojoNegro *izquierdo;
    NodoRojoNegro *derecho;
    NodoRojoNegro *padre;
    Color color;

    // Constructor por defecto
    NodoRojoNegro();

    // Constructor con libro
    NodoRojoNegro(const Libro &_libro);

    // Constructor completo
    NodoRojoNegro(const Libro &_libro, NodoRojoNegro *_izq, NodoRojoNegro *_der, NodoRojoNegro *_padre, Color _color);

    // Destructor
    ~NodoRojoNegro();

    // Obtener tío del nodo
    NodoRojoNegro *obtenerTio();

    // Obtener abuelo del nodo
    NodoRojoNegro *obtenerAbuelo();

    // Obtener hermano del nodo
    NodoRojoNegro *obtenerHermano();

    // Verificar si es hijo izquierdo
    bool esHijoIzquierdo();

    // Verificar si es hijo derecho
    bool esHijoDerecho();

    // Verificar si es raíz
    bool esRaiz();

    // Verificar si es hoja
    bool esHoja();
    
};

#endif // NODOROJONEGRO_H