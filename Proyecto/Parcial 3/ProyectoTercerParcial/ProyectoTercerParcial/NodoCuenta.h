/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Nodo para Árbol Rojo-Negro de cuentas                    *
 * Autor:                          Diaz Stiven, Cedenio Andres                              *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef NODO_CUENTA_H
#define NODO_CUENTA_H

#include "Cuenta.h"

enum Color
{
    ROJO,
    NEGRO
};

class NodoCuenta
{
public:
    Cuenta cuenta;
    NodoCuenta *izquierdo;
    NodoCuenta *derecho;
    NodoCuenta *padre;
    Color color;

    // Constructores
    NodoCuenta();
    NodoCuenta(const Cuenta &cuenta);
    NodoCuenta(const Cuenta &cuenta, NodoCuenta *izq, NodoCuenta *der,
               NodoCuenta *padre, Color color);

    // Destructor
    ~NodoCuenta();

    // Métodos para obtener relaciones familiares
    NodoCuenta *obtenerTio();
    NodoCuenta *obtenerAbuelo();
    NodoCuenta *obtenerHermano();

    // Métodos para verificar posición
    bool esHijoIzquierdo();
    bool esHijoDerecho();
    bool esRaiz();
    bool esHoja();
};

#endif // NODO_CUENTA_H