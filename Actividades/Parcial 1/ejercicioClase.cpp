// IngresarDatos.cpp
#include "IngresarDatos.h"

char IngresarDatos::ingresarEntero(const std::string &mensaje) {
    std::string input;
    int valor;
    while (true) {
        try {
            std::cout << mensaje;
            std::cin >> input;
            valor = std::stoi(input);
            return static_cast<char>(valor);
        } catch (std::invalid_argument &e) {
            std::cerr << "Entrada inválida. Intente nuevamente.\n";
        } catch (std::out_of_range &e) {
            std::cerr << "Número fuera de rango. Intente nuevamente.\n";
        }
    }
}

char IngresarDatos::ingresarFlotante(const std::string &mensaje) {
    std::string input;
    float valor;
    while (true) {
        try {
            std::cout << mensaje;
            std::cin >> input;
            valor = std::stof(input);
            return static_cast<char>(valor);
        } catch (std::invalid_argument &e) {
            std::cerr << "Entrada inválida. Intente nuevamente.\n";
        } catch (std::out_of_range &e) {
            std::cerr << "Número fuera de rango. Intente nuevamente.\n";
        }
    }
}

char IngresarDatos::ingresarDouble(const std::string &mensaje) {
    std::string input;
    double valor;
    while (true) {
        try {
            std::cout << mensaje;
            std::cin >> input;
            valor = std::stod(input);
            return static_cast<char>(valor);
        } catch (std::invalid_argument &e) {
            std::cerr << "Entrada inválida. Intente nuevamente.\n";
        } catch (std::out_of_range &e) {
            std::cerr << "Número fuera de rango. Intente nuevamente.\n";
        }
    }
}
