/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include "funciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <functional>

using namespace std;

vector<string> dividir(const string &linea, char delimitador)
{
    vector<string> partes;
    stringstream ss(linea);
    string parte;
    while (getline(ss, parte, delimitador))
    {
        partes.push_back(parte);
    }
    return partes;
}

void imprimirCabecera()
{
    cout << left;
    cout << setw(40) << "Título"
         << setw(25) << "Autor"
         << setw(22) << "ISNI"
         << setw(20) << "ISBN"
         << setw(15) << "Publicación"
         << "Nac. Autor" << endl;

    cout << string(120, '-') << endl;
    cout << "\n";
}

int extraerAnio(const string &fecha)
{
    // La fecha viene en formato DD/MM/YYYY o DD-MM-YYYY
    size_t pos = fecha.find_last_of("/-");
    if (pos != string::npos && pos + 5 <= fecha.length())
    {
        return stoi(fecha.substr(pos + 1));
    }
    return 0;
}

void buscarPorRango(const string &rutaArchivo, int anioInicio, int anioFin)
{
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    bool cabeceraImprimida = false;

    while (getline(archivo, linea))
    {
        vector<string> campos = dividir(linea, ';');
        if (campos.size() >= 6)
        {
            string fechaPublicacion = campos[5];
            int anioPublicacion = extraerAnio(fechaPublicacion);

            if (anioPublicacion >= anioInicio && anioPublicacion <= anioFin)
            {
                if (!cabeceraImprimida)
                {
                    imprimirCabecera();
                    cabeceraImprimida = true;
                }

                cout << left;
                cout << setw(40) << campos[0] // Título
                     << setw(25) << campos[1] // Autor
                     << setw(22) << campos[2] // ISNI
                     << setw(20) << campos[4] // ISBN
                     << setw(15) << campos[5] // Fecha Publicación
                     << campos[3] << endl;    // Fecha Nacimiento
            }
        }
    }

    if (!cabeceraImprimida)
    {
        cout << "No se encontraron libros en el rango de años especificado." << endl;
    }

    archivo.close();
}

void buscarPorRangoEnArbol(ArbolRojoNegro &arbol, int anioInicio, int anioFin)
{
    if (arbol.estaVacio())
    {
        cout << "El árbol está vacío." << endl;
        return;
    }

    bool encontrado = false;
    vector<Libro> libros;
    NodoRojoNegro *raiz = arbol.obtenerRaiz();

    // Realizar un recorrido inorden para obtener los libros ordenados
    function<void(NodoRojoNegro *)> inorden = [&](NodoRojoNegro *nodo)
    {
        if (nodo != nullptr)
        {
            inorden(nodo->izquierdo);

            int anioPublicacion = extraerAnio(nodo->libro.getFechaPublicacion().mostrar());
            if (anioPublicacion >= anioInicio && anioPublicacion <= anioFin)
            {
                if (!encontrado)
                {
                    imprimirCabecera();
                    encontrado = true;
                }

                cout << left;
                cout << setw(40) << nodo->libro.getTitulo()
                     << setw(25) << nodo->libro.getAutor().getNombre()
                     << setw(22) << nodo->libro.getAutor().getIsni()
                     << setw(20) << nodo->libro.getIsbn()
                     << setw(15) << nodo->libro.getFechaPublicacion().mostrar()
                     << nodo->libro.getAutor().getFechaNacimiento().mostrar() << endl;
            }

            inorden(nodo->derecho);
        }
    };

    inorden(raiz);

    if (!encontrado)
    {
        cout << "No se encontraron libros en el rango de años especificado." << endl;
    }
}
