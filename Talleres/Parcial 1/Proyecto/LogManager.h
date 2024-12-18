#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <fstream>
#include <string>
#include <ctime>
#include <iostream>

class LogManager {
private:
    std::string logFileName;

public:
    // Constructor
    LogManager(const std::string& fileName = "log.txt");

    // Escribe un mensaje en el archivo de log
    void escribirLog(const std::string& mensaje);

    // Muestra los registros en consola
    void mostrarLog() const;

    // Genera un timestamp actual (declaración, no definición)
    std::string obtenerTimestamp() const;
};

#endif // LOGMANAGER_H
