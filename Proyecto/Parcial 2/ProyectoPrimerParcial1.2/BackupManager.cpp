/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "BackupManager.h"
#include <iostream>
#include <windows.h>
#include <direct.h>
#include <sys/stat.h>
#include <algorithm>

void BackupManager::crearCarpetaSiNoExiste(const std::string &ruta)
{
    struct _stat st;

    if (_stat(ruta.c_str(), &st) != 0)
    {
        if (_mkdir(ruta.c_str()) == 0)
        {
            std::cout << "Carpeta creada: " << ruta << std::endl;
        }
        else
        {
            std::cerr << "Error al crear la carpeta: " << ruta << std::endl;
        }
    }
    else
    {
        std::cout << "La carpeta ya existe: " << ruta << std::endl;
    }
}

std::vector<std::string> BackupManager::listarArchivosEnCarpeta(const std::string &carpeta)
{
    std::vector<std::string> archivos;
    std::string path = carpeta + "\\*";
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error al acceder a la carpeta: " << carpeta << std::endl;
        return archivos;
    }

    do
    {
        std::string archivo = findFileData.cFileName;
        if (archivo != "." && archivo != "..")
        {
            archivos.push_back(archivo);
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
    return archivos;
}

void BackupManager::restaurarBackup(ArbolRojoNegro &arbol)
{
    std::string carpetaBackup = "backup";
    std::vector<std::string> archivos = listarArchivosEnCarpeta(carpetaBackup);

    if (archivos.empty())
    {
        std::cout << "No se encontraron archivos de backup en la carpeta " << carpetaBackup << ".\n";
        return;
    }

    std::cout << "Archivos disponibles para restaurar:\n";
    for (size_t i = 0; i < archivos.size(); ++i)
    {
        std::cout << i + 1 << ". " << archivos[i] << std::endl;
    }

    int seleccion;
    std::cout << "Seleccione un archivo para restaurar (ingrese el número): ";
    std::cin >> seleccion;

    // Validación de la entrada y limpieza del buffer
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Convertir seleccion a size_t para comparación segura
    if (seleccion < 1 || static_cast<size_t>(seleccion) > archivos.size())
    {
        std::cout << "Selección inválida.\n";
        return;
    }

    std::string archivoSeleccionado = carpetaBackup + "\\" + archivos[static_cast<size_t>(seleccion - 1)];
    arbol.restaurarBackup(archivoSeleccionado);
}
