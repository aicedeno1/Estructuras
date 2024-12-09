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
void cambiarColor(int color); // Función para cambiar el color del texto
bool ingresarDatoValido(const std::string& mensaje, std::string& dato);
void mostrarAutores(const ListaCircularDoble<Autor>& autores, const ListaCircularDoble<Libro>& libros);
void buscarPorConsulta(const ListaCircularDoble<Autor>& autores, const ListaCircularDoble<Libro>& libros, const std::string& consulta);

int main() {
    menu();
    return 0;
}

void menu() {
    ListaCircularDoble<Autor> autores;
    ListaCircularDoble<Libro> libros;

    const int numOpciones = 4;
    string opciones[numOpciones] = {"Ingresar libro", "Mostrar autores y libros", "Buscar por autor o libro", "Salir"};
    int opcionSeleccionada = 0;

    while (true) {
        mostrarMenu(opcionSeleccionada, opciones, numOpciones);
        char tecla = _getch();

        if (tecla == 13) { // Tecla Enter
            system("cls");
            procesarSeleccion(opcionSeleccionada, autores, libros);
            if (opcionSeleccionada == 3) { // Opción "Salir"
                break;
            }
        } else if (tecla == -32) { // Teclas especiales (flechas)
            tecla = _getch();
            if (tecla == 72) { // Flecha arriba
                opcionSeleccionada = (opcionSeleccionada - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) { // Flecha abajo
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
            cambiarColor(3); // Color destacado para la opción seleccionada
            cout << " > " << opciones[i] << "\n";
            cambiarColor(7); // Regresa al color normal
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
            int dia, mes, año;

            // Ingresar los datos
            if (!ingresarDatoValido("Titulo del libro: ", titulo)) break;
            if (!ingresarDatoValido("Nombre del autor: ", nombre)) break;
            if (!ingresarDatoValido("Apellido del autor: ", apellido)) break;

            cout << "Fecha de publicación (DD MM AAAA): ";
            cin >> dia >> mes >> año;

            // Validamos la fecha antes de continuar
            Fecha fechaPublicacion(dia, mes, año);
            if (!fechaPublicacion.esValida()) {
                cout << "Fecha inválida. Intente nuevamente.\n";
                break;
            }

            cin.ignore();  // Limpiar el buffer de entrada

            cout << "Editorial: ";
            getline(cin, editorial);

            // Creando el autor correctamente
            Autor autor(nombre, apellido);
            if (!autores.existe(autor, [](const Autor& a, const Autor& b) { return a == b; })) {
                autores.agregar(autor);
            } else {
                cout << "Este autor ya existe en la lista.\n";
            }

            // Agregando el libro con el autor
            libros.agregar(Libro(titulo, autor, fechaPublicacion, editorial));
            cout << "Libro agregado exitosamente.\n";
            break;
        }
        case 1: // Mostrar autores y libros
            mostrarAutores(autores, libros);
            break;
        case 2: { // Buscar por autor o libro
            string consulta;
            cout << "Ingrese el autor o libro que desea buscar: ";
            getline(cin, consulta);
            buscarPorConsulta(autores, libros, consulta);
            break;
        }
        case 3: // Salir
            cout << "Saliendo del programa...\n";
            break;
    }
    system("pause"); // Pausa antes de regresar al menú
}

void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool ingresarDatoValido(const std::string& mensaje, std::string& dato) {
    cout << mensaje;
    getline(cin, dato);

    // Verificar si la entrada es válida usando la clase Validaciones
    while (!Validaciones::esCadenaValida(dato)) {
        cout << "Entrada inválida. Intente nuevamente: ";
        getline(cin, dato);
    }

    return true;
}

void mostrarAutores(const ListaCircularDoble<Autor>& autores, const ListaCircularDoble<Libro>& libros) {
    cout << "Autores y Libros: \n";

    autores.imprimir([](const Autor& autor) {
        cout << autor.obtenerNombreCompleto() << endl;
    });

    libros.imprimir([](const Libro& libro) {
        cout << libro.obtenerInformacion() << endl;
    });
}

void buscarPorConsulta(const ListaCircularDoble<Autor>& autores, const ListaCircularDoble<Libro>& libros, const std::string& consulta) {
    bool encontrado = false;

    // Buscar en los autores
    autores.imprimir([&](const Autor& autor) {
        if (Validaciones::convertirMinusculas(autor.obtenerNombreCompleto()).find(Validaciones::convertirMinusculas(consulta)) != std::string::npos) {
            cout << "Autor encontrado: " << autor.obtenerNombreCompleto() << endl;
            encontrado = true;
        }
    });

    // Buscar en los libros
    libros.imprimir([&](const Libro& libro) {
        if (Validaciones::convertirMinusculas(libro.obtenerInformacion()).find(Validaciones::convertirMinusculas(consulta)) != std::string::npos) {
            cout << "Libro encontrado: " << libro.obtenerInformacion() << endl;
            encontrado = true;
        }
    });

    if (!encontrado) {
        cout << "No se encontró el autor o libro.\n";
    }
}
