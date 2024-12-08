#include <iostream>
#include "ListaCircularDoble.h"
#include "Autor.h"
#include "Libro.h"
#include "Validaciones.h"
#include <conio.h>  // Para capturar teclas direccionales

void mostrarAutores(const ListaCircularDoble<Autor>& autores, const ListaCircularDoble<Libro>& libros) {
    if (!autores.existe(Autor("", ""), [](const Autor& a, const Autor& b) {
        return a == b;
    })) {
        std::cout << "No hay autores registrados.\n";
        return;
    }

    autores.imprimir([&libros](const Autor& autor) {
        std::cout << autor.obtenerNombreCompleto() << ":\n";
        libros.imprimir([&autor](const Libro& libro) {
            if (libro.obtenerInformacion().find(autor.obtenerNombreCompleto()) != std::string::npos) {
                std::cout << " - " << libro.obtenerInformacion() << '\n';
            }
        });
    });
}

void buscarPorConsulta(const ListaCircularDoble<Autor>& autores, const ListaCircularDoble<Libro>& libros, const std::string& consulta) {
    bool encontrado = false;

    // Buscar por autor
    autores.imprimir([&consulta, &encontrado](const Autor& autor) {
        if (Validaciones::convertirMinusculas(autor.obtenerNombreCompleto()).find(
                Validaciones::convertirMinusculas(consulta)) != std::string::npos) {
            std::cout << "Autor encontrado: " << autor.obtenerNombreCompleto() << "\n";
            encontrado = true;
        }
    });

    // Buscar por libro
    libros.imprimir([&consulta, &encontrado](const Libro& libro) {
        if (Validaciones::convertirMinusculas(libro.obtenerInformacion()).find(
                Validaciones::convertirMinusculas(consulta)) != std::string::npos) {
            std::cout << "Libro encontrado: " << libro.obtenerInformacion() << "\n";
            encontrado = true;
        }
    });

    if (!encontrado) {
        std::cout << "No se encontraron resultados para: " << consulta << "\n";
    }
}

bool ingresarDatoValido(const std::string& mensaje, std::string& dato) {
    std::cout << mensaje;
    std::getline(std::cin, dato);

    dato = Validaciones::eliminarEspacios(dato);
    if (!Validaciones::esCadenaValida(dato)) {
        std::cout << "Entrada inválida. Solo se permiten letras y espacios.\n";
        return false;
    }
    return true;
}

int main() {
    ListaCircularDoble<Autor> autores;
    ListaCircularDoble<Libro> libros;

    int opcion = 0;
    bool continuar = true;
    int seleccion = 0;  // Variable para seguir la opción seleccionada

    // Opciones del menú
    std::string opciones[] = {
        "Ingresar libro",
        "Mostrar autores y sus libros",
        "Buscar por autor o libro",
        "Salir"
    };

    while (continuar) {
        // Mostrar las opciones con la opción seleccionada resaltada
        std::cout << "\nUsa las flechas arriba/abajo para navegar y Enter para seleccionar.\n";
        for (int i = 0; i < 4; ++i) {
            if (i == seleccion) {
                std::cout << "> " << opciones[i] << " <\n";  // Resalta la opción seleccionada
            } else {
                std::cout << opciones[i] << "\n";
            }
        }

        char tecla = _getch();  // Captura la tecla presionada

        // Si se presionó una tecla especial (flechas)
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();  // Lee el siguiente valor para las teclas especiales

            switch (tecla) {
            case 72:  // Flecha arriba
                if (seleccion > 0) seleccion--;  // Mueve hacia arriba
                break;
            case 80:  // Flecha abajo
                if (seleccion < 3) seleccion++;  // Mueve hacia abajo
                break;
            default:
                break;
            }
        }
        // Si se presionó Enter
        else if (tecla == 13) {
            // Ejecuta la acción según la opción seleccionada
            switch (seleccion) {
            case 0: {  // Ingresar libro
                std::string titulo, nombre, apellido;

                if (!ingresarDatoValido("Titulo del libro: ", titulo)) break;
                if (!ingresarDatoValido("Nombre del autor: ", nombre)) break;
                if (!ingresarDatoValido("Apellido del autor: ", apellido)) break;

                Autor autor(nombre, apellido);
                if (!autores.existe(autor, [](const Autor& a, const Autor& b) { return a == b; })) {
                    autores.agregar(autor);
                } else {
                    std::cout << "Este autor ya existe en la lista.\n";
                }
                libros.agregar(Libro(titulo, autor));
                std::cout << "Libro agregado exitosamente.\n";
                break;
            }
            case 1:  // Mostrar autores y libros
                mostrarAutores(autores, libros);
                break;
            case 2: {  // Buscar por autor o libro
                std::string consulta;
                std::cout << "Ingrese el autor o libro que desea buscar: ";
                std::getline(std::cin, consulta);
                buscarPorConsulta(autores, libros, consulta);
                break;
            }
            case 3:  // Salir
                continuar = false;
                std::cout << "Saliendo...\n";
                break;
            }
        }
    }

    return 0;
}
