/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Realizar una Lista circular doble                        *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "ListaCircularDoble.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <direct.h>  // Para mkdir en Windows
#include <sys/stat.h>  // Para usar _stat
#include "BackupManager.h"  // Incluir el archivo de cabecera con la declaración de la función

using namespace std;

// Agregar libro
void ListaCircularDoble::agregarLibro(const Libro& libro) {
    Nodo* nuevo = new Nodo{libro, nullptr, nullptr};
    if (!cabeza) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        Nodo* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        cabeza->anterior = nuevo;
        ultimo->siguiente = nuevo;
    }
    cout << "Libro agregado: " << libro.getTitulo() << endl;
    // Guardar solo si no se está restaurando un backup
    if (!evitarGuardar) {
        guardarLibrosEnArchivo();
    }
}

// Limpiar la lista actual
void ListaCircularDoble::limpiarLista() {
    if (!cabeza) return;

    Nodo* actual = cabeza;
    do {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);

    cabeza = nullptr;
}

// Imprimir todos los libros
void ListaCircularDoble::imprimirLibros() {
    if (!cabeza) {
        cout << "No hay libros registrados.\n";
        return;
    }
    Nodo* actual = cabeza;
    cout << left << setw(41) << "Título" 
        << setw(25) << "Autor" 
        << setw(25) << "ISNI" 
        << setw(20) << "ISBN"
        << setw(15) << "Publicación" 
        << setw(15) << "Nac. Autor" << endl;
    cout << string(140, '-') << endl;

    do {
        cout << left << setw(40) << actual->libro.getTitulo()
            << setw(25) << actual->libro.getAutor().getNombre()
            << setw(25) << actual->libro.getAutor().getIsni()
            << setw(20) << actual->libro.getIsbn()
            << setw(15) << actual->libro.getFechaPublicacion().mostrar()
            << setw(15) << actual->libro.getAutor().getFechaNacimiento().mostrar() << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}

// Buscar libro por título
Nodo* ListaCircularDoble::buscarLibro(const string& titulo) {
    if (!cabeza) return nullptr;
    Nodo* actual = cabeza;
    do {
        if (actual->libro.getTitulo() == titulo) return actual;
        actual = actual->siguiente;
    } while (actual != cabeza);
    return nullptr;
}

// Buscar libro por ISBN
Nodo* ListaCircularDoble::buscarLibroPorIsbn(const string& isbn) {
    if (!cabeza) return nullptr;
    Nodo* actual = cabeza;
    do {
        if (actual->libro.getIsbn() == isbn)
            return actual;
        actual = actual->siguiente;
    } while (actual != cabeza);
    return nullptr;
}

// Buscar autor por ISNI
Persona ListaCircularDoble::buscarAutorPorIsni(const string& isni) {
    if (!cabeza) return Persona();
    Nodo* actual = cabeza;
    do {
        if (actual->libro.getAutor().getIsni() == isni)
            return actual->libro.getAutor();
        actual = actual->siguiente;
    } while (actual != cabeza);
    return Persona();
}

// Eliminar libro y actualizar archivo
void ListaCircularDoble::eliminarLibro(const string& titulo) {
    if (!cabeza) return;
    Nodo* actual = cabeza;
    bool encontrado = false;
    do {
        if (actual->libro.getTitulo() == titulo) {
            encontrado = true;
            if (actual->siguiente == actual) {  // Si es el único libro
                cabeza = nullptr;
            } else {
                Nodo* anterior = actual->anterior;
                Nodo* siguiente = actual->siguiente;
                anterior->siguiente = siguiente;
                siguiente->anterior = anterior;
                if (actual == cabeza) cabeza = siguiente;
            }
            delete actual;
            cout << "Libro eliminado: " << titulo << endl;
            break;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    if (!encontrado) {
        cout << "Libro no encontrado: " << titulo << endl;
    }

    // Actualizar el archivo después de la eliminación
    guardarLibrosEnArchivo();  
}

// Guardar los libros en el archivo (actualizado)
void ListaCircularDoble::guardarLibrosEnArchivo() {
    ofstream archivo("libros_temp.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo temporal para guardar.\n\n";
        return;
    }

    Nodo* actual = cabeza;
    if (actual) {
        do {
            archivo << actual->libro.getTitulo() << ";"
                    << actual->libro.getAutor().getNombre() << ";"
                    << actual->libro.getAutor().getIsni() << ";"
                    << actual->libro.getAutor().getFechaNacimiento().mostrar() << ";"
                    << actual->libro.getIsbn() << ";"
                    << actual->libro.getFechaPublicacion().mostrar() << endl;
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    archivo.close();

    // Verificar si el archivo temporal se creó correctamente
    if (FILE* file = fopen("libros_temp.txt", "r")) {
        fclose(file);
    } else {
        cout << "No se pudo crear el archivo temporal correctamente.\n";
        return;
    }

    // Eliminar el archivo de destino si ya existe
    if (remove(archivoLibros.c_str()) != 0) {
        // Si el archivo no se puede eliminar, mostrar error
        cout << "Error al eliminar el archivo de destino: " << archivoLibros << endl;
    }

    // Renombrar el archivo temporal a la ubicación final
    if (rename("libros_temp.txt", archivoLibros.c_str()) != 0) {
        // Mostrar error si renombrar falla
        perror("Error al renombrar el archivo temporal");
    } else {
        cout << "Libros guardados en el archivo: " << archivoLibros << endl;
    }
}

// Cargar los libros desde el archivo
void ListaCircularDoble::cargarLibrosDesdeArchivo() {
    ifstream archivo(archivoLibros);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para cargar los libros.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string titulo, nombreAutor, isni, fechaNacAutor, isbn, fechaPublicacion;
        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacAutor, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPublicacion, ';');

        // Procesar fechas
        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNacAutor);
        Fecha fechaPublicacionLibro = Fecha::crearDesdeCadena(fechaPublicacion);

        Persona autorPersona(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autorPersona, fechaPublicacionLibro);
        agregarLibro(libro);
    }
    archivo.close();
    cout << "Libros cargados desde el archivo.\n";
}

// Backup
void ListaCircularDoble::crearBackup(const string& nombreArchivo) {
    string carpetaBackup = "backup";  // Carpeta donde se almacenan los backups
    
    // Asegurarnos de que la carpeta de backups exista
    BackupManager::crearCarpetaSiNoExiste(carpetaBackup);

    // Crear la ruta completa para el archivo de backup dentro de la carpeta "backup"
    string rutaCompleta = carpetaBackup + "\\" + nombreArchivo;

    // Crear el archivo de backup
    ofstream archivo(rutaCompleta);
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo de backup en la ruta: " << rutaCompleta << endl;
        return;
    }

    // Iterar sobre los elementos de la lista circular y guardar los datos de cada libro en el archivo
    Nodo* actual = cabeza;
    if (actual) {
        do {
            // Obtener información del libro y sus componentes
            const Libro& libro = actual->libro;
            const Persona& autor = libro.getAutor();
            const Fecha& fechaNac = autor.getFechaNacimiento();
            const Fecha& fechaPub = libro.getFechaPublicacion();

            // Guardar los datos en el archivo en un formato delimitado
            archivo << libro.getTitulo() << ";" 
                    << autor.getNombre() << ";"
                    << autor.getIsni() << ";"
                    << fechaNac.getDia() << "-" << fechaNac.getMes() << "-" << fechaNac.getAnio() << ";"
                    << libro.getIsbn() << ";"
                    << fechaPub.getDia() << "-" << fechaPub.getMes() << "-" << fechaPub.getAnio() << "\n";
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    // Cerrar el archivo después de escribir los datos
    archivo.close();
    cout << "Backup creado correctamente en: " << rutaCompleta << endl;
}

// Restaurar backup y sobreescribir archivo
void ListaCircularDoble::restaurarBackup(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de backup.\n";
        return;
    }

    cout << "Cargando backup desde: " << nombreArchivo << endl;

    limpiarLista();
    evitarGuardar = true; // Evitar guardar durante la restauración

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string titulo, nombreAutor, isni, fechaNacStr, isbn, fechaPubStr;

        // Leer datos del archivo
        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacStr, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPubStr, ';');

        // Parsear la fecha de nacimiento del autor
        int diaNac, mesNac, anioNac;
        sscanf(fechaNacStr.c_str(), "%d-%d-%d", &diaNac, &mesNac, &anioNac);
        Fecha fechaNacimientoAutor(diaNac, mesNac, anioNac);

        // Parsear la fecha de publicación
        int diaPub, mesPub, anioPub;
        sscanf(fechaPubStr.c_str(), "%d-%d-%d", &diaPub, &mesPub, &anioPub);
        Fecha fechaPublicacion(diaPub, mesPub, anioPub);

        // Crear los objetos correspondientes
        Persona autor(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autor, fechaPublicacion);

        // Agregar libro a la lista
        agregarLibro(libro);
    }

    evitarGuardar = false; // Volver a guardar normalmente
    archivo.close();

    guardarLibrosEnArchivo();
    cout << "Backup restaurado: " << nombreArchivo << endl;
}
