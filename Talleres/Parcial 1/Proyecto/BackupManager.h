#ifndef BACKUP_MANAGER_H
#define BACKUP_MANAGER_H

#include <string>
#include <vector>
#include <ctime>
#include "Arboles.h"  // Se cambia a la declaración del encabezado correspondiente
#include "Libro.h"
#include "Autor.h"

struct BackupInfo {
    std::string filename;
    std::string timestamp;
};

class BackupManager {
private:
    std::string backupDirectory;
    std::vector<BackupInfo> backupList;

    std::string generarNombreArchivo() const;
    std::string obtenerTimestamp() const;
    void cargarListaBackups();
    bool guardarObjeto(std::ofstream& file, const Libro& libro) const;
    bool guardarObjeto(std::ofstream& file, const Autor& autor) const;

public:
    BackupManager(const std::string& directory = "backups/");

    bool crearBackup(const ArbolBinario<Libro>& libros, 
                     const ArbolBinario<Autor>& autores);

    bool restaurarBackup(const std::string& timestamp,
                         ArbolBinario<Libro>& libros,
                         ArbolBinario<Autor>& autores);

    std::vector<BackupInfo> obtenerListaBackups() const;
    bool eliminarBackup(const std::string& timestamp);
};

#endif
