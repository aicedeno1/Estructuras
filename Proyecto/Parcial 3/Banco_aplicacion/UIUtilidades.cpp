#include "UIUtilidades.h"
#include "Validaciones.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib> // Para system

// Función para limpiar la pantalla de la consola
void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

std::string solicitarEntradaValidada(
    const std::string &mensaje, 
    const std::string &mensajeError, 
    bool (*funcionValidacion)(const std::string &)
) {
    std::string entrada;
    bool valido = false;
    
    while (!valido) {
        std::cout << mensaje;
        std::getline(std::cin, entrada);
        
        if (funcionValidacion(entrada)) {
            valido = true;
        } else {
            std::cout << mensajeError << std::endl;
        }
    }
    
    return entrada;
}

bool solicitarDatosNuevoCliente(Banco &banco) {
    std::cout << "\n=== REGISTRO DE NUEVO CLIENTE ===" << std::endl;
    
    // Solicitar y validar cédula primero
    std::string cedula;
    bool cedulaValida = false;
    
    while (!cedulaValida) {
        cedula = solicitarEntradaValidada(
            "Cédula: ", 
            "Error: Formato de cédula inválido. Debe contener solo números y tener entre 5 y 15 dígitos.", 
            validarCedula
        );
        
        // Verificar si la cédula ya existe
        if (banco.buscarClientePorCedula(cedula) != nullptr) {
            std::cout << "Error: Ya existe un cliente con esta cédula." << std::endl;
        } else {
            cedulaValida = true;
        }
    }
    
    // Solicitar y validar cada campo
    std::string nombres = solicitarEntradaValidada(
        "Nombres (solo letras, sin espacios): ", 
        "Error: Los nombres deben contener solo letras sin espacios.", 
        validarSoloLetras
    );
    
    std::string apellidos = solicitarEntradaValidada(
        "Apellidos (solo letras, sin espacios): ", 
        "Error: Los apellidos deben contener solo letras sin espacios.", 
        validarSoloLetras
    );
    
    std::string correo = solicitarEntradaValidada(
        "Correo electrónico: ", 
        "Error: Formato de correo inválido. Debe ser user@dominio.com", 
        validarCorreo
    );
    
    std::string telefono = solicitarEntradaValidada(
        "Teléfono (exactamente 10 dígitos): ", 
        "Error: El teléfono debe contener exactamente 10 dígitos sin espacios ni otros caracteres.", 
        validarTelefono
    );
    
    std::string direccion = solicitarEntradaValidada(
        "Dirección (solo letras y máximo un espacio): ", 
        "Error: La dirección debe contener solo letras y máximo un espacio.", 
        validarDireccion
    );
    
    std::string contrasena = solicitarEntradaValidada(
        "Contraseña (mínimo 6 caracteres): ", 
        "Error: La contraseña debe tener al menos 6 caracteres.", 
        validarContrasena
    );
    
    return banco.registrarCliente(cedula, nombres, apellidos, correo, telefono, direccion, contrasena);
}

std::shared_ptr<Cliente> solicitarBusquedaCliente(Banco &banco) {
    std::string cedula = solicitarEntradaValidada(
        "Ingrese la cédula del cliente a buscar: ",
        "Error: Formato de cédula inválido. Debe contener solo números y tener entre 5 y 15 dígitos.",
        validarCedula
    );
    
    return banco.buscarClientePorCedula(cedula);
}

bool crearRespaldo(const Banco &banco, const std::string &tipoArchivo) {
    std::string nombreArchivo = "respaldo_" + std::to_string(time(nullptr)) + "." + tipoArchivo;
    return banco.guardarRespaldo(nombreArchivo, tipoArchivo);
}