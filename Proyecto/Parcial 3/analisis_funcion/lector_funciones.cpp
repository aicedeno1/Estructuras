// lector_funciones.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

// Función para leer los nombres de las funciones en un archivo .h
std::vector<std::string> leer_funciones(const std::string& ruta_archivo) {
    std::vector<std::string> nombres_funciones;
    std::ifstream archivo(ruta_archivo);
    
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << ruta_archivo << std::endl;
        return nombres_funciones;
    }
    
    std::string linea;
    // Regex para encontrar declaraciones de funciones
    // Busca tipos de retorno seguidos de un nombre de función y parámetros
    std::regex patron_funcion(R"(([a-zA-Z_][a-zA-Z0-9_]*)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*;)");
    
    while (std::getline(archivo, linea)) {
        // Ignorar líneas de comentario y definiciones de macros
        if (linea.find("//") == 0 || linea.find("#") == 0) {
            continue;
        }
        
        std::smatch coincidencias;
        if (std::regex_search(linea, coincidencias, patron_funcion) && coincidencias.size() > 2) {
            // El grupo 2 contiene el nombre de la función
            nombres_funciones.push_back(coincidencias[2].str());
        }
    }
    
    archivo.close();
    return nombres_funciones;
}

int main(int argc, char* argv[]) {
    std::string ruta_archivo;
    
    if (argc > 1) {
        ruta_archivo = argv[1];
    } else {
        // Si no se proporciona la ruta como argumento, usar valor predeterminado
        ruta_archivo = "operaciones.h";
    }
    
    std::cout << "Leyendo funciones del archivo: " << ruta_archivo << std::endl;
    
    auto funciones = leer_funciones(ruta_archivo);
    
    if (funciones.empty()) {
        std::cout << "No se encontraron funciones en el archivo." << std::endl;
        return 1;
    }
    
    std::cout << "Funciones encontradas:" << std::endl;
    for (const auto& funcion : funciones) {
        std::cout << "- " << funcion << std::endl;
    }
    
    // Guardar los nombres de las funciones en un archivo para que los scripts de graficación los usen
    std::ofstream salida("funciones_encontradas.txt");
    for (const auto& funcion : funciones) {
        salida << funcion << std::endl;
    }
    salida.close();
    
    std::cout << "Nombres de funciones guardados en 'funciones_encontradas.txt'" << std::endl;
    
    return 0;
}