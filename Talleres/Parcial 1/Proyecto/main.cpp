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

using namespace std;

// Prototipos de funciones
void menu();
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones);
void procesarSeleccion(int opcionSeleccionada, ListaCircularDoble<Autor>& autores, ListaCircularDoble<Libro>& libros);
void cambiarColor(int color);
void realizarBackup(const ListaCircularDoble<Autor>& autores, const ListaCircularDoble<Libro>& libros);
void restaurarBackup(ListaCircularDoble<Autor>& autores, ListaCircularDoble<Libro>& libros);

int main() {
    menu();
    return 0;
}

void menu() {
    ListaCircularDoble<Autor> autores;
    ListaCircularDoble<Libro> libros;

    const int numOpciones = 8;
    string opciones[numOpciones] = {
        "Ingresar libro",
        "Mostrar autores y libros",
        "Buscar por autor o libro",
        "Eliminar libro",
        "Filtrar libros por fecha",
        "Crear backup",
        "Restaurar backup",
        "Salir"
    };
    int opcionSeleccionada = 0;

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch();

        if (tecla == 13) { // Enter
            system("cls");
            procesarSeleccion(opcionSeleccionada, autores, libros);
            if (opcionSeleccionada == 7) { // Salir
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

void procesarSeleccion(int opcionSeleccionada, ListaCircularDoble<Autor>& autores, ListaCircularDoble<Libro>& libros) {
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
            } else {
                // Obtener la fecha de nacimiento del autor existente
                fechaNacimiento = autor.obtenerFechaNacimiento();
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
            break;

        case 2: { // Buscar por autor o libro
            string consulta = Validaciones::ingresar_string_con_mayuscula("Ingrese el autor o libro que desea buscar: ");
            
            cout << "\nResultados de búsqueda para: " << consulta << "\n\n";
            
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
            break;
        }
        case 3: { // Eliminar libro
            string codigo = to_string(Validaciones::ingresar_entero("Ingrese el codigo del libro a eliminar: "));
            if (libros.eliminarPorCodigo(codigo)) {
                cout << "Libro eliminado exitosamente.\n";
            } else {
                cout << "No se encontro un libro con el codigo especificado.\n";
            }
            break;
        }
        case 4: // Filtrar libros por fecha
            FiltroManager::filtrarLibrosPorFecha(libros);
            break;
        case 5: // Crear backup
            realizarBackup(autores, libros);
            break;
        case 6: // Restaurar backup
            restaurarBackup(autores, libros);
            break;
        case 7: // Salir
            cout << "Saliendo del programa...\n";
            break;
    }
}

void realizarBackup(const ListaCircularDoble<Autor>& autores, const ListaCircularDoble<Libro>& libros) {
    BackupManager backupManager;
    if (backupManager.crearBackup(libros, autores)) {
        cout << "Backup creado exitosamente.\n";
    } else {
        cout << "Error al crear el backup.\n";
    }
}

void restaurarBackup(ListaCircularDoble<Autor>& autores, ListaCircularDoble<Libro>& libros) {
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
        if (backupManager.restaurarBackup(backups[opcion-1].timestamp, libros, autores)) {
            cout << "Backup restaurado exitosamente.\n";
        } else {
            cout << "Error al restaurar el backup.\n";
        }
    } else if (opcion != 0) {
        cout << "Opcion invalida.\n";
    }
}

void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
