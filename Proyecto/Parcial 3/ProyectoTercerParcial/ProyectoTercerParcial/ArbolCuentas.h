#ifndef ARBOL_CUENTAS_H
#define ARBOL_CUENTAS_H

#include <vector>
#include <fstream>
#include <iostream>

// Forward declaration
class GestorClientes;
#include "Cuenta.h"
#include "NodoCuenta.h"

class ArbolCuentas
{
private:
    NodoCuenta *raiz;
    bool evitarGuardar;
    std::string archivoCuentas;
    

    // Métodos auxiliares para rotaciones y balanceo
    void rotarIzquierda(NodoCuenta *nodo);
    void rotarDerecha(NodoCuenta *nodo);
    void balancearInsercion(NodoCuenta *nodo);
    void balancearEliminacion(NodoCuenta *nodo);

    // Métodos auxiliares para manejo de nodos
    NodoCuenta *encontrarMinimo(NodoCuenta *nodo);
    NodoCuenta *encontrarSucesor(NodoCuenta *nodo);
    void liberarMemoria(NodoCuenta *nodo);

    // Métodos auxiliares para recorrido del árbol
    void inorden(NodoCuenta *nodo, std::vector<Cuenta> &cuentas) const;
    void guardarEnArchivo(NodoCuenta *nodo, std::ofstream &archivo) const;

public:
    // Constructor y destructor
    ArbolCuentas();
    ~ArbolCuentas();

    // Operaciones principales
    void agregarCuenta(const Cuenta &cuenta);
    void eliminarCuenta(const std::string &numeroCuenta);
    NodoCuenta *buscarCuenta(const std::string &numeroCuenta) const;
    std::vector<Cuenta> listarCuentas() const;
    std::vector<Cuenta> buscarCuentasPorCliente(const std::string &cedulaCliente) const;

    // Gestión de archivos
    void guardarCuentasEnArchivo();
    void cargarCuentasDesdeArchivo(GestorClientes &gestorClientes);

    // Método sin parámetros para compatibilidad hacia atrás
    void cargarCuentasDesdeArchivo();

    // Métodos para backup
    void crearBackup(const std::string &nombreArchivo);
    void restaurarBackup(const std::string &nombreArchivo);

    // Limpiar árbol
    void limpiarArbol();

    // Verificador
    bool estaVacio() const;
    NodoCuenta *obtenerRaiz() const;
    void setEvitarGuardar(bool valor);
};

#endif // ARBOL_CUENTAS_H