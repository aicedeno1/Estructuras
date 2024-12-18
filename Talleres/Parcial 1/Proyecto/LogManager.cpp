#include "LogManager.h"

// Constructor
LogManager::LogManager(const std::string& fileName) : logFileName(fileName) {}

// Genera un timestamp actual
std::string LogManager::obtenerTimestamp() const {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", localTime);
    return std::string(buffer);
}

// Escribe un mensaje en el archivo de log
void LogManager::escribirLog(const std::string& mensaje) {
    std::ofstream logFile(logFileName, std::ios::app);
    if (logFile.is_open()) {
        logFile << obtenerTimestamp() << " " << mensaje << std::endl;
        logFile.close();
    }
}

// Muestra los registros en consola
void LogManager::mostrarLog() const {
    std::ifstream logFile(logFileName);
    if (logFile.is_open()) {
        std::string linea;
        while (std::getline(logFile, linea)) {
            std::cout << linea << std::endl;
        }
        logFile.close();
    } else {
        std::cout << "No se pudo abrir el archivo de log.\n";
    }
}
