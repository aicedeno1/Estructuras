#ifndef ARBOLROJONEGRO_H
#define ARBOLROJONEGRO_H

#include "NodoRojoNegro.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <set>

using namespace std;

class ArbolRojoNegro
{
private:
    NodoRojoNegro *raiz;
    string archivoLibros = "libros.txt";
    bool evitarGuardar = false;
    vector<Persona> obtenerAutoresOrdenados() const;
    int busquedaBinariaAutor(const vector<Persona> &autores, const string &nombreAutor) const;

    // Función auxiliar para normalizar strings (una sola implementación)
    string normalizarString(const string &str) const {
        string normalizado = str;
        
        // Convertir a minúsculas
        transform(normalizado.begin(), normalizado.end(), normalizado.begin(), 
                 [](unsigned char c) { return tolower(c); });
        
        // Eliminar espacios extras al inicio y final
        if (!normalizado.empty()) {
            size_t inicio = normalizado.find_first_not_of(" \t");
            if (inicio != string::npos) {
                size_t fin = normalizado.find_last_not_of(" \t");
                normalizado = normalizado.substr(inicio, fin - inicio + 1);
            } else {
                normalizado.clear(); // La cadena solo contiene espacios
            }
        }
        return normalizado;
    }

    // Métodos privados de balanceo
    void rotarIzquierda(NodoRojoNegro *nodo);
    void rotarDerecha(NodoRojoNegro *nodo);
    void balancearInsercion(NodoRojoNegro *nodo);
    void balancearEliminacion(NodoRojoNegro *nodo);

    // Métodos auxiliares privados
    NodoRojoNegro *encontrarSucesor(NodoRojoNegro *nodo);
    NodoRojoNegro *encontrarMinimo(NodoRojoNegro *nodo);
    void liberarMemoria(NodoRojoNegro *nodo);
    void inorden(NodoRojoNegro *nodo, vector<Libro> &libros) const;
    void guardarEnArchivo(NodoRojoNegro *nodo, ofstream &archivo) const;
    void actualizarPadre(NodoRojoNegro *nodoViejo, NodoRojoNegro *nodoNuevo);

public:
    // Constructor y destructor
    ArbolRojoNegro();
    ~ArbolRojoNegro();

    // Operaciones principales
    void agregarLibro(const Libro &libro);
    void eliminarLibro(const string &titulo);
    NodoRojoNegro *buscarLibro(const string &titulo) const;
    NodoRojoNegro *buscarLibroPorIsbn(const string &isbn) const;
    Persona buscarAutorPorIsni(const string &isni) const;
    void imprimirLibros() const;

    // Gestión de archivos y backup
    void guardarLibrosEnArchivo();
    void cargarLibrosDesdeArchivo();
    void crearBackup(const string &nombreArchivo);
    void restaurarBackup(const string &nombreArchivo);
    void limpiarArbol();
    void compararFechasNacimiento(const string &autor1, const string &autor2);
    void buscarAutorBinario(const string &nombreAutor);

    // Métodos de utilidad
    bool estaVacio() const;
    NodoRojoNegro *obtenerRaiz() const;
    void setEvitarGuardar(bool valor);

    // Métodos adicionales específicos para árboles rojo-negro
    Color obtenerColor(NodoRojoNegro *nodo) const {
        return (nodo == nullptr) ? NEGRO : nodo->color;
    }

    void fijarColor(NodoRojoNegro *nodo, Color color) {
        if (nodo != nullptr)
            nodo->color = color;
    }

    bool esRojo(NodoRojoNegro *nodo) const {
        return nodo != nullptr && nodo->color == ROJO;
    }

    bool esNegro(NodoRojoNegro *nodo) const {
        return nodo == nullptr || nodo->color == NEGRO;
    }
};

#endif // ARBOLROJONEGRO_H