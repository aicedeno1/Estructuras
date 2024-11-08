#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;


char* ingresar(const char*);
int ingresarInt(const char*);
float ingresarFloat(const char*);
string ingresarString(const char*);


char* ingresar(const char* msj) {
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


int ingresarInt(const char* msj) {
    char* cad = ingresar(msj); 
    return atoi(cad);          
}


float ingresarFloat(const char* msj) {
    char* cad = ingresar(msj); 
    return atof(cad);          
}


string ingresarString(const char* msj) {
    return string(ingresar(msj));  
}

int main() {
    
    char* letras = ingresar("Ingrese solo letras: ");
    int numero = ingresarInt("\nIngrese un número entero: ");
    float numeroFlotante = ingresarFloat("\nIngrese un número flotante: ");
    string texto = ingresarString("\nIngrese una palabra: ");

    // Mostrar los resultados
    cout << "\nLas letras ingresadas son: " << letras << endl;
    cout << "El número entero ingresado es: " << numero << endl;
    cout << "El número flotante ingresado es: " << numeroFlotante << endl;
    cout << "La palabra ingresada es: " << texto << endl;

    return 0;
}
