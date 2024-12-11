#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

class Validaciones {
public:
    static int ingresar_entero(const char* mensaje);
    static std::string ingresar_string(const char* mensaje);
    static std::string ingresar_cedula(const char* mensaje);
    static std::string ingresar_string_con_mayuscula(const char* mensaje);
    
    // Métodos mejorados para fechas
    static std::string ingresar_fecha(const char* mensaje, int anioMinimo = 1900, const std::string& fechaReferencia = "");
    static std::string ingresar_fecha_nacimiento_autor(const char* mensaje);
    static std::string ingresar_fecha_publicacion(const char* mensaje, const std::string& fechaNacimientoAutor);
    
    static bool validar_edad(int diaNacimiento, int mesNacimiento, int anioNacimiento);
    static void ingresar_fecha_autor(const char* mensaje);

private:
    static bool esFechaMenor(const std::string& fecha1, const std::string& fecha2);
};

#endif
