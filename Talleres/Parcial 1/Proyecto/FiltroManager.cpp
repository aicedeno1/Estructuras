#include "FiltroManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>

void FiltroManager::filtrarLibrosPorFecha(ArbolBinario<Libro>& libros) {
    std::cout << "=== Filtrar Libros por Rango de Fechas ===\n\n";
    
    // Obtener fechas del rango
    std::string fechaInicio = Validaciones::ingresar_fecha(
        "Ingrese fecha de inicio (DD/MM/AAAA): "
    );
    std::string fechaFin = Validaciones::ingresar_fecha(
        "Ingrese fecha final (DD/MM/AAAA): "
    );
    
    // Convertir strings a tm para comparación
    tm tiempoInicio = convertirFechaATime(fechaInicio);
    tm tiempoFin = convertirFechaATime(fechaFin);
    
    // Convertir a time_t para comparación fácil
    time_t inicio = mktime(&tiempoInicio);
    time_t fin = mktime(&tiempoFin);
    
    std::cout << "\nLibros publicados entre " << fechaInicio << " y " << fechaFin << ":\n";
    std::cout << "==========================================\n\n";
    
    // Contador para libros encontrados
    int contadorLibros = 0;
    
    // Utilizar el método buscarPor del árbol para filtrar
    libros.buscarPor(
        [inicio, fin](const Libro& libro) {
            std::string fechaLib = libro.getFechaPublicacion().obtenerFecha();
            tm tiempoLib = convertirFechaATime(fechaLib);
            time_t fechaLibro = mktime(&tiempoLib);
            return fechaLibro >= inicio && fechaLibro <= fin;
        },
        [&contadorLibros](const Libro& libro) {
            std::cout << libro.obtenerInformacion() << std::endl;
            contadorLibros++;
        }
    );
    
    // Mostrar resumen
    std::cout << "\n==========================================\n";
    if (contadorLibros == 0) {
        std::cout << "No se encontraron libros en el rango de fechas especificado.\n";
    } else {
        std::cout << "Total de libros encontrados: " << contadorLibros << std::endl;
    }
}

tm FiltroManager::convertirFechaATime(const std::string& fecha) {
    tm tiempo = {};
    int dia, mes, anio;
    sscanf(fecha.c_str(), "%d/%d/%d", &dia, &mes, &anio);
    tiempo.tm_year = anio - 1900;  // Años desde 1900
    tiempo.tm_mon = mes - 1;       // Meses 0-11
    tiempo.tm_mday = dia;          // Días 1-31
    return tiempo;
}