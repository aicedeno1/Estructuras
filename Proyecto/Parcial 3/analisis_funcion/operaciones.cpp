// operaciones.cpp
#include "operaciones.h"
#include <iostream>

// Implementaciones básicas
double suma(double a, double b) {
    return a + b;
}

double resta(double a, double b) {
    return a - b;
}

double multiplicacion(double a, double b) {
    return a * b;
}

double division(double a, double b) {
    if (b == 0) {
        std::cerr << "Error: División por cero" << std::endl;
        return 0;
    }
    return a / b;
}

// Implementaciones parametrizadas para análisis de complejidad
double suma_parametrizada(double a, double b, int n) {
    double resultado = 0;
    // O(n) - Complejidad lineal
    for (int i = 0; i < n; i++) {
        resultado += a + b;
    }
    return resultado / n;
}

double resta_parametrizada(double a, double b, int n) {
    double resultado = 0;
    // O(n) - Complejidad lineal
    for (int i = 0; i < n; i++) {
        resultado += a - b;
    }
    return resultado / n;
}

double multiplicacion_parametrizada(double a, double b, int n) {
    double resultado = 0;
    // O(n^2) - Simulamos complejidad cuadrática
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultado += a * b;
        }
    }
    return resultado / (n * n);
}

double division_parametrizada(double a, double b, int n) {
    if (b == 0) {
        std::cerr << "Error: División por cero" << std::endl;
        return 0;
    }
    
    double resultado = 0;
    // O(log n) - Simulamos complejidad logarítmica
    for (int i = 1; i <= n; i *= 2) {
        resultado += a / b;
    }
    
    // Contamos cuántas iteraciones hicimos
    int count = 0;
    for (int i = 1; i <= n; i *= 2) {
        count++;
    }
    
    return resultado / count;
}