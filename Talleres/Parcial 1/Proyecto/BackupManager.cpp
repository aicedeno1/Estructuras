#include "BackupManager.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <direct.h>
#include <windows.h>
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

bool BackupManager::crearBackup(const ArbolBinario<Libro>& libros, const ArbolBinario<Autor>& autores) {
    std::string filename = generarNombreArchivo();
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    // Guardar autores
    file << "AUTORES\n";
    autores.recorrer([&](const Autor& autor) {
        guardarObjeto(file, autor);
    });

    // Guardar libros
    file << "LIBROS\n";
    libros.recorrer([&](const Libro& libro) {
        guardarObjeto(file, libro);
    });

    file.close();
    cargarListaBackups();
    return true;
}

bool BackupManager::restaurarBackup(const std::string& timestamp, 
                                  ArbolBinario<Libro>& libros,
                                  ArbolBinario<Autor>& autores) {
    std::string filename = backupDirectory + "backup_" + timestamp + ".txt";
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    // Limpiar los árboles actuales
    libros.limpiar();
    autores.limpiar();

    std::string line;
    std::string seccion;
    std::map<std::string, Autor> mapaAutores;

    auto comparadorLibros = [](const Libro& a, const Libro& b) {
        return a.getTitulo() < b.getTitulo();
    };
    
    auto comparadorAutores = [](const Autor& a, const Autor& b) {
        return a.obtenerNombreCompleto() < b.obtenerNombreCompleto();
    };

    while (std::getline(file, line)) {
        if (line == "AUTORES") {
            seccion = "AUTORES";
            continue;
        }
        else if (line == "LIBROS") {
            seccion = "LIBROS";
            continue;
        }

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
            mapaAutores[autorKey] = autor;
            autores.insertar(autor, comparadorAutores);
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
                int dia, mes, anio;
                sscanf(fecha.c_str(), "%d/%d/%d", &dia, &mes, &anio);
                Fecha fechaPublicacion(dia, mes, anio);
                
                Libro libro(codigo, titulo, it->second, fechaPublicacion, editorial);
                libros.insertar(libro, comparadorLibros);
            }
        }
    }

    file.close();
    return true;
}

void BackupManager::cargarListaBackups() {
    backupList.clear();
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((backupDirectory + "backup_*.txt").c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::string filename = findFileData.cFileName;
            // Extraer el timestamp del nombre del archivo (backup_YYYYMMDD_HHMMSS.txt)
            std::string timestamp = filename.substr(7, 15); // 7 es la longitud de "backup_"
            BackupInfo info = {filename, timestamp};
            backupList.push_back(info);
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
}

bool BackupManager::eliminarBackup(const std::string& timestamp) {
    std::string filename = backupDirectory + "backup_" + timestamp + ".txt";
    if (DeleteFile(filename.c_str())) {
        cargarListaBackups();
        return true;
    }
    return false;
}

std::vector<BackupInfo> BackupManager::obtenerListaBackups() const {
    return backupList;
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