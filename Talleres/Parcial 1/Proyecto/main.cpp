#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Arboles.h"
#include "Autor.h"
#include "Libro.h"
#include "Fecha.h"
#include "Validaciones.h"
#include "BackupManager.h"
#include "FiltroManager.h"
#include "LogManager.h"
#include "FuncionesArboles.h"

using namespace std;

// Prototipos de funciones
void menu();
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones);
void procesarSeleccion(int opcionSeleccionada, BibliotecaManager& biblioteca);
void cambiarColor(int color);

int main() {
    menu();
    return 0;
}

void menu() {
    LogManager logManager("biblioteca_log.txt");
    BibliotecaManager biblioteca(logManager);

    const int numOpciones = 9;
    string opciones[numOpciones] = {
        "Ingresar libro",
        "Mostrar autores y libros",
        "Buscar por autor o libro",
        "Eliminar libro",
        "Filtrar libros por fecha",
        "Crear backup",
        "Restaurar backup",
        "Mostrar registro de eventos",
        "Salir"
    };
    int opcionSeleccionada = 0;

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch();

        if (tecla == 13) { // Enter
            system("cls");
            procesarSeleccion(opcionSeleccionada, biblioteca);
            if (opcionSeleccionada == 8) { // Salir
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

void procesarSeleccion(int opcionSeleccionada, BibliotecaManager& biblioteca) {
    switch (opcionSeleccionada) {
        case 0: { // Ingresar libro
            string titulo, nombre, apellido, editorial;
            
            titulo = Validaciones::ingresar_string_con_mayuscula("Titulo del libro: ");
            nombre = Validaciones::ingresar_string_con_mayuscula("Nombre del autor: ");
            apellido = Validaciones::ingresar_string_con_mayuscula("Apellido del autor: ");
            editorial = Validaciones::ingresar_string_con_mayuscula("Editorial: ");

            // Verificar si el autor ya existe
            Autor autorTemp(nombre, apellido, Fecha(1, 1, 1900));
            bool autorExistente = biblioteca.existeAutor(autorTemp);

            string fechaNacimiento;
            Fecha fechaNacimientoAutor(1, 1, 1900);
            Autor autor = autorTemp;

            if (!autorExistente) {
                fechaNacimiento = Validaciones::ingresar_fecha_nacimiento_autor(
                    "Fecha de nacimiento del autor (DD/MM/AAAA): "
                );
                int dia, mes, anio;
                sscanf(fechaNacimiento.c_str(), "%d/%d/%d", &dia, &mes, &anio);
                fechaNacimientoAutor = Fecha(dia, mes, anio);

                if (!fechaNacimientoAutor.esValida()) {
                    cout << "Fecha de nacimiento invalida.\n";
                    break;
                }

                autor = Autor(nombre, apellido, fechaNacimientoAutor);
                biblioteca.agregarAutor(autor);
            }

            string fechaPublicacionStr = Validaciones::ingresar_fecha_publicacion(
                "Fecha de publicacion (DD/MM/AAAA): ",
                fechaNacimiento
            );

            int dia, mes, anio;
            sscanf(fechaPublicacionStr.c_str(), "%d/%d/%d", &dia, &mes, &anio);
            Fecha fechaPublicacion(dia, mes, anio);

            if (!fechaPublicacion.esValida()) {
                cout << "Fecha invalida.\n";
                break;
            }

            Libro libro(titulo, autor, fechaPublicacion, editorial);
            if (biblioteca.agregarLibro(libro)) {
                cout << "Libro agregado exitosamente.\n";
            } else {
                cout << "Error al agregar el libro.\n";
            }
            break;
        }
        case 1: // Mostrar autores y libros
            biblioteca.mostrarAutores();
            cout << "\n";
            biblioteca.mostrarLibros();
            break;
        case 2: { // Buscar por autor o libro
            string consulta = Validaciones::ingresar_string_con_mayuscula(
                "Ingrese el autor o libro que desea buscar: "
            );
            biblioteca.buscarLibros(consulta);
            break;
        }
        case 3: { // Eliminar libro
            string codigo = to_string(Validaciones::ingresar_entero(
                "Ingrese el codigo del libro a eliminar: "
            ));
            if (biblioteca.eliminarLibro(codigo)) {
                cout << "Libro eliminado exitosamente.\n";
            } else {
                cout << "No se encontro el libro especificado.\n";
            }
            break;
        }
        case 4: // Filtrar libros por fecha
            FiltroManager::filtrarLibrosPorFecha(biblioteca.getLibros());
            break;
        case 5: // Crear backup
            {
                BackupManager backupManager;
                if (backupManager.crearBackup(biblioteca.getLibros(), biblioteca.getAutores())) {
                    cout << "Backup creado exitosamente.\n";
                } else {
                    cout << "Error al crear el backup.\n";
                }
            }
            break;
        case 6: // Restaurar backup
            {
                BackupManager backupManager;
                auto backups = backupManager.obtenerListaBackups();

                if (backups.empty()) {
                    cout << "No hay backups disponibles.\n";
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
                    if (backupManager.restaurarBackup(backups[opcion-1].timestamp, 
                                                    biblioteca.getLibros(), 
                                                    biblioteca.getAutores())) {
                        cout << "Backup restaurado exitosamente.\n";
                    } else {
                        cout << "Error al restaurar el backup.\n";
                    }
                }
            }
            break;
        case 7: // Mostrar registro de eventos
            biblioteca.logManager.mostrarLog();
            break;
        case 8: // Salir
            cout << "Saliendo del programa...\n";
            break;
    }
}

void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}