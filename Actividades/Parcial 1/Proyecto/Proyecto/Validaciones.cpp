#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <regex>
#include "Validaciones.h"
#include "Fecha.h"

using namespace std;

int Validaciones::ingresar_entero(const char* mensaje) {
    char num[10];
    char c;
    int i = 0;

    cout << mensaje;

    while ((c = _getch()) != 13) { // Enter
        if (c >= '0' && c <= '9') { // Números
            if (i < 9) { 
                cout << c; 
                num[i++] = c;
            }
        } else if (c == 8 && i > 0) { // Backspace
            cout << "\b \b"; 
            i--;
        }
    }

    num[i] = '\0'; 
    cout << endl;
    return atoi(num); 
}

string Validaciones::ingresar_string(const char* mensaje) {
    char cadena[100]; 
    char c;
    int i = 0;

    cout << mensaje;

    while ((c = _getch()) != 13) { // Enter
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
            if (i < 99) { 
                cout << c; 
                cadena[i++] = c;
            }
        } else if (c == 8 && i > 0) { // Backspace
            cout << "\b \b"; 
            i--;
        }
    }

    cadena[i] = '\0'; 
    cout << endl;
    return string(cadena);
}

string Validaciones::ingresar_cedula(const char* mensaje) {
    char cedula[11]; 
    char c;
    int i = 0;

    cout << mensaje;

    while (true) {
        c = _getch();

        if (c >= '0' && c <= '9') { 
            if (i < 10) { 
                cout << c; 
                cedula[i++] = c;
            }
        } else if (c == 8 && i > 0) { // Backspace
            cout << "\b \b"; 
            i--;
        } else if (c == 13) { // Enter
            if (i == 10) { 
                break;
            } else {
                cout << '\a'; 
            }
        }
    }

    cedula[i] = '\0'; 
    cout << endl;
    return string(cedula);
}

// Nuevo: String con mayúscula inicial
string Validaciones::ingresar_string_con_mayuscula(const char* mensaje) {
    char cadena[100]; 
    char c;
    int i = 0;
    bool mayuscula = true;

    cout << mensaje;

    while ((c = _getch()) != 13) { // Enter
        if (isalpha(c) || c == ' ') { // Acepta solo letras y espacio
            if (i < 99) {
                if (mayuscula && isalpha(c)) {
                    c = toupper(c); // Mayúscula inicial
                    mayuscula = false; // Bloquear más mayúsculas
                } else {
                    c = tolower(c); // Convertir a minúscula
                }
                cout << c;
                cadena[i++] = c;
            }
        } else if (c == 8 && i > 0) { // Backspace
            cout << "\b \b"; 
            mayuscula = (i == 1); // Permitir mayúscula si es el primer carácter
            i--;
        }
    }

    cadena[i] = '\0';
    cout << endl;
    return string(cadena);
}

// Nuevo: Validación de fecha
string Validaciones::ingresar_fecha(const char* mensaje) {
    char fecha[11]; // DD/MM/AAAA
    char c;
    int i;

    while (true) {
        i = 0; // Resetear el índice para cada intento de ingreso
        cout << mensaje;

        while (true) {
            c = _getch(); // Obtener un carácter

            // Aceptar solo números y '/' para la fecha
            if ((c >= '0' && c <= '9') || c == '/') {
                if (i < 10) { // Limitar la cantidad de caracteres
                    cout << c; // Mostrar el carácter
                    fecha[i++] = c; // Almacenar el carácter
                }
            } 
            // Permitir backspace para borrar caracteres
            else if (c == 8 && i > 0) {
                cout << "\b \b"; // Eliminar el último carácter mostrado
                i--; // Reducir el índice
            } 
            // Finalizar la entrada cuando se presiona Enter
            else if (c == 13 && i == 10) { // Fecha completa debe tener 10 caracteres (DD/MM/AAAA)
                break; // Salir del bucle si la fecha es válida
            } 
            // Si no es un número ni '/', no permitirlo
            else if (c != 8) {
                continue; // Ignorar cualquier otro carácter
            }
        }

        fecha[i] = '\0'; // Terminar la cadena
        cout << endl;

        // Separar la fecha
        int dia, mes, año;
        sscanf(fecha, "%d/%d/%d", &dia, &mes, &año);

        // Verificar si el año es mayor que 2024
        int añoLimite = 2024; // Año límite
        if (año > añoLimite) {
            cout << "El año no puede ser mayor a " << añoLimite << ".\n";
            continue;
        }

        // Crear el objeto Fecha para validación
        Fecha fechaValidada(dia, mes, año);

        // Si la fecha es válida, salir del bucle
        if (fechaValidada.esValida()) {
            return string(fecha); // Retornar la fecha válida
        } else {
            // Si la fecha no es válida, mostrar un mensaje y permitir reintentar
            cout << "Fecha invalida. Por favor, ingrese una fecha valida (DD/MM/AAAA).\n";
        }
    }
}

