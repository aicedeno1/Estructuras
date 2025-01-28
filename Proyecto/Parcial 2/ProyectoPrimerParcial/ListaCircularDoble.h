/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Realizar una Lista circular doble          *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/



#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include <iostream>
#include <string>
#include <sstream>
#include "Nodo.h"
#include "Libro.h"
#include "Persona.cpp"

using namespace std;

// Clase para la lista circular doblemente enlazada
class ListaCircularDoble {
private:
    Nodo* cabeza = nullptr;
    string archivoLibros = "libros.txt";  // Archivo donde se guardarán los libros
    bool evitarGuardar = false;           // Bandera para controlar el guardado
public:
    // Agregar libro
    void agregarLibro(const Libro& libro);
    // Imprimir todos los libros
    void imprimirLibros();
    // Buscar libro por título
    Nodo* buscarLibro(const string& titulo);
    // Buscar libro por ISBN
    Nodo* buscarLibroPorIsbn(const string& isbn);
    // Buscar autor por ISNI
    Persona buscarAutorPorIsni(const string& isni);
    // Eliminar libro
    void eliminarLibro(const string& titulo);
    // Crear backup
    void crearBackup(const string& nombreArchivo);
    // Restaurar backup
    void restaurarBackup(const string& nombreArchivo);
    // Guardar todos los libros en el archivo
    void guardarLibrosEnArchivo();
    // Cargar los libros desde el archivo
    void cargarLibrosDesdeArchivo();
    // Limpiar la lista
    void limpiarLista();
};

#endif
