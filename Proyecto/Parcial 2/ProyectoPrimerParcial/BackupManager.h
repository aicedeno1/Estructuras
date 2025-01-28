/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Gestionar Backups                          *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <string>
#include <vector>
#include "ListaCircularDoble.h"

class BackupManager {
public:
    // Métodos públicos de la clase
    static void crearCarpetaSiNoExiste(const std::string& ruta);
    static std::vector<std::string> listarArchivosEnCarpeta(const std::string& carpeta);
    static void restaurarBackup(ListaCircularDoble& lista);
};

#endif // BACKUPMANAGER_H
