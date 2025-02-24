// main.cpp
#include <iostream>
#include "operaciones.h"
#include <chrono>
#include <fstream>
#include <vector>

// Función para medir el tiempo de ejecución
template<typename Func, typename... Args>
double medir_tiempo(Func&& func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

// Función para generar datos para análisis de complejidad
void generar_datos_complejidad() {
    std::ofstream archivo("datos_complejidad.csv");
    archivo << "n,suma_tiempo,resta_tiempo,multiplicacion_tiempo,division_tiempo\n";
    
    // Tamaños de prueba
    std::vector<int> valores_n = {10, 100, 1000, 2000, 5000, 10000};
    
    for (int n : valores_n) {
        double tiempo_suma = medir_tiempo([n]() {
            suma_parametrizada(5.0, 3.0, n);
        });
        
        double tiempo_resta = medir_tiempo([n]() {
            resta_parametrizada(5.0, 3.0, n);
        });
        
        double tiempo_multiplicacion = medir_tiempo([n]() {
            multiplicacion_parametrizada(5.0, 3.0, n);
        });
        
        double tiempo_division = medir_tiempo([n]() {
            division_parametrizada(5.0, 3.0, n);
        });
        
        archivo << n << "," << tiempo_suma << "," << tiempo_resta << "," 
                << tiempo_multiplicacion << "," << tiempo_division << "\n";
    }
    
    archivo.close();
    std::cout << "Datos de complejidad generados en 'datos_complejidad.csv'" << std::endl;
}

int main() {
    double a = 10.0;
    double b = 5.0;
    
    std::cout << "Operaciones básicas:" << std::endl;
    std::cout << "Suma: " << suma(a, b) << std::endl;
    std::cout << "Resta: " << resta(a, b) << std::endl;
    std::cout << "Multiplicación: " << multiplicacion(a, b) << std::endl;
    std::cout << "División: " << division(a, b) << std::endl;
    
    std::cout << "\nGenerando datos para análisis de complejidad..." << std::endl;
    generar_datos_complejidad();
    
    return 0;
}