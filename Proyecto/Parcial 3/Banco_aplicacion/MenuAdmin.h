#ifndef MENU_CLIENTE_H
#define MENU_CLIENTE_H

#include <memory>
#include "Banco.h"
#include "Cliente.h"

/**
 * @brief Muestra el menú de cliente y gestiona sus opciones
 * @param banco Referencia al banco
 * @param cliente Puntero al cliente autenticado
 */
void mostrarMenuCliente(Banco &banco, std::shared_ptr<Cliente> cliente);

/**
 * @brief Gestiona el cambio de información personal del cliente
 * @param cliente Puntero al cliente
 */
void gestionarCambioInformacionPersonal(std::shared_ptr<Cliente> cliente);

/**
 * @brief Gestiona las transferencias entre cuentas
 * @param banco Referencia al banco
 * @param cliente Puntero al cliente
 */
void gestionarTransferencia(Banco &banco, std::shared_ptr<Cliente> cliente);

/**
 * @brief Gestiona el pago de servicios
 * @param banco Referencia al banco
 * @param cliente Puntero al cliente
 */
void gestionarPagoServicio(Banco &banco, std::shared_ptr<Cliente> cliente);

/**
 * @brief Gestiona la visualización del historial de transacciones
 * @param cliente Puntero al cliente
 */
void verHistorialTransacciones(std::shared_ptr<Cliente> cliente);

/**
 * @brief Gestiona la visualización del gráfico de estado de cuenta
 * @param banco Referencia al banco
 * @param cliente Puntero al cliente
 */
void verGraficoEstadoCuenta(Banco &banco, std::shared_ptr<Cliente> cliente);

#endif // MENU_CLIENTE_H