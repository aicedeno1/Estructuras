#include "FiltroManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

tm FiltroManager::convertirFechaATime(const string& fecha) {
    tm tiempo = {};
    int dia, mes, anio;
    sscanf(fecha.c_str(), "%d/%d/%d", &dia, &mes, &anio);
    tiempo.tm_year = anio - 1900;  // Años desde 1900
    tiempo.tm_mon = mes - 1;       // Meses 0-11
    tiempo.tm_mday = dia;          // Días 1-31
    return tiempo;
}

void FiltroManager::filtrarLibrosPorFecha(ListaCircularDoble<Libro>& libros) {
    cout << "=== Filtrar Libros por Rango de Fechas ===\n\n";
    
    // Obtener fechas del rango
    string fechaInicio = Validaciones::ingresar_fecha("Ingrese fecha de inicio (DD/MM/AAAA): ");
    string fechaFin = Validaciones::ingresar_fecha("Ingrese fecha final (DD/MM/AAAA): ");
    
    // Convertir strings a tm para comparación
    tm tiempoInicio = convertirFechaATime(fechaInicio);
    tm tiempoFin = convertirFechaATime(fechaFin);
    
    // Convertir a time_t para comparación fácil
    time_t inicio = mktime(&tiempoInicio);
    time_t fin = mktime(&tiempoFin);
    
    cout << "\nLibros publicados entre " << fechaInicio << " y " << fechaFin << ":\n";
    cout << "==========================================\n\n";
    
    // Lambda para filtrar y mostrar los libros
    auto filtroFecha = [inicio, fin](const Libro& libro) {
        string fechaLib = libro.getFechaPublicacion().obtenerFecha();
        tm tiempoLib = convertirFechaATime(fechaLib);
        time_t fechaLibro = mktime(&tiempoLib);
        
        if (fechaLibro >= inicio && fechaLibro <= fin) {
            cout << libro.obtenerInformacion() << endl;
            return true;
        }
        return false;
    };
    
    // Contador para libros encontrados
    int contadorLibros = 0;
    
    // Aplicar el filtro y contar libros
    libros.imprimir([&](const Libro& libro) {
        if (filtroFecha(libro)) {
            contadorLibros++;
        }
    });
    
    // Mostrar resumen
    cout << "\n==========================================\n";
    if (contadorLibros == 0) {
        cout << "No se encontraron libros en el rango de fechas especificado.\n";
    } else {
        cout << "Total de libros encontrados: " << contadorLibros << endl;
    }
}