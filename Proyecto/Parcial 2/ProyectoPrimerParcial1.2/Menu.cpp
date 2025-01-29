/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Menu principal                                           *
 * Autor:                          Stiven Diaz, Andres Cedeño                              *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Menu.h"
#include "BackupManager.h"
#include "Validaciones.h"
#include "Utils.h"
#include "funciones.h"
#include "pdf_generator.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <sstream>
#include <ctime>
#include <windows.h>

using namespace std;

void mostrarMenu(ArbolRojoNegro& arbol) {
    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Agregar libro");
    menuOpciones.insertar("Buscar libro");
    menuOpciones.insertar("Eliminar libro");
    menuOpciones.insertar("Ver todos los libros");
    menuOpciones.insertar("Exportar en archivo PDF");
    menuOpciones.insertar("Crear backup");
    menuOpciones.insertar("Restaurar backup");
    menuOpciones.insertar("Buscar por rango");
    menuOpciones.insertar("Buscar autor (busqueda binaria)");
    menuOpciones.insertar("Comparar fechas de autores");
    menuOpciones.insertar("Salir");

    int seleccion = 0;
    string ruta = "libros.txt";
    int anioInicio, anioFin;

    while (true) {
        system("cls");
        cout << "=== Menu Principal ===\n";
        NodoMenu* actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++) {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<\n";
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        }
        else if (tecla == 80) { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        }
        else if (tecla == '\r') { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Agregar libro") {
                string titulo, isbn, isni;
                string fechaPub, fechaNac;
                Persona autor;
                do {
                    cout << "Ingrese título del libro (o presione Enter para regresar al menú): ";
                    getline(cin, titulo);
                    if (titulo.empty()) {
                        cout << "Regresando al menú principal...\n";
                        break;
                    }
                } while (!Validaciones::validarTitulo(titulo, "Título"));

                if (titulo.empty()) continue;

                do {
                    cout << "Ingrese ISBN (o presione Enter para regresar al menú): ";
                    getline(cin, isbn);
                    if (isbn.empty()) {
                        cout << "Regresando al menú principal...\n";
                        break;
                    }
                } while (!Validaciones::validarIsbn(isbn));

                if (isbn.empty()) continue;

                NodoRojoNegro* libroExistente = arbol.buscarLibroPorIsbn(isbn);
                if (libroExistente) {
                    cout << "El ISBN ya existe. Información del libro existente:\n";
                    libroExistente->libro.mostrar();
                }
                else {
                    do {
                        cout << "Ingrese ISNI del autor (o presione Enter para regresar al menú): ";
                        getline(cin, isni);
                        if (isni.empty()) {
                            cout << "Regresando al menú principal...\n";
                            break;
                        }
                    } while (!Validaciones::validarIsni(isni));

                    if (isni.empty()) continue;

                    Persona autorExistente = arbol.buscarAutorPorIsni(isni);
                    if (autorExistente.getNombre() != "") {
                        cout << "Autor existente encontrado. Usando información del autor.\n";
                        autor = autorExistente;
                        fechaNac = autorExistente.getFechaNacimiento().toString();
                    }
                    else {
                        string nombreAutor;
                        do {
                            cout << "Ingrese nombre del autor (o presione Enter para regresar al menú): ";
                            getline(cin, nombreAutor);
                            if (nombreAutor.empty()) {
                                cout << "Regresando al menú principal...\n";
                                break;
                            }
                        } while (!Validaciones::validarTituloNombre(nombreAutor, "Nombre del Autor"));

                        if (nombreAutor.empty()) continue;

                        do {
                            cout << "Ingrese fecha de nacimiento del autor (DD-MM-YYYY): ";
                            getline(cin, fechaNac);
                            if (fechaNac.empty()) {
                                cout << "Regresando al menú principal...\n";
                                break;
                            }
                        } while (!Validaciones::validarFecha(fechaNac));

                        if (fechaNac.empty()) continue;

                        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNac);
                        autor = Persona(nombreAutor, isni, fechaNacimientoAutor);
                    }

                    do {
                        cout << "Ingrese fecha de publicación del libro (DD-MM-YYYY): ";
                        getline(cin, fechaPub);
                        if (fechaPub.empty()) {
                            cout << "Regresando al menú principal...\n";
                            break;
                        }
                    } while (!Validaciones::validarFechaPublicacion(fechaPub, fechaNac));

                    if (fechaPub.empty()) continue;

                    Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPub);
                    Libro libro(titulo, isbn, autor, fechaPublicacion);
                    arbol.agregarLibro(libro);
                }
            }
            else if (opcionSeleccionada == "Buscar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a buscar (o presione Enter para regresar al menú): ";
                getline(cin, isbn);
                
                if (isbn.empty()) {
                    cout << "Operación cancelada. Regresando al menú principal...\n";
                    continue;
                }

                if (!Validaciones::validarIsbn(isbn)) {
                    continue;
                }

                NodoRojoNegro* nodo = arbol.buscarLibroPorIsbn(isbn);
                if (nodo) {
                    nodo->libro.mostrar();
                } else {
                    cout << "Libro no encontrado.\n";
                }
            }
            else if (opcionSeleccionada == "Eliminar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a eliminar (o presione Enter para regresar al menú): ";
                getline(cin, isbn);

                if (isbn.empty()) {
                    cout << "Operación cancelada. Regresando al menú principal...\n";
                    continue;
                }

                if (!Validaciones::validarIsbn(isbn)) {
                    continue;
                }

                NodoRojoNegro* nodo = arbol.buscarLibroPorIsbn(isbn);
                if (nodo) {
                    cout << "¿Está seguro de que desea eliminar este libro? (S/N): ";
                    string confirmacion;
                    getline(cin, confirmacion);
                    if (confirmacion == "S" || confirmacion == "s") {
                        arbol.eliminarLibro(nodo->libro.getTitulo());
                        cout << "Libro eliminado exitosamente.\n";
                    } else {
                        cout << "Operación cancelada.\n";
                    }
                } else {
                    cout << "Libro no encontrado.\n";
                }
            }
            else if (opcionSeleccionada == "Ver todos los libros") {
                arbol.imprimirLibros();
            }
            else if (opcionSeleccionada == "Exportar en archivo PDF") {
                try {
                    const string inputFile = "libros.txt";
                    createPDF(inputFile);
                    cout << "PDF generado exitosamente.\n";
                } catch (const exception& e) {
                    cout << "Error al generar el PDF: " << e.what() << endl;
                }
            }
            else if (opcionSeleccionada == "Crear backup") {
                try {
                    time_t ahora = time(0);
                    tm* tiempo = localtime(&ahora);
                    stringstream ss;
                    ss << (1900 + tiempo->tm_year) << "_"
                       << (1 + tiempo->tm_mon) << "_"
                       << tiempo->tm_mday << "_"
                       << tiempo->tm_hour << "_"
                       << tiempo->tm_min << "_"
                       << tiempo->tm_sec << ".txt";
                    arbol.crearBackup(ss.str());
                } catch (const exception& e) {
                    cout << "Error al crear el backup: " << e.what() << endl;
                }
            }
            else if (opcionSeleccionada == "Restaurar backup") {
                try {
                    BackupManager::restaurarBackup(arbol);
                } catch (const exception& e) {
                    cout << "Error al restaurar el backup: " << e.what() << endl;
                }
            }
            else if (opcionSeleccionada == "Buscar por rango") {
                while (true) {
                    string inputAnioInicio, inputAnioFin;

                    cout << "Ingrese el año de inicio (0001 a 2025) (o presione Enter para regresar al menú): ";
                    getline(cin, inputAnioInicio);
                    if (inputAnioInicio.empty()) {
                        cout << "Operación cancelada. Regresando al menú principal...\n";
                        break;
                    }

                    cout << "Ingrese el año de fin (0001 a 2025) (o presione Enter para regresar al menú): ";
                    getline(cin, inputAnioFin);
                    if (inputAnioFin.empty()) {
                        cout << "Operación cancelada. Regresando al menú principal...\n";
                        break;
                    }

                    try {
                        anioInicio = stoi(inputAnioInicio);
                        anioFin = stoi(inputAnioFin);

                        if (anioInicio < 1 || anioInicio > 2025 || anioFin < 1 || anioFin > 2025) {
                            cout << "Error: Los años deben estar en el rango de 0001 a 2025.\n";
                            continue;
                        }

                        if (anioFin > anioInicio) {
                            cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                            buscarPorRango(ruta, anioInicio, anioFin);
                            break;
                        } else {
                            cout << "Error: El año de fin debe ser mayor al año de inicio.\n";
                        }
                    } catch (const invalid_argument&) {
                        cout << "Error: Entrada inválida. Por favor, ingrese un año válido.\n";
                    }
                }
            }
            else if (opcionSeleccionada == "Buscar autor (busqueda binaria)") {
                string nombreAutor;
                cout << "Ingrese el nombre del autor a buscar (o presione Enter para regresar al menú): ";
                getline(cin, nombreAutor);
                
                if (nombreAutor.empty()) {
                    cout << "Operación cancelada. Regresando al menú principal...\n";
                    continue;
                }

                // Validar que el nombre solo contenga letras y espacios
                if (!Validaciones::validarTexto(nombreAutor, "Nombre del autor")) {
                    continue;
                }

                // Validar que el nombre tenga una longitud razonable
                if (nombreAutor.length() < 3) {
                    cout << "Error: El nombre del autor debe tener al menos 3 caracteres.\n";
                    continue;
                }

                try {
                    arbol.buscarAutorBinario(nombreAutor);
                } catch (const exception& e) {
                    cout << "Error al buscar el autor: " << e.what() << endl;
                }
            }
            else if (opcionSeleccionada == "Comparar fechas de autores") {
                string autor1, autor2;

                // Validación primer autor
                do {
                    cout << "Ingrese el nombre del primer autor (o presione Enter para regresar al menú): ";
                    getline(cin, autor1);
                    
                    if (autor1.empty()) {
                        cout << "Operación cancelada. Regresando al menú principal...\n";
                        break;
                    }

                    if (!Validaciones::validarTexto(autor1, "Nombre del primer autor")) {
                        continue;
                    }

                    if (autor1.length() < 3) {
                        cout << "Error: El nombre del autor debe tener al menos 3 caracteres.\n";
                        continue;
                    }
                    break;
                } while (true);

                if (autor1.empty()) continue;

                // Validación segundo autor
                do {
                    cout << "Ingrese el nombre del segundo autor (o presione Enter para regresar al menú): ";
                    getline(cin, autor2);
                    
                    if (autor2.empty()) {
                        cout << "Operación cancelada. Regresando al menú principal...\n";
                        break;
                    }

                    if (!Validaciones::validarTexto(autor2, "Nombre del segundo autor")) {
                        continue;
                    }

                    if (autor2.length() < 3) {
                        cout << "Error: El nombre del autor debe tener al menos 3 caracteres.\n";
                        continue;
                    }

                    // Verificar que los autores sean diferentes
                    if (autor1 == autor2) {
                        cout << "Error: No puede comparar un autor consigo mismo.\n";
                        continue;
                    }
                    break;
                } while (true);

                if (autor2.empty()) continue;

                try {
                    arbol.compararFechasNacimiento(autor1, autor2);
                } catch (const exception& e) {
                    cout << "Error al comparar las fechas: " << e.what() << endl;
                }
            }
            else if (opcionSeleccionada == "Salir") {
                cout << "¿Está seguro que desea salir? (S/N): ";
                string confirmacion;
                getline(cin, confirmacion);
                if (confirmacion == "S" || confirmacion == "s") {
                    cout << "Gracias por usar el programa. ¡Hasta luego!\n";
                    break;
                }
            }
            cout << "\nPresione cualquier tecla para continuar...\n";
            _getch();
        }
        else if (tecla == 59) { // F1
            try {
                wstring base_path = getExecutablePath();
                wstring ayuda_path = base_path + L"\\output\\ayuda.exe";
                string command = "start cmd /C \"" + string(ayuda_path.begin(), ayuda_path.end()) + "\"";
                system(command.c_str());
            } catch (const exception& e) {
                cout << "Error al abrir la ayuda: " << e.what() << endl;
            }
        }
    }
}
                        