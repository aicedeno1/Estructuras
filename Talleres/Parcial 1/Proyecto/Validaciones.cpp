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
    bool prev_space = false; // Para detectar espacios consecutivos

    while (true) {
        cout << mensaje;
        i = 0; // Reiniciar el índice en cada intento
        prev_space = false; // Reiniciar el estado del espacio previo

        while ((c = _getch()) != 13) { // Enter
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
                if (i < 99) {
                    if (c == ' ' && prev_space) {
                        cout << "\nNo se pueden ingresar espacios consecutivos. Intente nuevamente.\n";
                        i = 0;  // Reiniciar la cadena
                        break;
                    }
                    if (c == ' ') {
                        prev_space = true;
                    } else {
                        prev_space = false;
                    }
                    cout << c; 
                    cadena[i++] = c;
                }
            } else if (c == 8 && i > 0) { // Backspace
                cout << "\b \b"; 
                prev_space = (i == 1); // Permitir espacio si es el primer carácter
                i--;
            }
        }

        if (i == 0) { // Si no se ingresó nada o solo espacios
            cout << "\nEl campo no puede estar vacio. Intente nuevamente.\n";
        } else {
            // Validación de que no haya solo espacios
            string str(cadena);
            if (str.find_first_not_of(" ") == string::npos) {
                cout << "\nEl campo no puede contener solo espacios. Intente nuevamente.\n";
            } else {
                break;
            }
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
    bool prev_space = false; // Para detectar espacios consecutivos

    while (true) {
        cout << mensaje;
        i = 0; // Reiniciar el índice en cada intento
        prev_space = false; // Reiniciar el estado del espacio previo

        while ((c = _getch()) != 13) { // Enter
            if (isalpha(c) || c == ' ') { // Acepta solo letras y espacio
                if (i < 99) {
                    if (c == ' ' && prev_space) {
                        cout << "\nNo se pueden ingresar espacios consecutivos. Intente nuevamente.\n";
                        i = 0;  // Reiniciar la cadena
                        break;
                    }
                    if (c == ' ') {
                        prev_space = true;
                    } else {
                        prev_space = false;
                    }

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
                prev_space = (i == 1); // Permitir espacio si es el primer carácter
                i--;
            }
        }

        if (i == 0) { // Si no se ingresó nada o solo espacios
            cout << "\nEl campo no puede estar vacio. Intente nuevamente.\n";
        } else {
            // Validación de que no haya solo espacios
            string str(cadena);
            if (str.find_first_not_of(" ") == string::npos) {
                cout << "\nEl campo no puede contener solo espacios. Intente nuevamente.\n";
            } else {
                break;
            }
        }
    }

    cadena[i] = '\0';
    cout << endl;
    return string(cadena);
}


string Validaciones::ingresar_fecha(const char* mensaje, int anioMinimo, const string& fechaReferencia) {
    char fecha[11]; // Formato DD/MM/AAAA
    char c;
    int i;

    // Obtener la fecha actual
    time_t t = time(nullptr);
    tm* fechaActual = localtime(&t);
    int anioActual = fechaActual->tm_year + 1900;
    int mesActual = fechaActual->tm_mon + 1;
    int diaActual = fechaActual->tm_mday;

    while (true) {
        i = 0;
        cout << mensaje;

        // Entrada de fecha
        while (true) {
            c = _getch();

            if ((c >= '0' && c <= '9') || c == '/') {
                if (i < 10) {
                    cout << c;
                    fecha[i++] = c;
                }
            } else if (c == 8 && i > 0) { // Backspace
                cout << "\b \b";
                i--;
            } else if (c == 13 && i == 10) { // Enter con entrada completa
                break;
            } else if (c == 13 && i == 0) { // Enter sin entrada
                cout << "\nEl campo no puede estar vacio. Intente nuevamente.\n";
                break;
            }
        }

        if (i == 0) continue;

        fecha[i] = '\0';
        cout << endl;

        int dia, mes, anio;
        if (sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio) != 3) {
            cout << "Formato de fecha invalido. Use DD/MM/AAAA.\n";
            continue;
        }

        // Validación básica de fecha
        if (anio < anioMinimo) {
            cout << "El anio debe ser mayor o igual a " << anioMinimo << ". Intente nuevamente.\n";
            continue;
        }
        if (anio > anioActual) {
            cout << "El anio no puede ser mayor al actual (" << anioActual << "). Intente nuevamente.\n";
            continue;
        }
        if (mes < 1 || mes > 12) {
            cout << "El mes debe estar entre 1 y 12. Intente nuevamente.\n";
            continue;
        }
        if (dia < 1 || dia > 31) {
            cout << "El dia debe estar entre 1 y 31. Intente nuevamente.\n";
            continue;
        }

        // Validación de días según el mes
        int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0)) {
            diasEnMes[1] = 29; // Año bisiesto
        }
        if (dia > diasEnMes[mes - 1]) {
            cout << "El mes " << mes << " solo tiene " << diasEnMes[mes - 1] << " dias.\n";
            continue;
        }

        // Validar que la fecha no sea futura
        if (anio == anioActual) {
            if (mes > mesActual || (mes == mesActual && dia > diaActual)) {
                cout << "La fecha no puede ser futura. Intente nuevamente.\n";
                continue;
            }
        }

        // Si hay fecha de referencia, validar que la fecha ingresada no sea anterior
        if (!fechaReferencia.empty() && esFechaMenor(fecha, fechaReferencia)) {
            cout << "La fecha no puede ser anterior a " << fechaReferencia << ". Intente nuevamente.\n";
            continue;
        }

        // Si todas las validaciones pasan, la fecha es válida
        return string(fecha);
    }
}


bool Validaciones::validar_edad(int diaNacimiento, int mesNacimiento, int anioNacimiento) {
    // Obtener la fecha actual
    time_t t = time(nullptr);
    tm* fechaActual = localtime(&t);
    int anioActual = fechaActual->tm_year + 1900;
    int mesActual = fechaActual->tm_mon + 1;
    int diaActual = fechaActual->tm_mday;

    // Calcular edad
    int edad = anioActual - anioNacimiento;

    if (mesNacimiento > mesActual || (mesNacimiento == mesActual && diaNacimiento > diaActual)) {
        edad--; // Restar un año si el cumpleaños aún no ha pasado este año
    }

    // Verificar si la edad es mayor o igual a 18 años
    return edad >= 18;
}

void Validaciones::ingresar_fecha_autor(const char* mensaje) {
    char fecha[11]; // Formato DD/MM/AAAA
    int dia, mes, anio;

    while (true) {
        cout << mensaje;
        cin.getline(fecha, 11);

        // Extraer día, mes y año de la cadena ingresada
        if (sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio) == 3) {
            if (anio >= 1900 && mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31) {
                if (validar_edad(dia, mes, anio)) {
                    cout << "La edad del autor es valida (mayor de 18 anios).\n";
                    break;
                } else {
                    cout << "El autor debe tener al menos 18 anios. Intente nuevamente.\n";
                }
            } else {
                cout << "Fecha invalida. Asegurese de que este en el formato DD/MM/AAAA y sea valida.\n";
            }
        } else {
            cout << "Formato incorrecto. Ingrese la fecha en el formato DD/MM/AAAA.\n";
      } 
 }
}
bool Validaciones::esFechaMenor(const string& fecha1, const string& fecha2) {
    int dia1, mes1, anio1, dia2, mes2, anio2;
    sscanf(fecha1.c_str(), "%d/%d/%d", &dia1, &mes1, &anio1);
    sscanf(fecha2.c_str(), "%d/%d/%d", &dia2, &mes2, &anio2);
    
    if (anio1 < anio2) return true;
    if (anio1 > anio2) return false;
    if (mes1 < mes2) return true;
    if (mes1 > mes2) return false;
    return dia1 < dia2;
}
string Validaciones::ingresar_fecha_nacimiento_autor(const char* mensaje) {
    return ingresar_fecha(mensaje, 1800); // Permitimos fechas desde 1800
}

string Validaciones::ingresar_fecha_publicacion(const char* mensaje, const string& fechaNacimientoAutor) {
    // La fecha de publicación debe ser posterior a la fecha de nacimiento del autor
    return ingresar_fecha(mensaje, 1800, fechaNacimientoAutor);
}
