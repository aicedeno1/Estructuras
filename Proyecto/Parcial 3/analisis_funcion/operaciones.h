// operaciones.h
#ifndef OPERACIONES_H
#define OPERACIONES_H

// Operaciones matemáticas básicas
double suma(double a, double b);
double resta(double a, double b);
double multiplicacion(double a, double b);
double division(double a, double b);

// Versiones parametrizadas para análisis de complejidad
// Estas funciones realizan la operación n veces para simular diferentes complejidades
double suma_parametrizada(double a, double b, int n);
double resta_parametrizada(double a, double b, int n);
double multiplicacion_parametrizada(double a, double b, int n);
double division_parametrizada(double a, double b, int n);

#endif // OPERACIONES_H