#include <iostream>
#include <conio.h>
#include <windows.h>
#include "ListaCircularDoble.h"
#include "Autor.h"
#include "Libro.h"
#include "Fecha.h"
#include "Validaciones.h"

using namespace std;

// Prototipos de funciones
void menu();
void mostrarMenu(int opcionSeleccionada, const string opciones[], int numOpciones);
void procesarSeleccion(int opcionSeleccionada, ListaCircularDoble<Autor>& autores, ListaCircularDoble<Libro>& libros);
void cambiarColor(int color);

int main() {
    menu();
    return 0;
}

void menu() {
    ListaCircularDoble<Autor> autores;
    ListaCircularDoble<Libro> libros;

    const int numOpciones = 5;
    string opciones[numOpciones] = {"Ingresar libro", "Mostrar autores y libros", "Buscar por autor o libro", "Eliminar libro", "Salir"};
    int opcionSeleccionada = 0;

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch();

        if (tecla == 13) { 
            system("cls");
            procesarSeleccion(opcionSeleccionada, autores, libros);
            if (opcionSeleccionada == 4) { 
                break;
            }
        } else if (tecla == -32) { 
            tecla = _getch();
            if (tecla == 72) { 
                opcionSeleccionada = (opcionSeleccionada - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) { 
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
            cambiarColor(3); 
            cout << " > " << opciones[i] << "\n";
            cambiarColor(7); 
        } else {
            cambiarColor(7);
            cout << "   " << opciones[i] << "\n";
        }
    }
}

void procesarSeleccion(int opcionSeleccionada, ListaCircularDoble<Autor>& autores, ListaCircularDoble<Libro>& libros) {
    switch (opcionSeleccionada) {
        case 0: { 
            string titulo, nombre, apellido, editorial;
            int dia, mes, año;
            int diaNacimiento, mesNacimiento, añoNacimiento;

            // Validaciones con mayúsculas y fechas
            titulo = Validaciones::ingresar_string_con_mayuscula("Titulo del libro: ");
            nombre = Validaciones::ingresar_string_con_mayuscula("Nombre del autor: ");
            apellido = Validaciones::ingresar_string_con_mayuscula("Apellido del autor: ");
            editorial = Validaciones::ingresar_string_con_mayuscula("Editorial: ");

            // Verificar si el autor ya existe
            Autor autor(nombre, apellido, Fecha(0, 0, 0)); // Solo la fecha de nacimiento no se usa aquí
            bool autorExistente = autores.existe(autor, [](const Autor& a, const Autor& b) { return a == b; });

            if (autorExistente) {
                cout << "Este autor ya existe en la lista.\n";
            } else {
                // Validación de la fecha de nacimiento del autor si no existe
                string fechaNacimiento = Validaciones::ingresar_fecha("Fecha de nacimiento del autor (DD/MM/AAAA): ");
                sscanf(fechaNacimiento.c_str(), "%d/%d/%d", &diaNacimiento, &mesNacimiento, &añoNacimiento);
                Fecha fechaNacimientoAutor(diaNacimiento, mesNacimiento, añoNacimiento);

                if (!fechaNacimientoAutor.esValida()) {
                    cout << "Fecha de nacimiento invalida.\n";
                    break;
                }

                // Agregar el autor a la lista si no existía
                autores.agregar(Autor(nombre, apellido, fechaNacimientoAutor));
            }

            // Validación de la fecha de publicación del libro
            string fecha = Validaciones::ingresar_fecha("Fecha de publicacion (DD/MM/AAAA): ");
            sscanf(fecha.c_str(), "%d/%d/%d", &dia, &mes, &año);
            Fecha fechaPublicacion(dia, mes, año);

            if (!fechaPublicacion.esValida()) {
                cout << "Fecha invalida.\n";
                break;
            }

            // Agregar el libro (si el autor existía o fue agregado previamente)
            libros.agregar(Libro(titulo, autor, fechaPublicacion, editorial));
            cout << "Libro agregado exitosamente.\n";
            break;
        }
        case 1: 
            autores.imprimir([](const Autor& autor) { 
                cout << autor.obtenerNombreCompleto() << " (Fecha de nacimiento: " 
                     << autor.obtenerFechaNacimiento() << ")" << endl; 
            });
            libros.imprimir([](const Libro& libro) { cout << libro.obtenerInformacion() << endl; });
            break;
        case 2: { 
            // Aplicando la validación de mayúsculas en la búsqueda
            string consulta = Validaciones::ingresar_string_con_mayuscula("Ingrese el autor o libro que desea buscar: ");
            autores.imprimir([&](const Autor& autor) {
                if (autor.obtenerNombreCompleto().find(consulta) != string::npos) {
                    cout << "Autor encontrado: " << autor.obtenerNombreCompleto() << endl;
                }
            });
            libros.imprimir([&](const Libro& libro) {
                if (libro.obtenerInformacion().find(consulta) != string::npos) {
                    cout << "Libro encontrado: " << libro.obtenerInformacion() << endl;
                }
            });
            break;
        }
        case 3: { 
            int codigo = Validaciones::ingresar_entero("Ingrese el codigo del libro a eliminar: ");
            if (libros.eliminarPorCodigo(codigo)) {
                cout << "Libro eliminado exitosamente.\n";
            } else {
                cout << "No se encontro el libro con el codigo proporcionado.\n";
            }
            break;
        }
        case 4: 
            cout << "Saliendo del programa...\n";
            break;
    }
    system("pause");
}


void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
