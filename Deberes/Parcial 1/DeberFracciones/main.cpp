#include <iostream>
#include "Validaciones1.h"
#include "Fraccion1.h"
#include "Calculo.h"

using namespace std;

int main() {
    Validaciones val;
    
    // Ingreso de datos para float
    cout << "---- Operaciones con flotantes ----" << endl;
    float num1 = val.ingresarFloat("Ingrese el numerador de la primera fraccion (float): ");
    float den1 = val.ingresarFloat("Ingrese el denominador de la primera fraccion (float): ");
    float num2 = val.ingresarFloat("Ingrese el numerador de la segunda fraccion (float): ");
    float den2 = val.ingresarFloat("Ingrese el denominador de la segunda fraccion (float): ");

    Fraccion<float> frac1(num1, den1);
    Fraccion<float> frac2(num2, den2);

    Calculo<float> calculoFloat(frac1, frac2);
    Fraccion<float> resultadoFloat = calculoFloat.sumar();
    cout << "Resultado de la suma (float): " << resultadoFloat.numerador << "/" << resultadoFloat.denominador << endl;

    // Ingreso de datos para double
    cout << "\n---- Operaciones con dobles ----" << endl;
    double num3 = val.ingresarDouble("Ingrese el numerador de la primera fraccion (double): ");
    double den3 = val.ingresarDouble("Ingrese el denominador de la primera fraccion (double): ");
    double num4 = val.ingresarDouble("Ingrese el numerador de la segunda fraccion (double): ");
    double den4 = val.ingresarDouble("Ingrese el denominador de la segunda fraccion (double): ");

    Fraccion<double> frac3(num3, den3);
    Fraccion<double> frac4(num4, den4);

    Calculo<double> calculoDouble(frac3, frac4);
    Fraccion<double> resultadoDouble = calculoDouble.sumar();
    cout << "Resultado de la suma (double): " << resultadoDouble.numerador << "/" << resultadoDouble.denominador << endl;

    return 0;
}
