#ifndef FECHA_H
#define FECHA_H

#include <string>

class Fecha {
private:
    int dia;
    int mes;
    int año;

public:
    Fecha(int dia, int mes, int año);

    std::string obtenerFecha() const; // Muestra la fecha en formato "DD/MM/YYYY"
    bool esValida() const; // Valida si la fecha es correcta
};

#endif
