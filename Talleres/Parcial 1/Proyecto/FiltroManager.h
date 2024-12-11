#ifndef FILTRO_MANAGER_H
#define FILTRO_MANAGER_H

#include <string>
#include <ctime>
#include "ListaCircularDoble.h"
#include "Libro.h"
#include "Validaciones.h"

class FiltroManager {
public:
    // Método público para filtrar libros por rango de fechas
    static void filtrarLibrosPorFecha(ListaCircularDoble<Libro>& libros);

private:
    // Método auxiliar para convertir string de fecha a estructura tm
    static tm convertirFechaATime(const std::string& fecha);
    
    // Constructor privado para evitar instanciación
    FiltroManager() {}
};

#endif // FILTRO_MANAGER_H