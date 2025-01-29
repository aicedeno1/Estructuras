/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include "ArbolRojoNegro.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "BackupManager.h"
#include <set>

using namespace std;

// Constructor y destructor
ArbolRojoNegro::ArbolRojoNegro() : raiz(nullptr) {}

ArbolRojoNegro::~ArbolRojoNegro()
{
    limpiarArbol();
}

// Rotaciones
void ArbolRojoNegro::rotarIzquierda(NodoRojoNegro *nodo)
{
    NodoRojoNegro *hijoDerecho = nodo->derecho;
    nodo->derecho = hijoDerecho->izquierdo;

    if (hijoDerecho->izquierdo != nullptr)
        hijoDerecho->izquierdo->padre = nodo;

    hijoDerecho->padre = nodo->padre;

    if (nodo->padre == nullptr)
        raiz = hijoDerecho;
    else if (nodo == nodo->padre->izquierdo)
        nodo->padre->izquierdo = hijoDerecho;
    else
        nodo->padre->derecho = hijoDerecho;

    hijoDerecho->izquierdo = nodo;
    nodo->padre = hijoDerecho;
}

void ArbolRojoNegro::rotarDerecha(NodoRojoNegro *nodo)
{
    NodoRojoNegro *hijoIzquierdo = nodo->izquierdo;
    nodo->izquierdo = hijoIzquierdo->derecho;

    if (hijoIzquierdo->derecho != nullptr)
        hijoIzquierdo->derecho->padre = nodo;

    hijoIzquierdo->padre = nodo->padre;

    if (nodo->padre == nullptr)
        raiz = hijoIzquierdo;
    else if (nodo == nodo->padre->derecho)
        nodo->padre->derecho = hijoIzquierdo;
    else
        nodo->padre->izquierdo = hijoIzquierdo;

    hijoIzquierdo->derecho = nodo;
    nodo->padre = hijoIzquierdo;
}

// Balanceo después de inserción
void ArbolRojoNegro::balancearInsercion(NodoRojoNegro *nodo)
{
    while (nodo != raiz && nodo->padre->color == ROJO)
    {
        if (nodo->padre == nodo->padre->padre->izquierdo)
        {
            NodoRojoNegro *tio = nodo->padre->padre->derecho;

            if (tio != nullptr && tio->color == ROJO)
            {
                nodo->padre->color = NEGRO;
                tio->color = NEGRO;
                nodo->padre->padre->color = ROJO;
                nodo = nodo->padre->padre;
            }
            else
            {
                if (nodo == nodo->padre->derecho)
                {
                    nodo = nodo->padre;
                    rotarIzquierda(nodo);
                }
                nodo->padre->color = NEGRO;
                nodo->padre->padre->color = ROJO;
                rotarDerecha(nodo->padre->padre);
            }
        }
        else
        {
            NodoRojoNegro *tio = nodo->padre->padre->izquierdo;

            if (tio != nullptr && tio->color == ROJO)
            {
                nodo->padre->color = NEGRO;
                tio->color = NEGRO;
                nodo->padre->padre->color = ROJO;
                nodo = nodo->padre->padre;
            }
            else
            {
                if (nodo == nodo->padre->izquierdo)
                {
                    nodo = nodo->padre;
                    rotarDerecha(nodo);
                }
                nodo->padre->color = NEGRO;
                nodo->padre->padre->color = ROJO;
                rotarIzquierda(nodo->padre->padre);
            }
        }
    }
    raiz->color = NEGRO;
}

// Agregar libro
void ArbolRojoNegro::agregarLibro(const Libro &libro)
{
    NodoRojoNegro *nuevo = new NodoRojoNegro(libro);
    NodoRojoNegro *actual = raiz;
    NodoRojoNegro *padre = nullptr;

    // Encontrar la posición correcta
    while (actual != nullptr)
    {
        padre = actual;
        if (libro.getIsbn() < actual->libro.getIsbn())
            actual = actual->izquierdo;
        else if (libro.getIsbn() > actual->libro.getIsbn())
            actual = actual->derecho;
        else
        {
            delete nuevo;
            cout << "ISBN ya existe en el árbol." << endl;
            return;
        }
    }

    nuevo->padre = padre;
    if (padre == nullptr)
        raiz = nuevo;
    else if (libro.getIsbn() < padre->libro.getIsbn())
        padre->izquierdo = nuevo;
    else
        padre->derecho = nuevo;

    balancearInsercion(nuevo);

    if (!evitarGuardar)
    {
        guardarLibrosEnArchivo();
    }
}

// Buscar libro por ISBN
NodoRojoNegro *ArbolRojoNegro::buscarLibroPorIsbn(const string &isbn) const
{
    NodoRojoNegro *actual = raiz;
    while (actual != nullptr)
    {
        if (isbn == actual->libro.getIsbn())
            return actual;
        else if (isbn < actual->libro.getIsbn())
            actual = actual->izquierdo;
        else
            actual = actual->derecho;
    }
    return nullptr;
}

// Buscar autor por ISNI
Persona ArbolRojoNegro::buscarAutorPorIsni(const string &isni) const
{
    vector<Libro> libros;
    inorden(raiz, libros);

    for (const Libro &libro : libros)
    {
        if (libro.getAutor().getIsni() == isni)
            return libro.getAutor();
    }
    return Persona();
}

// Imprimir libros
void ArbolRojoNegro::imprimirLibros() const
{
    if (raiz == nullptr)
    {
        cout << "No hay libros registrados.\n";
        return;
    }

    cout << left << setw(41) << "Título"
         << setw(25) << "Autor"
         << setw(25) << "ISNI"
         << setw(20) << "ISBN"
         << setw(15) << "Publicación"
         << setw(15) << "Nac. Autor" << endl;
    cout << string(140, '-') << endl;

    vector<Libro> libros;
    inorden(raiz, libros);

    for (const Libro &libro : libros)
    {
        cout << left << setw(40) << libro.getTitulo()
             << setw(25) << libro.getAutor().getNombre()
             << setw(25) << libro.getAutor().getIsni()
             << setw(20) << libro.getIsbn()
             << setw(15) << libro.getFechaPublicacion().mostrar()
             << setw(15) << libro.getAutor().getFechaNacimiento().mostrar() << endl;
    }
}

// Métodos de manejo de archivos
void ArbolRojoNegro::guardarLibrosEnArchivo()
{
    ofstream archivo("libros_temp.txt");
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo temporal para guardar.\n";
        return;
    }

    guardarEnArchivo(raiz, archivo);
    archivo.close();

    if (remove(archivoLibros.c_str()) != 0)
    {
        cout << "Error al eliminar el archivo de destino: " << archivoLibros << endl;
    }

    if (rename("libros_temp.txt", archivoLibros.c_str()) != 0)
    {
        perror("Error al renombrar el archivo temporal");
    }
    else
    {
        cout << "Libros guardados en el archivo: " << archivoLibros << endl;
    }
}

void ArbolRojoNegro::guardarEnArchivo(NodoRojoNegro *nodo, ofstream &archivo) const
{
    if (nodo != nullptr)
    {
        guardarEnArchivo(nodo->izquierdo, archivo);

        archivo << nodo->libro.getTitulo() << ";"
                << nodo->libro.getAutor().getNombre() << ";"
                << nodo->libro.getAutor().getIsni() << ";"
                << nodo->libro.getAutor().getFechaNacimiento().mostrar() << ";"
                << nodo->libro.getIsbn() << ";"
                << nodo->libro.getFechaPublicacion().mostrar() << endl;

        guardarEnArchivo(nodo->derecho, archivo);
    }
}

void ArbolRojoNegro::cargarLibrosDesdeArchivo()
{
    ifstream archivo(archivoLibros);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para cargar los libros.\n";
        return;
    }

    limpiarArbol();
    string linea;
    evitarGuardar = true;

    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string titulo, nombreAutor, isni, fechaNacAutor, isbn, fechaPublicacion;

        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacAutor, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPublicacion, ';');

        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNacAutor);
        Fecha fechaPublicacionLibro = Fecha::crearDesdeCadena(fechaPublicacion);

        Persona autorPersona(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autorPersona, fechaPublicacionLibro);
        agregarLibro(libro);
    }

    evitarGuardar = false;
    archivo.close();
    cout << "Libros cargados desde el archivo.\n";
}

void ArbolRojoNegro::limpiarArbol()
{
    liberarMemoria(raiz);
    raiz = nullptr;
}

void ArbolRojoNegro::liberarMemoria(NodoRojoNegro *nodo)
{
    if (nodo != nullptr)
    {
        liberarMemoria(nodo->izquierdo);
        liberarMemoria(nodo->derecho);
        delete nodo;
    }
}

// Métodos para backup
void ArbolRojoNegro::crearBackup(const string &nombreArchivo)
{
    string carpetaBackup = "backup";
    BackupManager::crearCarpetaSiNoExiste(carpetaBackup);
    string rutaCompleta = carpetaBackup + "\\" + nombreArchivo;

    ofstream archivo(rutaCompleta);
    if (!archivo.is_open())
    {
        cout << "Error al crear el archivo de backup en la ruta: " << rutaCompleta << endl;
        return;
    }

    guardarEnArchivo(raiz, archivo);
    archivo.close();
    cout << "Backup creado correctamente en: " << rutaCompleta << endl;
}

void ArbolRojoNegro::restaurarBackup(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo de backup.\n";
        return;
    }

    cout << "Cargando backup desde: " << nombreArchivo << endl;
    limpiarArbol();
    evitarGuardar = true;

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string titulo, nombreAutor, isni, fechaNacStr, isbn, fechaPubStr;

        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacStr, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPubStr, ';');

        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNacStr);
        Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPubStr);

        Persona autor(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autor, fechaPublicacion);
        agregarLibro(libro);
    }

    evitarGuardar = false;
    archivo.close();
    guardarLibrosEnArchivo();
    cout << "Backup restaurado: " << nombreArchivo << endl;
}

void ArbolRojoNegro::eliminarLibro(const string &titulo)
{
    NodoRojoNegro *nodoEliminar = buscarLibro(titulo);
    if (nodoEliminar == nullptr)
    {
        cout << "Libro no encontrado: " << titulo << endl;
        return;
    }

    NodoRojoNegro *y = nullptr;
    NodoRojoNegro *x = nullptr;

    if (nodoEliminar->izquierdo == nullptr || nodoEliminar->derecho == nullptr)
    {
        y = nodoEliminar;
    }
    else
    {
        y = encontrarSucesor(nodoEliminar);
    }

    if (y->izquierdo != nullptr)
    {
        x = y->izquierdo;
    }
    else
    {
        x = y->derecho;
    }

    if (x != nullptr)
    {
        x->padre = y->padre;
    }

    if (y->padre == nullptr)
    {
        raiz = x;
    }
    else if (y == y->padre->izquierdo)
    {
        y->padre->izquierdo = x;
    }
    else
    {
        y->padre->derecho = x;
    }

    if (y != nodoEliminar)
    {
        nodoEliminar->libro = y->libro;
    }

    if (y->color == NEGRO)
    {
        balancearEliminacion(x);
    }

    delete y;
    if (!evitarGuardar)
    {
        guardarLibrosEnArchivo();
    }
    cout << "Libro eliminado: " << titulo << endl;
}

void ArbolRojoNegro::balancearEliminacion(NodoRojoNegro *x)
{
    while (x != raiz && (x == nullptr || x->color == NEGRO))
    {
        if (x == nullptr)
            break;

        if (x == x->padre->izquierdo)
        {
            NodoRojoNegro *w = x->padre->derecho;
            if (w->color == ROJO)
            {
                w->color = NEGRO;
                x->padre->color = ROJO;
                rotarIzquierda(x->padre);
                w = x->padre->derecho;
            }
            if ((w->izquierdo == nullptr || w->izquierdo->color == NEGRO) &&
                (w->derecho == nullptr || w->derecho->color == NEGRO))
            {
                w->color = ROJO;
                x = x->padre;
            }
            else
            {
                if (w->derecho == nullptr || w->derecho->color == NEGRO)
                {
                    if (w->izquierdo != nullptr)
                        w->izquierdo->color = NEGRO;
                    w->color = ROJO;
                    rotarDerecha(w);
                    w = x->padre->derecho;
                }
                w->color = x->padre->color;
                x->padre->color = NEGRO;
                if (w->derecho != nullptr)
                    w->derecho->color = NEGRO;
                rotarIzquierda(x->padre);
                x = raiz;
            }
        }
        else
        {
            // Caso simétrico para cuando x es hijo derecho
            NodoRojoNegro *w = x->padre->izquierdo;
            if (w->color == ROJO)
            {
                w->color = NEGRO;
                x->padre->color = ROJO;
                rotarDerecha(x->padre);
                w = x->padre->izquierdo;
            }
            if ((w->derecho == nullptr || w->derecho->color == NEGRO) &&
                (w->izquierdo == nullptr || w->izquierdo->color == NEGRO))
            {
                w->color = ROJO;
                x = x->padre;
            }
            else
            {
                if (w->izquierdo == nullptr || w->izquierdo->color == NEGRO)
                {
                    if (w->derecho != nullptr)
                        w->derecho->color = NEGRO;
                    w->color = ROJO;
                    rotarIzquierda(w);
                    w = x->padre->izquierdo;
                }
                w->color = x->padre->color;
                x->padre->color = NEGRO;
                if (w->izquierdo != nullptr)
                    w->izquierdo->color = NEGRO;
                rotarDerecha(x->padre);
                x = raiz;
            }
        }
    }
    if (x != nullptr)
        x->color = NEGRO;
}

NodoRojoNegro *ArbolRojoNegro::encontrarSucesor(NodoRojoNegro *nodo)
{
    if (nodo->derecho != nullptr)
        return encontrarMinimo(nodo->derecho);

    NodoRojoNegro *sucesor = nodo->padre;
    while (sucesor != nullptr && nodo == sucesor->derecho)
    {
        nodo = sucesor;
        sucesor = sucesor->padre;
    }
    return sucesor;
}

NodoRojoNegro *ArbolRojoNegro::encontrarMinimo(NodoRojoNegro *nodo)
{
    while (nodo->izquierdo != nullptr)
        nodo = nodo->izquierdo;
    return nodo;
}

void ArbolRojoNegro::inorden(NodoRojoNegro *nodo, vector<Libro> &libros) const
{
    if (nodo != nullptr)
    {
        inorden(nodo->izquierdo, libros);
        libros.push_back(nodo->libro);
        inorden(nodo->derecho, libros);
    }
}

NodoRojoNegro *ArbolRojoNegro::buscarLibro(const string &titulo) const
{
    vector<Libro> libros;
    inorden(raiz, libros);

    for (const Libro &libro : libros)
    {
        if (libro.getTitulo() == titulo)
        {
            return buscarLibroPorIsbn(libro.getIsbn());
        }
    }
    return nullptr;
}

bool ArbolRojoNegro::estaVacio() const
{
    return raiz == nullptr;
}

NodoRojoNegro *ArbolRojoNegro::obtenerRaiz() const
{
    return raiz;
}

void ArbolRojoNegro::setEvitarGuardar(bool valor)
{
    evitarGuardar = valor;
}

// Búsqueda binaria por nombre de autor
int ArbolRojoNegro::busquedaBinariaAutor(const vector<Persona> &autores, const string &nombreAutor) const
{
    string nombreBuscado = normalizarString(nombreAutor);
    int inicio = 0;
    int fin = autores.size() - 1;

    while (inicio <= fin)
    {
        int medio = inicio + (fin - inicio) / 2;
        string nombreActual = normalizarString(autores[medio].getNombre());

        if (nombreActual == nombreBuscado)
            return medio;

        if (nombreActual < nombreBuscado)
            inicio = medio + 1;
        else
            fin = medio - 1;
    }

    return -1;
}

// Función 1: Comparar fechas de nacimiento usando búsqueda binaria
void ArbolRojoNegro::compararFechasNacimiento(const string &autor1, const string &autor2)
{
    vector<Persona> autores = obtenerAutoresOrdenados();

    int indice1 = busquedaBinariaAutor(autores, autor1);
    int indice2 = busquedaBinariaAutor(autores, autor2);

    if (indice1 == -1)
    {
        cout << "Autor no encontrado: " << autor1 << endl;
        return;
    }
    if (indice2 == -1)
    {
        cout << "Autor no encontrado: " << autor2 << endl;
        return;
    }

    const Persona &persona1 = autores[indice1];
    const Persona &persona2 = autores[indice2];

    cout << "\nComparación de fechas de nacimiento:" << endl;
    cout << "----------------------------------------" << endl;
    cout << persona1.getNombre() << ": " << persona1.getFechaNacimiento().mostrar() << endl;
    cout << persona2.getNombre() << ": " << persona2.getFechaNacimiento().mostrar() << endl;

    if (persona1.getFechaNacimiento().esAnterior(persona2.getFechaNacimiento()))
    {
        cout << persona1.getNombre() << " nació antes que " << persona2.getNombre() << endl;
    }
    else if (persona2.getFechaNacimiento().esAnterior(persona1.getFechaNacimiento()))
    {
        cout << persona2.getNombre() << " nació antes que " << persona1.getNombre() << endl;
    }
    else
    {
        cout << "Ambos autores nacieron en la misma fecha" << endl;
    }
}

// Función 2: Buscar autor e imprimir datos usando búsqueda binaria

void ArbolRojoNegro::buscarAutorBinario(const string &nombreAutor)
{
    if (nombreAutor.empty())
    {
        cout << "Error: El nombre del autor no puede estar vacío." << endl;
        return;
    }

    vector<Persona> autores = obtenerAutoresOrdenados();
    if (autores.empty())
    {
        cout << "No hay autores registrados en el sistema." << endl;
        return;
    }

    int indice = busquedaBinariaAutor(autores, nombreAutor);

    if (indice == -1)
    {
        cout << "\nAutor no encontrado: " << nombreAutor << endl;
        cout << "Sugerencias de autores disponibles:" << endl;
        cout << "----------------------------------------" << endl;
        for (const Persona &autor : autores)
        {
            cout << "- " << autor.getNombre() << endl;
        }
        return;
    }

    const Persona &autor = autores[indice];

    cout << "\nDatos del autor encontrado:" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Nombre: " << autor.getNombre() << endl;
    cout << "ISNI: " << autor.getIsni() << endl;
    cout << "Fecha de nacimiento: " << autor.getFechaNacimiento().mostrar() << endl;

    vector<Libro> libros;
    inorden(raiz, libros);

    cout << "\nLibros del autor:" << endl;
    cout << "----------------------------------------" << endl;
    bool encontroLibros = false;

    for (const Libro &libro : libros)
    {
        if (normalizarString(libro.getAutor().getNombre()) == normalizarString(nombreAutor))
        {
            encontroLibros = true;
            cout << "- " << libro.getTitulo() << " (ISBN: " << libro.getIsbn() << ")" << endl;
            cout << "  Fecha de publicación: " << libro.getFechaPublicacion().mostrar() << endl;
        }
    }

    if (!encontroLibros)
    {
        cout << "No se encontraron libros para este autor." << endl;
    }
}
vector<Persona> ArbolRojoNegro::obtenerAutoresOrdenados() const
{
    vector<Libro> libros;
    inorden(raiz, libros);

    // Usar un set para mantener autores únicos
    set<string> autoresUnicos;
    vector<Persona> autores;

    for (const Libro &libro : libros)
    {
        string nombreAutor = normalizarString(libro.getAutor().getNombre());
        if (autoresUnicos.insert(nombreAutor).second)
        {
            autores.push_back(libro.getAutor());
        }
    }

    // Ordenar autores por nombre normalizado
    sort(autores.begin(), autores.end(),
         [this](const Persona &a, const Persona &b)
         {
             return normalizarString(a.getNombre()) < normalizarString(b.getNombre());
         });

    return autores;
}