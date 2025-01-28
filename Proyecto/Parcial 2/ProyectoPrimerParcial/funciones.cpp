#include "funciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip> // Para std::setw y std::left

using namespace std;

// Función para dividir una línea por un delimitador
vector<string> dividir(const std::string& linea, char delimitador) {
    vector<string> partes;
    stringstream ss(linea);
    string parte;
    while (getline(ss, parte, delimitador)) {
        partes.push_back(parte);
    }
    return partes;
}

// Función para imprimir la cabecera formateada
void imprimirCabecera() {
    cout << left;
    cout << setw(40) << "Título"
         << setw(25) << "Autor"
         << setw(22) << "ISNI"
         << setw(20) << "ISBN"
         << setw(15) << "Publicación"
         << "Nac. Autor" << endl;

    cout << string(120, '-') << endl; // Línea divisoria
    cout << "\n";
}

// Función para buscar registros en un rango de años
void buscarPorRango(const std::string& rutaArchivo, int anioInicio, int anioFin) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    // Lambda para verificar si el año está en el rango
    auto filtrarPorRango = [anioInicio, anioFin](const string& fecha) {
        int anioPublicacion = stoi(fecha.substr(fecha.size() - 4));
        return anioPublicacion >= anioInicio && anioPublicacion <= anioFin;
    };

    bool cabeceraImprimida = false;

    while (getline(archivo, linea)) {
        vector<string> campos = dividir(linea, ';');
        if (campos.size() >= 6) {
            string titulo = campos[0];
            string autor = campos[1];
            string isni = campos[2];
            string fechaNacimiento = campos[3];
            string isbn = campos[4];
            string fechaPublicacion = campos[5];

            // Usamos la lambda para filtrar
            if (filtrarPorRango(fechaPublicacion)) {
                if (!cabeceraImprimida) {
                    imprimirCabecera();
                    cabeceraImprimida = true;
                }

                // Imprimimos el registro formateado
                cout << left;
                cout << setw(40) << titulo
                     << setw(25) << autor
                     << setw(22) << isni
                     << setw(20) << isbn
                     << setw(15) << fechaPublicacion
                     << fechaNacimiento << endl;
            }
        }
    }

    archivo.close();
}
