#ifndef UI_UTILIDADES_H
#define UI_UTILIDADES_H

#include <string>
#include <memory>
#include "Banco.h"
#include "Cliente.h"

/**
 * @brief Limpia la pantalla de la consola
 */
void limpiarPantalla();

/**
 * @brief Solicita y valida datos para crear un nuevo cliente
 * @param banco Referencia al banco donde se registrará el cliente
 * @return true si el cliente fue registrado exitosamente, false en caso contrario
 */
bool solicitarDatosNuevoCliente(Banco &banco);

/**
 * @brief Solicita y valida cédula para buscar un cliente
 * @param banco Referencia al banco donde se buscará el cliente
 * @return Puntero al cliente encontrado, nullptr si no se encontró
 */
std::shared_ptr<Cliente> solicitarBusquedaCliente(Banco &banco);

/**
 * @brief Solicita al usuario una cadena y la valida usando la función proporcionada
 * @param mensaje Mensaje a mostrar al usuario
 * @param mensajeError Mensaje a mostrar en caso de error
 * @param funcionValidacion Función que valida la entrada
 * @return Cadena validada
 */
std::string solicitarEntradaValidada(
    const std::string &mensaje, 
    const std::string &mensajeError, 
    bool (*funcionValidacion)(const std::string &)
);

/**
 * @brief Crea un respaldo de los datos del banco
 * @param banco Referencia al banco
 * @param tipoArchivo Tipo de archivo para el respaldo ("txt" o "csv")
 * @return true si el respaldo fue creado exitosamente, false en caso contrario
 */
bool crearRespaldo(const Banco &banco, const std::string &tipoArchivo);

#endif // UI_UTILIDADES_H