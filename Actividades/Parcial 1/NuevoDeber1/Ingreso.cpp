#include "Ingreso.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

char* Ingreso::ingresar(const char* msj) {
    static char cad[100];
    char c;
    int i = 0;

    printf("%s", msj);

    while ((c = _getch()) != 13) { 
        printf("%c", c);
        cad[i++] = c;
    }

    cad[i] = '\0';
    return cad;
}

int Ingreso::ingresarInt(const char* msj) {
    char* cad = ingresar(msj);
    return atoi(cad);
}

float Ingreso::ingresarFloat(const char* msj) {
    char* cad = ingresar(msj);
    return atof(cad);
}

std::string Ingreso::ingresarString(const char* msj) {
    return std::string(ingresar(msj));
}
