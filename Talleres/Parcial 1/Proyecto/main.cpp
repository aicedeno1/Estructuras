#include <iostream>
#include <conio.h>
#include <windows.h>
#include "ListaCircularDoble.h"
#include "Autor.h"
#include "Libro.h"
#include "Fecha.h"
#include "Validaciones.h"
#include "BackupManager.h"
#include "FiltroManager.h"
#include "LogManager.h" // Agregamos la cabecera del LogManager

using namespace std;

// Prototipos de funciones
void menu();
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones);
void procesarSeleccion(int opcionSeleccionada, ListaCircularDoble<Autor>& autores, ListaCircularDoble<Libro>& libros, LogManager& logManager);
void cambiarColor(int color);
void realizarBackup(const ListaCircularDoble<Autor>& autores, const ListaCircularDoble<Libro>& libros, LogManager& logManager);
void restaurarBackup(ListaCircularDoble<Autor>& autores, ListaCircularDoble<Libro>& libros, LogManager& logManager);
void shellSort(ListaCircularDoble<Libro>& libros); // Función de Shell Sort para ordenar libros por título

int main() {
    menu();
    return 0;
}

void menu() {
    ListaCircularDoble<Autor> autores;
    ListaCircularDoble<Libro> libros;
    LogManager logManager("biblioteca_log.txt"); // Instancia del LogManager

    const int numOpciones = 10; // Agregamos una opción más para ordenar libros
    string opciones[numOpciones] = {
        "Ingresar libro",
        "Mostrar autores y libros",
        "Buscar por autor o libro",
        "Eliminar libro",
        "Filtrar libros por fecha",
        "Crear backup",
        "Restaurar backup",
        "Mostrar registro de eventos",
        "Ordenar libros por título", // Nueva opción
        "Salir"
    };
    int opcionSeleccionada = 0;

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch();

        if (tecla == 13) { // Enter
            system("cls");
            procesarSeleccion(opcionSeleccionada, autores, libros, logManager);
            if (opcionSeleccionada == 9) { // Salir
                break;
            }
            system("pause");
        } else if (tecla == -32) { // Teclas especiales
            tecla = _getch();
            if (tecla == 72) { // Arriba
                opcionSeleccionada = (opcionSeleccionada - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) { // Abajo
                opcionSeleccionada = (opcionSeleccionada + 1) % numOpciones;
            }
        }
    }
}

void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones) {
    system("cls");
    cout << "=== Biblioteca de Libros y Autores ===\n";
    for (int i = 0; i < numOpciones; ++i) {
        if (i == opcionSeleccionada) {
            cambiarColor(3); // Color destacado
            cout << " > " << opciones[i] << "\n";
            cambiarColor(7); // Color normal
        } else {
            cambiarColor(7);
            cout << "   " << opciones[i] << "\n";
        }
    }
}

void procesarSeleccion(int opcionSeleccionada, ListaCircularDoble<Autor>& autores, ListaCircularDoble<Libro>& libros, LogManager& logManager) {
    switch (opcionSeleccionada) {
        case 0: { // Ingresar libro
            string titulo, nombre, apellido, editorial;
            int dia, mes, anio;

            // Validaciones con mayúsculas
            titulo = Validaciones::ingresar_string_con_mayuscula("Titulo del libro: ");
            nombre = Validaciones::ingresar_string_con_mayuscula("Nombre del autor: ");
            apellido = Validaciones::ingresar_string_con_mayuscula("Apellido del autor: ");
            editorial = Validaciones::ingresar_string_con_mayuscula("Editorial: ");

            // Verificar si el autor ya existe
            Autor autorTemp(nombre, apellido, Fecha(1, 1, 1900)); // Fecha temporal
            bool autorExistente = autores.existe(autorTemp, [](const Autor& a, const Autor& b) { return a == b; });

            string fechaNacimiento;
            Fecha fechaNacimientoAutor(1, 1, 1900);
            Autor autor = autorTemp;

            if (!autorExistente) {
                // Validación de la fecha de nacimiento del autor si no existe
                fechaNacimiento = Validaciones::ingresar_fecha_nacimiento_autor(
                    "Fecha de nacimiento del autor (DD/MM/AAAA): "
                );
                sscanf(fechaNacimiento.c_str(), "%d/%d/%d", &dia, &mes, &anio);
                fechaNacimientoAutor = Fecha(dia, mes, anio);

                if (!fechaNacimientoAutor.esValida()) {
                    cout << "Fecha de nacimiento invalida.\n";
                    break;
                }

                autor = Autor(nombre, apellido, fechaNacimientoAutor);
                autores.agregar(autor);
            }

            // Validación de la fecha de publicación del libro
            string fechaPublicacionStr = Validaciones::ingresar_fecha_publicacion(
                "Fecha de publicacion (DD/MM/AAAA): ",
                fechaNacimiento
            );

            sscanf(fechaPublicacionStr.c_str(), "%d/%d/%d", &dia, &mes, &anio);
            Fecha fechaPublicacion(dia, mes, anio);

            if (!fechaPublicacion.esValida()) {
                cout << "Fecha invalida.\n";
                break;
            }

            // Agregar el libro
            libros.agregar(Libro(titulo, autor, fechaPublicacion, editorial));
            cout << "Libro agregado exitosamente.\n";
            logManager.escribirLog("Libro agregado: " + titulo);
            break;
        }
        case 1: // Mostrar autores y libros
            cout << "=== Autores ===\n";
            autores.imprimir([](const Autor& autor) {
                cout << "- " << autor.obtenerNombreCompleto() 
                     << " (Fecha de nacimiento: " << autor.obtenerFechaNacimiento() << ")" << endl;
            });

            cout << "\n=== Libros ===\n";
            libros.imprimir([](const Libro& libro) {
                cout << libro.obtenerInformacion() << endl;
            });
            logManager.escribirLog("Mostrando autores y libros.");
            break;

        case 2: { // Buscar por autor o libro
            string consulta = Validaciones::ingresar_string_con_mayuscula("Ingrese el autor o libro que desea buscar: ");

            cout << "\nResultados de busqueda para: " << consulta << "\n\n";

            cout << "Autores encontrados:\n";
            bool encontrado = false;
            autores.imprimir([&](const Autor& autor) {
                if (autor.obtenerNombreCompleto().find(consulta) != string::npos) {
                    cout << "- " << autor.obtenerNombreCompleto() 
                         << " (Fecha de nacimiento: " << autor.obtenerFechaNacimiento() << ")" << endl;
                    encontrado = true;
                }
            });

            cout << "\nLibros encontrados:\n";
            libros.imprimir([&](const Libro& libro) {
                if (libro.obtenerInformacion().find(consulta) != string::npos) {
                    cout << libro.obtenerInformacion() << endl;
                    encontrado = true;
                }
            });

            if (!encontrado) {
                cout << "No se encontraron coincidencias.\n";
            }
            logManager.escribirLog("Busqueda realizada: " + consulta);
            break;
        }
        case 3: { // Eliminar libro
            string codigo = to_string(Validaciones::ingresar_entero("Ingrese el codigo del libro a eliminar: "));
            if (libros.eliminarPorCodigo(codigo)) {
                cout << "Libro eliminado exitosamente.\n";
                logManager.escribirLog("Libro eliminado: Codigo " + codigo);
            } else {
                cout << "No se encontro un libro con el codigo especificado.\n";
            }
            break;
        }
        case 4: // Filtrar libros por fecha
            FiltroManager::filtrarLibrosPorFecha(libros);
            logManager.escribirLog("Filtro aplicado a libros por fecha.");
            break;
        case 5: // Crear backup
            realizarBackup(autores, libros, logManager);
            break;
        case 6: // Restaurar backup
            restaurarBackup(autores, libros, logManager);
            break;
        case 7: // Mostrar registro de eventos
            logManager.mostrarLog();
            break;
        case 8: { // Ordenar libros por título
            shellSort(libros);
            cout << "Libros ordenados por titulo.\n";
            logManager.escribirLog("Libros ordenados por título.");
            break;
        }
        case 9: // Salir
            cout << "Saliendo del programa...\n";
            logManager.escribirLog("El programa ha finalizado.");
            break;
    }
}

void realizarBackup(const ListaCircularDoble<Autor>& autores, const ListaCircularDoble<Libro>& libros, LogManager& logManager) {
    BackupManager backupManager;
    if (backupManager.crearBackup(libros, autores)) {
        cout << "Backup creado exitosamente.\n";
        logManager.escribirLog("Backup creado exitosamente.");
    } else {
        cout << "Error al crear el backup.\n";
        logManager.escribirLog("Error al crear el backup.");
    }
}

void restaurarBackup(ListaCircularDoble<Autor>& autores, ListaCircularDoble<Libro>& libros, LogManager& logManager) {
    BackupManager backupManager;
    auto backups = backupManager.obtenerListaBackups();

    if (backups.empty()) {
        cout << "No hay backups disponibles.\n";
        logManager.escribirLog("No hay backups disponibles para restaurar.");
        return;
    }

    cout << "Backups disponibles:\n";
    for (size_t i = 0; i < backups.size(); ++i) {
        cout << i + 1 << ". " << backups[i].timestamp << "\n";
    }

    cout << "Seleccione el numero de backup a restaurar (0 para cancelar): ";
    int opcion;
    cin >> opcion;

    if (opcion > 0 && opcion <= static_cast<int>(backups.size())) {
        if (backupManager.restaurarBackup(backups[opcion-1].timestamp, libros, autores)) {
            cout << "Backup restaurado exitosamente.\n";
            logManager.escribirLog("Backup restaurado: " + backups[opcion-1].timestamp);
        } else {
            cout << "Error al restaurar el backup.\n";  
            logManager.escribirLog("Error al restaurar el backup: " + backups[opcion-1].timestamp);
        }
    } else if (opcion != 0) {
        cout << "Opcion invalida.\n";
        logManager.escribirLog("Intento fallido de restaurar backup. Opcion invalida seleccionada.");
    }
}

void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void shellSort(ListaCircularDoble<Libro>& libros) {
    int n = libros.obtenerTamano(); // Obtener el tamaño de la lista
    if (n <= 1) return; // Si la lista tiene uno o menos elementos, no hay nada que ordenar

    // Definimos un comparador para ordenar los libros por título
    auto comparador = [](const Libro& a, const Libro& b) {
        return a.getTitulo() < b.getTitulo(); // Comparar por el título alfabéticamente
    };

    libros.ordenarShell(comparador); // Llamamos al método ordenarShell de ListaCircularDoble

    // Imprimir la lista ordenada
    cout << "Libros ordenados por titulo:\n";
    libros.imprimir([](const Libro& libro) {
        cout << libro.obtenerInformacion() << endl;  // Aquí se muestra la información del libro, puedes personalizar la salida
    });
}

