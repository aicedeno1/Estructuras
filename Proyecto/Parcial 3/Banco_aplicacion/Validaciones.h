#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

/**
 * @brief Valida que un string contenga solo números con posible punto decimal
 * @param str String a validar
 * @return true si es un número válido, false en caso contrario
 */
bool validarNumero(const std::string &str);

/**
 * @brief Valida que un string contenga solo letras (sin espacios, números o símbolos)
 * @param str String a validar
 * @return true si contiene solo letras, false en caso contrario
 */
bool validarSoloLetras(const std::string &str);

/**
 * @brief Valida el formato de una cédula de identidad
 * @param cedula String con la cédula a validar
 * @return true si es una cédula válida, false en caso contrario
 */
bool validarCedula(const std::string &cedula);

/**
 * @brief Valida el formato de un correo electrónico
 * @param correo String con el correo a validar
 * @return true si es un correo válido, false en caso contrario
 */
bool validarCorreo(const std::string &correo);

/**
 * @brief Valida el formato de un número de teléfono (exactamente 10 dígitos)
 * @param telefono String con el teléfono a validar
 * @return true si es un teléfono válido, false en caso contrario
 */
bool validarTelefono(const std::string &telefono);

/**
 * @brief Valida una contraseña según criterios de seguridad
 * @param contrasena String con la contraseña a validar
 * @return true si es una contraseña válida, false en caso contrario
 */
bool validarContrasena(const std::string &contrasena);

/**
 * @brief Valida que una dirección contenga solo letras y máximo un espacio
 * @param direccion String con la dirección a validar
 * @return true si es una dirección válida, false en caso contrario
 */
bool validarDireccion(const std::string &direccion);

/**
 * @brief Valida que un string no esté vacío
 * @param str String a validar
 * @return true si no está vacío, false en caso contrario
 */
bool validarNoVacio(const std::string &str);

#endif // VALIDACIONES_H