#!/usr/bin/env python3
# graficar_complejidad.py
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Funciones para modelar diferentes complejidades
def complejidad_constante(n, a):
    return a * np.ones_like(n)

def complejidad_logaritmica(n, a, b):
    return a * np.log(n) + b

def complejidad_lineal(n, a, b):
    return a * n + b

def complejidad_nlogn(n, a, b):
    return a * n * np.log(n) + b

def complejidad_cuadratica(n, a, b):
    return a * n**2 + b

# Función para determinar la complejidad
def analizar_complejidad(n_valores, tiempos):
    funciones = [
        ("O(1)", complejidad_constante),
        ("O(log n)", complejidad_logaritmica),
        ("O(n)", complejidad_lineal),
        ("O(n log n)", complejidad_nlogn),
        ("O(n²)", complejidad_cuadratica)
    ]
    
    mejor_error = float('inf')
    mejor_nombre = ""
    mejor_params = None
    mejor_funcion = None
    
    for nombre, funcion in funciones:
        try:
            # Ajustar la función a los datos
            if funcion == complejidad_constante:
                params, _ = curve_fit(funcion, n_valores, tiempos)
                prediccion = funcion(n_valores, *params)
            else:
                params, _ = curve_fit(funcion, n_valores, tiempos)
                prediccion = funcion(n_valores, *params)
            
            # Calcular el error cuadrático medio
            error = np.mean((prediccion - tiempos)**2)
            
            if error < mejor_error:
                mejor_error = error
                mejor_nombre = nombre
                mejor_params = params
                mejor_funcion = funcion
        except:
            # Ignorar si el ajuste falla
            continue
    
    return mejor_nombre, mejor_funcion, mejor_params

# Cargar los datos
def main():
    try:
        datos = pd.read_csv("datos_complejidad.csv")
    except FileNotFoundError:
        print("Error: No se encontró el archivo 'datos_complejidad.csv'")
        print("Por favor, ejecute primero el programa principal en C++")
        return
    
    # Obtener valores de n y tiempos
    n_valores = datos['n'].values
    
    # Crear la figura
    plt.figure(figsize=(14, 10))
    
    # Definir las operaciones y sus colores
    operaciones = [
        ('suma_tiempo', 'Suma', 'blue'),
        ('resta_tiempo', 'Resta', 'green'),
        ('multiplicacion_tiempo', 'Multiplicación', 'red'),
        ('division_tiempo', 'División', 'purple')
    ]
    
    # Crear gráficas para cada operación
    for i, (columna, nombre, color) in enumerate(operaciones):
        tiempos = datos[columna].values
        complejidad, funcion, params = analizar_complejidad(n_valores, tiempos)
        
        # Crear una nueva figura para cada operación
        plt.subplot(2, 2, i+1)
        
        # Graficar datos originales
        plt.scatter(n_valores, tiempos, color=color, label='Datos')
        
        # Generar puntos para la curva de ajuste
        x_fit = np.linspace(min(n_valores), max(n_valores), 100)
        if funcion == complejidad_constante:
            y_fit = funcion(x_fit, *params)
        else:
            y_fit = funcion(x_fit, *params)
        
        # Graficar la curva de ajuste
        plt.plot(x_fit, y_fit, '--', color='black', label=f'Ajuste: {complejidad}')
        
        plt.title(f'Análisis de Complejidad: {nombre}')
        plt.xlabel('Tamaño (n)')
        plt.ylabel('Tiempo (ms)')
        plt.grid(True, linestyle='--', alpha=0.7)
        plt.legend()
    
    plt.tight_layout()
    plt.savefig('complejidad_python.png')
    plt.show()
    
    print("Gráfica guardada como 'complejidad_python.png'")

if __name__ == "__main__":
    main()