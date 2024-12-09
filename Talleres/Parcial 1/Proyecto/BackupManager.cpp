#include "BackupManager.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <direct.h>
#include <windows.h>
#include <iostream>
#include <map>

BackupManager::BackupManager(const std::string& directory) : backupDirectory(directory) {
    _mkdir(directory.c_str());
    cargarListaBackups();
}

std::string BackupManager::generarNombreArchivo() const {
    return backupDirectory + "backup_" + obtenerTimestamp() + ".txt";
}

std::string BackupManager::obtenerTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S");
    return ss.str();
}

void BackupManager::cargarListaBackups() {
    backupList.clear();
    
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((backupDirectory + "*.txt").c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::string filename = findFileData.cFileName;
            size_t start = filename.find("_") + 1;
            size_t end = filename.find(".txt");
            if (start != std::string::npos && end != std::string::npos) {
                std::string timestamp = filename.substr(start, end - start);
                backupList.push_back({backupDirectory + filename, timestamp});
            }
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
}

bool BackupManager::crearBackup(const ListaCircularDoble<Libro>& libros,
                              const ListaCircularDoble<Autor>& autores) {
    std::string filename = generarNombreArchivo();
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    // Guardar autores
    file << "AUTORES\n";
    autores.imprimir([&](const Autor& autor) {
        guardarObjeto(file, autor);
    });

    // Guardar libros
    file << "LIBROS\n";
    libros.imprimir([&](const Libro& libro) {
        guardarObjeto(file, libro);
    });

    file.close();
    cargarListaBackups();
    return true;
}

bool BackupManager::guardarObjeto(std::ofstream& file, const Libro& libro) const {
    file << "LIBRO|" 
         << libro.obtenerCodigo() << "|"
         << libro.getTitulo() << "|"
         << libro.getAutor().getNombre() << "|"
         << libro.getAutor().getApellido() << "|"
         << libro.getFechaPublicacion().obtenerFecha() << "|"
         << libro.getEditorial() << "\n";
    return true;
}

bool BackupManager::guardarObjeto(std::ofstream& file, const Autor& autor) const {
    file << "AUTOR|"
         << autor.getNombre() << "|"
         << autor.getApellido() << "|"
         << autor.obtenerFechaNacimiento() << "\n";
    return true;
}

bool BackupManager::restaurarBackup(const std::string& timestamp,
                                  ListaCircularDoble<Libro>& libros,
                                  ListaCircularDoble<Autor>& autores) {
    std::string filename = backupDirectory + "backup_" + timestamp + ".txt";
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::cout << "Iniciando restauración desde: " << filename << std::endl;

    // Limpiar las listas actuales
    libros.limpiar();
    autores.limpiar();

    std::string line;
    std::string seccion;
    std::map<std::string, Autor> mapaAutores;
    
    while (std::getline(file, line)) {
        // Eliminar retorno de carro si existe
        if (!line.empty() && line[line.length()-1] == '\r') {
            line = line.substr(0, line.length()-1);
        }

        std::cout << "Procesando línea: " << line << std::endl;

        if (line == "AUTORES") {
            seccion = "AUTORES";
            continue;
        }
        else if (line == "LIBROS") {
            seccion = "LIBROS";
            continue;
        }

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string tipo;
        std::getline(ss, tipo, '|');

        if (seccion == "AUTORES" && tipo == "AUTOR") {
        std::string nombre, apellido, fechaNac;
        std::getline(ss, nombre, '|');
        std::getline(ss, apellido, '|');
        std::getline(ss, fechaNac);
        
        int dia, mes, anio;
        sscanf(fechaNac.c_str(), "%d/%d/%d", &dia, &mes, &anio);
        Fecha fechaNacimiento(dia, mes, anio);
        
        Autor autor(nombre, apellido, fechaNacimiento);
        std::string autorKey = nombre + "|" + apellido;
        mapaAutores.emplace(autorKey, autor);
        autores.agregar(autor);
        
        std::cout << "Autor restaurado: " << nombre << " " << apellido << std::endl;
    }
        else if (seccion == "LIBROS" && tipo == "LIBRO") {
            std::string codigo, titulo, nombreAutor, apellidoAutor, fecha, editorial;
            
            std::getline(ss, codigo, '|');
            std::getline(ss, titulo, '|');
            std::getline(ss, nombreAutor, '|');
            std::getline(ss, apellidoAutor, '|');
            std::getline(ss, fecha, '|');
            std::getline(ss, editorial);
            
            std::string autorKey = nombreAutor + "|" + apellidoAutor;
            auto it = mapaAutores.find(autorKey);
            if (it != mapaAutores.end()) {
                int dia = 0, mes = 0, anio = 0;
                if (sscanf(fecha.c_str(), "%d/%d/%d", &dia, &mes, &anio) == 3) {
                    Fecha fechaPublicacion(dia, mes, anio);
                    
                    if (!fechaPublicacion.esValida()) {
                        std::cout << "Fecha inválida para el libro: " << titulo << std::endl;
                        continue;
                    }
                    
                    Libro libro(codigo, titulo, it->second, fechaPublicacion, editorial);
                    libros.agregar(libro);
                    
                    std::cout << "Libro restaurado: " << titulo << " por " << it->second.obtenerNombreCompleto() << std::endl;
                }
            }
        }
    }

    file.close();
    std::cout << "Restauración completada" << std::endl;
    return true;
}

std::vector<BackupInfo> BackupManager::obtenerListaBackups() const {
    return backupList;
}

bool BackupManager::eliminarBackup(const std::string& timestamp) {
    std::string filename = backupDirectory + "backup_" + timestamp + ".txt";
    if (DeleteFileA(filename.c_str())) {
        cargarListaBackups();
        return true;
    }
    return false;
}