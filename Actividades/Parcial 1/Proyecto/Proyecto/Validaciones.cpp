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

    while (true) {
        cout << mensaje;
        i = 0; // Reiniciar el índice en cada intento
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

        if (i == 0) { // Si no se ingresó nada
            cout << "\nEl campo no puede estar vacio. Intente nuevamente.\n";
        } else {
            break;
        }
    }

    num[i] = '\0'; 
    cout << endl;
    return atoi(num); 
}

string Validaciones::ingresar_string(const char* mensaje) {
    char cadena[100]; 
    char c;
    int i;

    while (true) {
        cout << mensaje;
        i = 0; // Reiniciar el índice en cada intento

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

        if (i == 0) { // Si no se ingresó nada
            cout << "\nEl campo no puede estar vacio. Intente nuevamente.\n";
        } else {
            break;
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

string Validaciones::ingresar_string_con_mayuscula(const char* mensaje) {
    char cadena[100]; 
    char c;
    int i;
    bool mayuscula = true;

    while (true) {
        cout << mensaje;
        i = 0; // Reiniciar el índice en cada intento

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

        if (i == 0) { // Si no se ingresó nada
            cout << "\nEl campo no puede estar vacio. Intente nuevamente.\n";
        } else {
            break;
        }
    }

    cadena[i] = '\0';
    cout << endl;
    return string(cadena);
}

string Validaciones::ingresar_fecha(const char* mensaje) {
    char fecha[11]; // DD/MM/AAAA
    char c;
    int i;

    while (true) {
        i = 0; // Reiniciar el índice en cada intento
        cout << mensaje;

        while (true) {
            c = _getch(); // Obtener un carácter

            if ((c >= '0' && c <= '9') || c == '/') {
                if (i < 10) { 
                    cout << c; 
                    fecha[i++] = c; 
                }
            } else if (c == 8 && i > 0) { // Backspace
                cout << "\b \b"; 
                i--;
            } else if (c == 13 && i == 10) { // Enter
                break;
            } else if (c == 13 && i == 0) { // Enter sin entrada
                cout << "\nEl campo no puede estar vacio. Intente nuevamente.\n";
                break;
            }
        }

        if (i == 0) continue;

        fecha[i] = '\0'; 
        cout << endl;

        int dia, mes, año;
        sscanf(fecha, "%d/%d/%d", &dia, &mes, &año);

        if (año > 2024) {
            cout << "El anio no puede ser mayor a 2024.\n";
            continue;
        }

        Fecha fechaValidada(dia, mes, año);
        if (fechaValidada.esValida()) {
            return string(fecha);
        } else {
            cout << "Fecha invalida. Por favor, intente nuevamente.\n";
        }
    }
}
