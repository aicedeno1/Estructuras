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
    int i;
    bool valido = false;

    while (!valido) {
        cout << mensaje;
        i = 0;
        memset(num, 0, sizeof(num));  // Limpiar el array

        while ((c = _getch()) != 13) {  // Mientras no se presione Enter
            if (c >= '0' && c <= '9') {  // Si es un número
                if (i < 9) {
                    cout << c;
                    num[i++] = c;
                }
            }
            else if (c == 8 && i > 0) {  // Backspace
                cout << "\b \b";
                i--;
            }
            else if (c != 13) {  // Si no es número ni backspace ni enter
                // Reproducir un sonido de error
                cout << '\a';
            }
        }
        cout << endl;

        if (i == 0) {
            cout << "Error: Debe ingresar un número válido.\n";
            continue;
        }

        // Verificar que todos los caracteres son números
        bool todosNumeros = true;
        for (int j = 0; j < i; j++) {
            if (!isdigit(num[j])) {
                todosNumeros = false;
                break;
            }
        }

        if (todosNumeros) {
            num[i] = '\0';
            valido = true;
        }
        else {
            cout << "Error: Solo se permiten números.\n";
        }
    }

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
            if (isalpha(c)) { // Solo acepta letras
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

string Validaciones::ingresar_string_titulo(const char* mensaje) {
    char cadena[100]; 
    char c;
    int i;
    bool prev_space = false;
    bool mayuscula = true;

    while (true) {
        cout << mensaje;
        i = 0;
        prev_space = false;
        mayuscula = true;

        while ((c = _getch()) != 13) {
            if ((isalpha(c) || c == ' ')) {
                if (i < 99) {
                    if (c == ' ' && prev_space) {
                        continue;
                    }
                    if (c == ' ') {
                        prev_space = true;
                        mayuscula = true;
                    } else {
                        if (mayuscula && isalpha(c)) {
                            c = toupper(c);
                            mayuscula = false;
                        } else {
                            c = tolower(c);
                        }
                        prev_space = false;
                    }
                    cout << c; 
                    cadena[i++] = c;
                }
            } else if (c == 8 && i > 0) {
                cout << "\b \b"; 
                i--;
                if (i > 0) {
                    prev_space = (cadena[i-1] == ' ');
                    mayuscula = prev_space;
                } else {
                    prev_space = false;
                    mayuscula = true;
                }
            }
        }

        if (i == 0) {
            cout << "\nEl campo no puede estar vacio. Intente nuevamente.\n";
        } else if (cadena[i-1] == ' ') {
            cout << "\nEl texto no puede terminar en espacio. Intente nuevamente.\n";
        } else if (cadena[0] == ' ') {
            cout << "\nEl texto no puede empezar con espacio. Intente nuevamente.\n";
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
        i = 0;
        mayuscula = true;

        while ((c = _getch()) != 13) {
            if (isalpha(c)) {
                if (i < 99) {
                    if (mayuscula) {
                        c = toupper(c);
                        mayuscula = false;
                    } else {
                        c = tolower(c);
                    }
                    cout << c;
                    cadena[i++] = c;
                }
            } else if (c == 8 && i > 0) {
                cout << "\b \b"; 
                mayuscula = (i == 1);
                i--;
            }
        }

        if (i == 0) {
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
            cout << "El año no puede ser mayor a 2024. Por favor, ingrese una fecha válida en formato DD/MM/AAAA.\n";
            continue;
        }

        Fecha fechaValidada(dia, mes, año);
        if (fechaValidada.esValida()) {
            return string(fecha);
        } else {
            cout << "La fecha ingresada no es válida. Asegúrese de usar el formato correcto (DD/MM/AAAA) y que la fecha sea real.\n";
            cout << "Ejemplo: 31/12/2024.\n";
        }
    }
}
