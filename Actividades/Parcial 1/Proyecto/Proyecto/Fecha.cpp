#include "Fecha.h"
#include <iostream>
#include <sstream>

Fecha::Fecha(int dia, int mes, int año) : dia(dia), mes(mes), año(año) {}

std::string Fecha::obtenerFecha() const {
    std::ostringstream fecha;
    fecha << (dia < 10 ? "0" : "") << dia << "/" 
          << (mes < 10 ? "0" : "") << mes << "/" 
          << año;
    return fecha.str();
}

bool Fecha::esValida() const {
    // Aquí puedes validar la fecha: comprobar si el mes es válido, si el día existe en ese mes, etc.
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;

    // Implementar validación para días específicos de los meses
    // Como ejemplo, no verificamos los años bisiestos, pero puedes incluirlo si es necesario
    return true;
}
