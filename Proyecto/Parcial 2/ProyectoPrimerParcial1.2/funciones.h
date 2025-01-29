/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>
#include "ArbolRojoNegro.h"

// Funciones de utilidad para procesamiento de datos
std::vector<std::string> dividir(const std::string &linea, char delimitador);

// Función para imprimir la cabecera formateada
void imprimirCabecera();

// Funciones de búsqueda
void buscarPorRango(const std::string &rutaArchivo, int anioInicio, int anioFin);
void buscarPorRangoEnArbol(ArbolRojoNegro &arbol, int anioInicio, int anioFin);

// Nueva función para convertir fecha a año
int extraerAnio(const std::string &fecha);

#endif
