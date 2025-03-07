/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación de la gestión de backups                  *
 * Autor:                          Diaz Stiven, Cedenio Andres                              *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "BackupManager.h"
#include <iostream>
#include <windows.h>
#include <direct.h>
#include <sys/stat.h>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

// Implementación de los métodos estáticos de BackupManager

void BackupManager::crearCarpetaSiNoExiste(const string &ruta)
{
    struct _stat st;

    // Verificar si la carpeta existe
    if (_stat(ruta.c_str(), &st) != 0)
    {
        // Si la carpeta no existe, la creamos
        if (_mkdir(ruta.c_str()) == 0)
        {
            cout << "Carpeta creada: " << ruta << endl;
        }
        else
        {
            cerr << "Error al crear la carpeta: " << ruta << endl;
        }
    }
}

vector<string> BackupManager::listarArchivosEnCarpeta(const string &carpeta)
{
    vector<string> archivos;
    string path = carpeta + "\\*"; // Agregar comodín para buscar todos los archivos
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        cerr << "Error al acceder a la carpeta: " << carpeta << endl;
        return archivos;
    }

    do
    {
        string archivo = findFileData.cFileName;
        if (archivo != "." && archivo != "..")
        { // Ignorar "." y ".."
            archivos.push_back(archivo);
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
    return archivos;
}

void BackupManager::restaurarBackupCuentas(ArbolCuentas &arbol)
{
    string carpetaBackup = "backup/cuentas"; // Carpeta donde se almacenan los backups de cuentas
    crearCarpetaSiNoExiste("backup");
    crearCarpetaSiNoExiste(carpetaBackup);

    vector<string> archivos = listarArchivosEnCarpeta(carpetaBackup);

    if (archivos.empty())
    {
        cout << "No se encontraron archivos de backup en la carpeta " << carpetaBackup << ".\n";
        return;
    }

    // Mostrar los archivos disponibles
    cout << "Archivos disponibles para restaurar:\n";
    for (size_t i = 0; i < archivos.size(); ++i)
    {
        cout << i + 1 << ". " << archivos[i] << endl;
    }

    // Seleccionar archivo
    int seleccion;
    cout << "Seleccione un archivo para restaurar (ingrese el número): ";
    cin >> seleccion;

    if (seleccion < 1 || seleccion > archivos.size())
    {
        cout << "Selección inválida.\n";
        return;
    }

    string archivoSeleccionado = carpetaBackup + "\\" + archivos[seleccion - 1];
    arbol.restaurarBackup(archivoSeleccionado);

    // Registrar operación
    registrarOperacion("RESTAURAR_BACKUP_CUENTAS", "Archivo: " + archivos[seleccion - 1]);
}

void BackupManager::restaurarBackupClientes(GestorClientes &gestor)
{
    string carpetaBackup = "backup/clientes"; // Carpeta donde se almacenan los backups de clientes
    crearCarpetaSiNoExiste("backup");
    crearCarpetaSiNoExiste(carpetaBackup);

    vector<string> archivos = listarArchivosEnCarpeta(carpetaBackup);

    if (archivos.empty())
    {
        cout << "No se encontraron archivos de backup en la carpeta " << carpetaBackup << ".\n";
        return;
    }

    // Mostrar los archivos disponibles
    cout << "Archivos disponibles para restaurar:\n";
    for (size_t i = 0; i < archivos.size(); ++i)
    {
        cout << i + 1 << ". " << archivos[i] << endl;
    }

    // Seleccionar archivo
    int seleccion;
    cout << "Seleccione un archivo para restaurar (ingrese el número): ";
    cin >> seleccion;

    if (seleccion < 1 || seleccion > archivos.size())
    {
        cout << "Selección inválida.\n";
        return;
    }

    string archivoSeleccionado = carpetaBackup + "\\" + archivos[seleccion - 1];
    gestor.restaurarBackup(archivoSeleccionado);

    // Registrar operación
    registrarOperacion("RESTAURAR_BACKUP_CLIENTES", "Archivo: " + archivos[seleccion - 1]);
}

void BackupManager::crearBackupCompleto(ArbolCuentas &arbol, GestorClientes &gestor)
{
    // Obtener fecha y hora actual para generar nombre de archivo único
    time_t ahora = time(0);
    tm *tiempo = localtime(&ahora);
    stringstream ss;
    ss << (1900 + tiempo->tm_year) << "_"
       << setw(2) << setfill('0') << (1 + tiempo->tm_mon) << "_"
       << setw(2) << setfill('0') << tiempo->tm_mday << "_"
       << setw(2) << setfill('0') << tiempo->tm_hour << "_"
       << setw(2) << setfill('0') << tiempo->tm_min << "_"
       << setw(2) << setfill('0') << tiempo->tm_sec;

    string fechaHora = ss.str();

    // Crear carpetas necesarias
    crearCarpetaSiNoExiste("backup");
    crearCarpetaSiNoExiste("backup/cuentas");
    crearCarpetaSiNoExiste("backup/clientes");

    // Nombres de archivos de backup
    string nombreBackupCuentas = "backup/cuentas/cuentas_" + fechaHora + ".txt";
    string nombreBackupClientes = "backup/clientes/clientes_" + fechaHora + ".txt";

    // Crear los backups
    arbol.crearBackup(nombreBackupCuentas);
    gestor.crearBackup(nombreBackupClientes);

    cout << "Backup completo creado correctamente con fecha: " << fechaHora << endl;

    // Registrar operación
    registrarOperacion("CREAR_BACKUP_COMPLETO", "Fecha: " + fechaHora);
}

void BackupManager::registrarOperacion(const string &operacion, const string &detalles)
{
    crearCarpetaSiNoExiste("logs");

    // Obtener fecha actual para el nombre del archivo de log
    time_t ahora = time(0);
    tm *tiempo = localtime(&ahora);

    stringstream ssNombreArchivo;
    ssNombreArchivo << "logs/log_"
                    << (1900 + tiempo->tm_year) << "_"
                    << setw(2) << setfill('0') << (1 + tiempo->tm_mon) << "_"
                    << setw(2) << setfill('0') << tiempo->tm_mday << ".txt";

    string nombreArchivo = ssNombreArchivo.str();

    // Abrir archivo en modo append
    ofstream archivo(nombreArchivo, ios::app);
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo de log: " << nombreArchivo << endl;
        return;
    }

    // Formatear hora actual para el registro
    stringstream ssHora;
    ssHora << setw(2) << setfill('0') << tiempo->tm_hour << ":"
           << setw(2) << setfill('0') << tiempo->tm_min << ":"
           << setw(2) << setfill('0') << tiempo->tm_sec;

    // Escribir el registro
    archivo << "[" << ssHora.str() << "] " << operacion << " - " << detalles << endl;

    archivo.close();
}
std::vector<std::string> BackupManager::obtenerHistorialOperaciones(const std::string &fecha)
{
    vector<string> lineasHistorial;
    string nombreArchivo = "logs/log_" + fecha + ".txt";

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cerr << "Error: No se encontró el archivo de historial para la fecha " << fecha << endl;
        return lineasHistorial;
    }

    string linea;
    while (getline(archivo, linea))
    {
        lineasHistorial.push_back(linea);
    }

    archivo.close();
    return lineasHistorial;
}

void BackupManager::limpiarHistorialOperaciones(int diasAntiguedad)
{
    // Obtener la fecha actual
    time_t ahora = time(0);
    tm *tiempo = localtime(&ahora);

    // Retroceder los días especificados
    tiempo->tm_mday -= diasAntiguedad;
    mktime(tiempo); // Normalizar la estructura de tiempo

    // Crear carpeta de logs si no existe
    crearCarpetaSiNoExiste("logs");

    // Listar archivos en la carpeta logs
    vector<string> archivos = listarArchivosEnCarpeta("logs");

    // Formato de nombre de archivo: log_YYYY_MM_DD.txt
    for (const auto &archivo : archivos)
    {
        if (archivo.substr(0, 4) == "log_")
        {
            // Extraer la fecha del nombre del archivo
            string fechaStr = archivo.substr(4, 10); // YYYY_MM_DD

            // Convertir a componentes de fecha
            int anio, mes, dia;
            sscanf(fechaStr.c_str(), "%d_%d_%d", &anio, &mes, &dia);

            // Crear estructura tm para la fecha del archivo
            // tm fechaArchivo = {0};
            tm fechaArchivo = {};
            fechaArchivo.tm_sec = 0;
            fechaArchivo.tm_min = 0;
            fechaArchivo.tm_hour = 0;
            fechaArchivo.tm_mday = 0;
            fechaArchivo.tm_mon = 0;
            fechaArchivo.tm_year = 0;
            fechaArchivo.tm_wday = 0;
            fechaArchivo.tm_yday = 0;
            fechaArchivo.tm_isdst = 0;

            // Convertir a time_t
            time_t tiempoArchivo = mktime(&fechaArchivo);

            // Comparar con la fecha límite
            if (tiempoArchivo < mktime(tiempo))
            {
                // Eliminar archivo si es más antiguo que la fecha límite
                string rutaCompleta = "logs/" + archivo;
                if (remove(rutaCompleta.c_str()) == 0)
                {
                    cout << "Archivo de historial eliminado: " << archivo << endl;
                }
                else
                {
                    cerr << "Error al eliminar archivo de historial: " << archivo << endl;
                }
            }
        }
    }

    cout << "Limpieza de historial completada." << endl;
}