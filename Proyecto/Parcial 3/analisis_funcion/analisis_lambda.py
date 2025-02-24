#!/usr/bin/env python3
# analisis_lambda.py
# Este script utiliza funciones lambda para analizar la complejidad de las funciones

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import re
import os

# Definir funciones lambda para diferentes complejidades
complejidades = {
    'O(1)': lambda n, a: a * np.ones_like(n),
    'O(log n)': lambda n, a, b: a * np.log(n) + b,
    'O(n)': lambda n, a, b: a * n + b,
    'O(n log n)': lambda n, a, b: a * n * np.log(n) + b,
    'O(n²)': lambda n, a, b: a * n**2 + b
}

# Función para analizar la complejidad de una función basada en sus tiempos
def analizar_funcion(nombre_funcion, n_valores, tiempos):
    print(f"Analizando función: {nombre_funcion}")
    
    # Crear una figura para esta función específica
    plt.figure(figsize=(10, 6))
    plt.scatter(n_valores, tiempos, color='blue', label='Datos medidos')
    
    mejor_error = float('inf')
    mejor_ajuste = None
    mejor_nombre = None
    mejor_params = None
    
    # Probar cada modelo de complejidad
    for nombre, funcion in complejidades.items():
        try:
            if nombre == 'O(1)':
                params, _ = curve_fit(funcion, n_valores, tiempos)
                prediccion = funcion(n_valores, *params)
            else:
                params, _ = curve_fit(funcion, n_valores, tiempos)
                prediccion = funcion(n_valores, *params)
            
            # Calcular error
            error = np.mean((prediccion - tiempos)**2)
            
            print(f"  {nombre}: Error = {error:.6f}")
            
            if error < mejor_error:
                mejor_error = error
                mejor_ajuste = prediccion
                mejor_nombre = nombre
                mejor_params = params
        except Exception as e:
            print(f"  Error al ajustar {nombre}: {e}")
    
    # Generar una curva suave para graficar
    x_suave = np.linspace(min(n_valores), max(n_valores), 100)
    if mejor_nombre == 'O(1)':
        y_suave = complejidades[mejor_nombre](x_suave, *mejor_params)
    else:
        y_suave = complejidades[mejor_nombre](x_suave, *mejor_params)
    
    plt.plot(x_suave, y_suave, 'r-', label=f'Ajuste: {mejor_nombre}')
    
    plt.title(f'Análisis de Complejidad: {nombre_funcion}')
    plt.xlabel('Tamaño (n)')
    plt.ylabel('Tiempo (ms)')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend()
    
    # Guardar la gráfica
    archivo_salida = f"complejidad_{nombre_funcion}.png"
    plt.savefig(archivo_salida)
    plt.close()
    
    print(f"  Mejor ajuste: {mejor_nombre}")
    print(f"  Gráfica guardada como '{archivo_salida}'")
    print("-" * 50)
    
    return {
        'nombre': nombre_funcion,
        'complejidad': mejor_nombre,
        'error': mejor_error,
        'params': mejor_params
    }

def main():
    # Cargar los datos de complejidad
    try:
        datos = pd.read_csv("datos_complejidad.csv")
    except FileNotFoundError:
        print("Error: No se encontró el archivo 'datos_complejidad.csv'")
        print("Por favor, ejecute primero el programa principal en C++")
        return
    
    # Obtener valores de n
    n_valores = datos['n'].values
    
    # Mapeo de columnas a funciones
    mapeo_funciones = {
        'suma_tiempo': 'suma_parametrizada',
        'resta_tiempo': 'resta_parametrizada',
        'multiplicacion_tiempo': 'multiplicacion_parametrizada',
        'division_tiempo': 'division_parametrizada'
    }
    
    # Analizar cada función
    resultados = []
    
    for columna, funcion in mapeo_funciones.items():
        if columna in datos.columns:
            tiempos = datos[columna].values
            resultado = analizar_funcion(funcion, n_valores, tiempos)
            resultados.append(resultado)
    
    # Crear un informe resumido
    informe = pd.DataFrame(resultados)
    informe.to_csv("informe_complejidad.csv", index=False)
    print(f"Informe de complejidad guardado en 'informe_complejidad.csv'")
    
    # Mostrar un resumen en consola
    print("\nResumen de análisis de complejidad:")
    print("-" * 60)
    print(f"{'Función':<30} | {'Complejidad':<15} | {'Error':<10}")
    print("-" * 60)
    
    for res in resultados:
        print(f"{res['nombre']:<30} | {res['complejidad']:<15} | {res['error']:<10.6f}")

if __name__ == "__main__":
    main()