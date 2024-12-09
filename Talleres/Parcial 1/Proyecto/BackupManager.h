#ifndef BACKUP_MANAGER_H
#define BACKUP_MANAGER_H

#include <string>
#include <vector>
#include <ctime>
#include "ListaCircularDoble.h"
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
    
    bool crearBackup(const ListaCircularDoble<Libro>& libros, 
                    const ListaCircularDoble<Autor>& autores);
    
    bool restaurarBackup(const std::string& timestamp,
                        ListaCircularDoble<Libro>& libros,
                        ListaCircularDoble<Autor>& autores);
    
    std::vector<BackupInfo> obtenerListaBackups() const;
    bool eliminarBackup(const std::string& timestamp);
};

#endif