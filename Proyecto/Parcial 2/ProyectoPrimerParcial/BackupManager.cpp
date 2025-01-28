/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Gestionar Backups                                        *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "BackupManager.h"
#include <iostream>
#include <windows.h> // Para las funciones de Windows
#include <direct.h>  // Para mkdir en Windows
#include <sys/stat.h> // Para _stat
#include <fstream>   // Para trabajar con archivos

using namespace std;

// Implementación de los métodos de BackupManager

void BackupManager::crearCarpetaSiNoExiste(const string& ruta) {
    struct _stat st;

    // Verificar si la carpeta existe
    if (_stat(ruta.c_str(), &st) != 0) {
        // Si la carpeta no existe, la creamos
        if (_mkdir(ruta.c_str()) == 0) {
            cout << "Carpeta creada: " << ruta << endl;
        } else {
            cerr << "Error al crear la carpeta: " << ruta << endl;
        }
    } else {
        cout << "La carpeta ya existe: " << ruta << endl;
    }
}

vector<string> BackupManager::listarArchivosEnCarpeta(const string& carpeta) {
    vector<string> archivos;
    string path = carpeta + "\\*"; // Agregar comodín para buscar todos los archivos
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "Error al acceder a la carpeta: " << carpeta << endl;
        return archivos;
    }

    do {
        string archivo = findFileData.cFileName;
        if (archivo != "." && archivo != "..") { // Ignorar "." y ".."
            archivos.push_back(archivo);
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
    return archivos;
}

void BackupManager::restaurarBackup(ListaCircularDoble& lista) {
    string carpetaBackup = "backup"; // Carpeta donde se almacenan los backups
    vector<string> archivos = listarArchivosEnCarpeta(carpetaBackup);

    if (archivos.empty()) {
        cout << "No se encontraron archivos de backup en la carpeta " << carpetaBackup << ".\n";
        return;
    }

    // Mostrar los archivos disponibles
    cout << "Archivos disponibles para restaurar:\n";
    for (size_t i = 0; i < archivos.size(); ++i) {
        cout << i + 1 << ". " << archivos[i] << endl;
    }

    // Seleccionar archivo
    int seleccion;
    cout << "Seleccione un archivo para restaurar (ingrese el número): ";
    cin >> seleccion;

    if (seleccion < 1 || seleccion > archivos.size()) {
        cout << "Selección invalida.\n";
        return;
    }

    string archivoSeleccionado = carpetaBackup + "\\" + archivos[seleccion - 1];
    lista.restaurarBackup(archivoSeleccionado);
}
