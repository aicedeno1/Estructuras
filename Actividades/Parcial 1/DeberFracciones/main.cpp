#include "Fraccion.cpp"
#include <stdio.h>

int ingresar(char *msj) {
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s\n", msj); // Salto de línea después del mensaje
    while((c = getch()) != 13) {
        if (c >= '0' && c <= '9') {
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8 && i > 0) {
            printf("\b \b");
            i--;
        }
    }
    cad[i] = '\0';
    valor = atoi(cad);
    return valor;
}

int main() {
    int num1, den1, num2, den2;

    do {
        num1 = ingresar("\nIngrese el numerador de la primera fraccion: ");
        den1 = ingresar("\nIngrese el denominador de la primera fraccion (mayor que 0):");
    } while (den1 <= 0);

    do {
        num2 = ingresar("\nIngrese el numerador de la segunda fraccion: ");
        den2 = ingresar("\nIngrese el denominador de la segunda fraccion (mayor que 0): ");
    } while (den2 <= 0);

    Fraccion<int> fraccion1(num1, den1);
    Fraccion<int> fraccion2(num2, den2);
    Calculo<int> calculo(fraccion1, fraccion2);

    Fraccion<int> resultado = calculo.sumar();
    printf("\nLa suma de las fracciones es: %d/%d\n", resultado.numerador, resultado.denominador);

    return 0;
}
