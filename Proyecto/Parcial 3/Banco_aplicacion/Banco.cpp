#include "Banco.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>
#include <ctime>

Banco::Banco(const std::string &nombre) : nombre(nombre), ultimoNumeroCuenta(1000)
{
}

std::string Banco::generarNumeroCuenta()
{
    // Generar un número de cuenta único
    ultimoNumeroCuenta++;
    std::stringstream ss;
    ss << "10" << std::setw(8) << std::setfill('0') << ultimoNumeroCuenta;
    return ss.str();
}

bool Banco::registrarCliente(const std::string &cedula, const std::string &nombres,
                             const std::string &apellidos, const std::string &correo,
                             const std::string &telefono, const std::string &direccion,
                             const std::string &contrasena)
{
    // Verificar si ya existe un cliente con esa cédula
    if (clientes.find(cedula) != clientes.end())
    {
        std::cout << "Error: Ya existe un cliente con la cédula " << cedula << std::endl;
        return false;
    }

    // Crear nuevo cliente
    auto nuevoCliente = std::make_shared<Cliente>(cedula, nombres, apellidos,
                                                  correo, telefono, direccion,
                                                  contrasena);

    // Agregar al mapa de clientes
    clientes[cedula] = nuevoCliente;

    std::cout << "Cliente registrado exitosamente." << std::endl;
    return true;
}

std::shared_ptr<Cliente> Banco::buscarClientePorCedula(const std::string &cedula)
{
    auto it = clientes.find(cedula);
    if (it != clientes.end())
    {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<Cliente> Banco::autenticarCliente(const std::string &cedula, const std::string &contrasena)
{
    auto cliente = buscarClientePorCedula(cedula);

    if (cliente && cliente->verificarContrasena(contrasena) && cliente->isActivo())
    {
        return cliente;
    }

    return nullptr;
}

void Banco::listarClientes() const
{
    std::cout << "===== LISTA DE CLIENTES =====" << std::endl;
    std::cout << std::left << std::setw(15) << "CÉDULA"
              << std::setw(30) << "NOMBRE"
              << std::setw(25) << "CORREO"
              << "ESTADO" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (const auto &par : clientes)
    {
        const auto &cliente = par.second;
        std::cout << std::left << std::setw(15) << cliente->getCedula()
                  << std::setw(30) << cliente->getNombreCompleto()
                  << std::setw(25) << cliente->getCorreo()
                  << (cliente->isActivo() ? "Activo" : "Inactivo") << std::endl;
    }
}

bool Banco::crearCuenta(const std::string &cedulaCliente, TipoCuenta tipo, double saldoInicial)
{
    auto cliente = buscarClientePorCedula(cedulaCliente);

    if (!cliente)
    {
        std::cout << "Error: Cliente no encontrado." << std::endl;
        return false;
    }

    if (!cliente->isActivo())
    {
        std::cout << "Error: El cliente está inactivo." << std::endl;
        return false;
    }

    if (saldoInicial < 0)
    {
        std::cout << "Error: El saldo inicial no puede ser negativo." << std::endl;
        return false;
    }

    // Generar número de cuenta
    std::string numeroCuenta = generarNumeroCuenta();

    // Crear la cuenta
    auto nuevaCuenta = std::make_shared<Cuenta>(numeroCuenta, saldoInicial, tipo);

    // Agregar la cuenta al cliente
    cliente->agregarCuenta(nuevaCuenta);

    std::cout << "Cuenta creada exitosamente: " << numeroCuenta << std::endl;
    return true;
}

std::shared_ptr<Cuenta> Banco::buscarCuentaPorNumero(const std::string &numeroCuenta)
{
    // Buscar en todos los clientes
    for (const auto &par : clientes)
    {
        auto cuenta = par.second->buscarCuentaPorNumero(numeroCuenta);
        if (cuenta)
        {
            return cuenta;
        }
    }

    return nullptr;
}

bool Banco::realizarTransferencia(const std::string &numeroCuentaOrigen,
                                  const std::string &numeroCuentaDestino,
                                  double monto,
                                  const std::string &descripcion)
{
    if (monto <= 0)
    {
        std::cout << "Error: El monto debe ser positivo." << std::endl;
        return false;
    }

    auto cuentaOrigen = buscarCuentaPorNumero(numeroCuentaOrigen);
    auto cuentaDestino = buscarCuentaPorNumero(numeroCuentaDestino);

    if (!cuentaOrigen)
    {
        std::cout << "Error: Cuenta origen no encontrada." << std::endl;
        return false;
    }

    if (!cuentaDestino)
    {
        std::cout << "Error: Cuenta destino no encontrada." << std::endl;
        return false;
    }

    return cuentaOrigen->transferir(*cuentaDestino, monto, descripcion);
}

bool Banco::pagarServicio(const std::string &numeroCuenta, const std::string &tipoServicio,
                          double monto, const std::string &referencia)
{
    auto cuenta = buscarCuentaPorNumero(numeroCuenta);

    if (!cuenta)
    {
        std::cout << "Error: Cuenta no encontrada." << std::endl;
        return false;
    }

    std::string descripcion = "Pago de " + tipoServicio + " - Ref: " + referencia;
    return cuenta->retirar(monto, descripcion);
}

void Banco::mostrarGraficoEstadoCuenta(const std::string &numeroCuenta) const
{
    auto cuenta = const_cast<Banco *>(this)->buscarCuentaPorNumero(numeroCuenta);

    if (!cuenta)
    {
        std::cout << "Error: Cuenta no encontrada." << std::endl;
        return;
    }

    // Obtener historial de transacciones
    const auto &transacciones = cuenta->getHistorialTransacciones();

    if (transacciones.empty())
    {
        std::cout << "No hay transacciones para mostrar en el gráfico." << std::endl;
        return;
    }

    std::cout << "\n===== GRÁFICO DE ESTADO DE CUENTA =====" << std::endl;
    std::cout << "Cuenta: " << numeroCuenta << " - Saldo actual: $"
              << std::fixed << std::setprecision(2) << cuenta->getSaldo() << std::endl;

    // Determinar el máximo valor para el gráfico
    double maxSaldo = 0;
    for (const auto &trans : transacciones)
    {
        if (trans.getSaldoResultante() > maxSaldo)
        {
            maxSaldo = trans.getSaldoResultante();
        }
    }

    // Mostrar gráfico ASCII básico
    const int ANCHO_GRAFICO = 50;
    const int NUM_TRANS_MOSTRAR = std::min(10, static_cast<int>(transacciones.size()));

    std::cout << std::string(80, '-') << std::endl;

    // Mostrar las últimas N transacciones
    for (int i = std::max(0, static_cast<int>(transacciones.size()) - NUM_TRANS_MOSTRAR);
         i < transacciones.size(); i++)
    {
        const auto &trans = transacciones[i];

        // Convertir time_t a estructura tm para formatear la fecha
        time_t fechaHora = trans.getFechaHora();  // Guarda el resultado en una variable
        struct tm *timeinfo = localtime(&fechaHora); // Pasa la dirección de la variable
        char buffer[20];

        strftime(buffer, 20, "%d/%m", timeinfo);

        // Calcular longitud de la barra
        int longitud = static_cast<int>((trans.getSaldoResultante() / maxSaldo) * ANCHO_GRAFICO);

        std::cout << std::left << std::setw(8) << buffer;
        std::cout << " $" << std::right << std::setw(10) << std::fixed << std::setprecision(2)
                  << trans.getSaldoResultante() << " |";

        // Dibujar la barra
        std::cout << std::string(longitud, '#') << std::endl;
    }

    std::cout << std::string(80, '-') << std::endl;
}

void Banco::mostrarEstadisticas() const
{
    std::cout << "\n===== ESTADÍSTICAS GENERALES =====" << std::endl;

    // Estadísticas de clientes
    int totalClientes = clientes.size();
    int clientesActivos = 0;
    for (const auto &par : clientes)
    {
        if (par.second->isActivo())
        {
            clientesActivos++;
        }
    }

    // Estadísticas de cuentas
    int totalCuentas = 0;
    int cuentasAhorros = 0;
    int cuentasCorriente = 0;
    double saldoTotal = 0.0;
    double saldoPromedioAhorros = 0.0;
    double saldoPromedioCorriente = 0.0;
    double saldoTotalAhorros = 0.0;
    double saldoTotalCorriente = 0.0;

    for (const auto &par : clientes)
    {
        const auto &cuentasCliente = par.second->getCuentas();
        totalCuentas += cuentasCliente.size();

        for (const auto &cuenta : cuentasCliente)
        {
            saldoTotal += cuenta->getSaldo();

            if (cuenta->getTipo() == AHORROS)
            {
                cuentasAhorros++;
                saldoTotalAhorros += cuenta->getSaldo();
            }
            else
            {
                cuentasCorriente++;
                saldoTotalCorriente += cuenta->getSaldo();
            }
        }
    }

    if (cuentasAhorros > 0)
    {
        saldoPromedioAhorros = saldoTotalAhorros / cuentasAhorros;
    }

    if (cuentasCorriente > 0)
    {
        saldoPromedioCorriente = saldoTotalCorriente / cuentasCorriente;
    }

    // Mostrar estadísticas
    std::cout << "Clientes registrados: " << totalClientes << std::endl;
    std::cout << "Clientes activos: " << clientesActivos << " ("
              << (totalClientes > 0 ? (clientesActivos * 100.0 / totalClientes) : 0) << "%)" << std::endl;
    std::cout << "Total de cuentas: " << totalCuentas << std::endl;
    std::cout << "Cuentas de ahorro: " << cuentasAhorros << std::endl;
    std::cout << "Cuentas corrientes: " << cuentasCorriente << std::endl;
    std::cout << "Saldo total en el banco: $" << std::fixed << std::setprecision(2) << saldoTotal << std::endl;
    std::cout << "Saldo promedio en cuentas de ahorro: $" << saldoPromedioAhorros << std::endl;
    std::cout << "Saldo promedio en cuentas corrientes: $" << saldoPromedioCorriente << std::endl;
}

bool Banco::guardarDatos(const std::string &rutaArchivo) const
{
    // Implementación básica para guardar datos
    // En un sistema real, se utilizaría una base de datos o un formato más robusto
    std::ofstream archivo(rutaArchivo);

    if (!archivo.is_open())
    {
        std::cout << "Error: No se pudo abrir el archivo para guardar los datos." << std::endl;
        return false;
    }

    // Guardar información del banco
    archivo << nombre << "\n";
    archivo << ultimoNumeroCuenta << "\n";

    // Guardar número de clientes
    archivo << clientes.size() << "\n";

    // Guardar información de cada cliente
    for (const auto &par : clientes)
    {
        const auto &cliente = par.second;

        // Datos básicos del cliente
        archivo << cliente->getCedula() << ";"
                << cliente->getNombres() << ";"
                << cliente->getApellidos() << ";"
                << cliente->getCorreo() << ";"
                << cliente->getTelefono() << ";"
                << cliente->getDireccion() << ";"
                << (cliente->isActivo() ? "1" : "0") << "\n";

        // Número de cuentas
        const auto &cuentas = cliente->getCuentas();
        archivo << cuentas.size() << "\n";

        // Información de cada cuenta
        for (const auto &cuenta : cuentas)
        {
            archivo << cuenta->getNumeroCuenta() << ";"
                    << cuenta->getTipo() << ";"
                    << cuenta->getSaldo() << ";"
                    << (cuenta->isActiva() ? "1" : "0") << "\n";

            // Guardar transacciones (simplificado)
            const auto &transacciones = cuenta->getHistorialTransacciones();
            archivo << transacciones.size() << "\n";

            for (const auto &trans : transacciones)
            {
                archivo << trans.getTipo() << ";"
                        << trans.getMonto() << ";"
                        << trans.getSaldoResultante() << ";"
                        << trans.getDescripcion() << ";"
                        << trans.getFechaHora() << "\n";
            }
        }
    }

    archivo.close();
    std::cout << "Datos guardados exitosamente." << std::endl;
    return true;
}

bool Banco::guardarRespaldo(const std::string &nombreArchivo, const std::string &tipoArchivo) const
{
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        std::cout << "Error: No se pudo crear el archivo de respaldo." << std::endl;
        return false;
    }

    // Cabecera del archivo
    if (tipoArchivo == "csv")
    {
        archivo << "Tipo,Cédula,Nombres,Apellidos,Correo,Teléfono,Estado,NumeroCuenta,TipoCuenta,Saldo,EstadoCuenta\n";
    }
    else
    {
        archivo << "===== RESPALDO DE DATOS DEL BANCO " << nombre << " =====" << std::endl;
        archivo << "Fecha de respaldo: " << std::time(nullptr) << std::endl;
        archivo << std::string(80, '-') << std::endl;
    }

    // Datos de clientes y cuentas
    for (const auto &par : clientes)
    {
        const auto &cliente = par.second;
        const auto &cuentas = cliente->getCuentas();

        if (tipoArchivo == "csv")
        {
            // Formato CSV
            if (cuentas.empty())
            {
                // Cliente sin cuentas
                archivo << "CLIENTE,"
                        << cliente->getCedula() << ","
                        << cliente->getNombres() << ","
                        << cliente->getApellidos() << ","
                        << cliente->getCorreo() << ","
                        << cliente->getTelefono() << ","
                        << (cliente->isActivo() ? "Activo" : "Inactivo") << ",,,,"
                        << "\n";
            }
            else
            {
                // Cliente con cuentas
                for (const auto &cuenta : cuentas)
                {
                    archivo << "CLIENTE,"
                            << cliente->getCedula() << ","
                            << cliente->getNombres() << ","
                            << cliente->getApellidos() << ","
                            << cliente->getCorreo() << ","
                            << cliente->getTelefono() << ","
                            << (cliente->isActivo() ? "Activo" : "Inactivo") << ","
                            << cuenta->getNumeroCuenta() << ","
                            << (cuenta->getTipo() == AHORROS ? "AHORROS" : "CORRIENTE") << ","
                            << cuenta->getSaldo() << ","
                            << (cuenta->isActiva() ? "Activa" : "Inactiva") << "\n";
                }
            }
        }
        else
        {
            // Formato TXT
            archivo << "CLIENTE: " << cliente->getCedula() << " - "
                    << cliente->getNombreCompleto() << std::endl;
            archivo << "Correo: " << cliente->getCorreo() << std::endl;
            archivo << "Teléfono: " << cliente->getTelefono() << std::endl;
            archivo << "Estado: " << (cliente->isActivo() ? "Activo" : "Inactivo") << std::endl;

            if (cuentas.empty())
            {
                archivo << "No tiene cuentas registradas." << std::endl;
            }
            else
            {
                archivo << "CUENTAS:" << std::endl;
                for (const auto &cuenta : cuentas)
                {
                    archivo << "  - Número: " << cuenta->getNumeroCuenta()
                            << " | Tipo: " << (cuenta->getTipo() == AHORROS ? "AHORROS" : "CORRIENTE")
                            << " | Saldo: $" << std::fixed << std::setprecision(2) << cuenta->getSaldo()
                            << " | Estado: " << (cuenta->isActiva() ? "Activa" : "Inactiva") << std::endl;
                }
            }
            archivo << std::string(80, '-') << std::endl;
        }
    }

    archivo.close();
    return true;
}

bool Banco::cargarDatos(const std::string &rutaArchivo)
{
    std::ifstream archivo(rutaArchivo);

    if (!archivo.is_open())
    {
        std::cout << "Error: No se pudo abrir el archivo para cargar los datos." << std::endl;
        return false;
    }

    try
    {
        // Limpiar datos actuales
        clientes.clear();

        // Leer información del banco
        std::string linea;
        std::getline(archivo, nombre);
        std::getline(archivo, linea);
        ultimoNumeroCuenta = std::stoi(linea);

        // Leer número de clientes
        std::getline(archivo, linea);
        int numClientes = std::stoi(linea);

        // Leer información de cada cliente
        for (int i = 0; i < numClientes; i++)
        {
            std::getline(archivo, linea);
            std::stringstream ss(linea);
            std::string cedula, nombres, apellidos, correo, telefono, direccion, activoStr;

            std::getline(ss, cedula, ';');
            std::getline(ss, nombres, ';');
            std::getline(ss, apellidos, ';');
            std::getline(ss, correo, ';');
            std::getline(ss, telefono, ';');
            std::getline(ss, direccion, ';');
            std::getline(ss, activoStr, ';');

            // Crear cliente (con contraseña temporal que deberá cambiar)
            auto nuevoCliente = std::make_shared<Cliente>(cedula, nombres, apellidos,
                                                          correo, telefono, direccion,
                                                          "temp123");

            // Establecer estado
            if (activoStr == "0")
            {
                nuevoCliente->desactivar();
            }

            // Leer número de cuentas
            std::getline(archivo, linea);
            int numCuentas = std::stoi(linea);

            // Leer información de cada cuenta
            for (int j = 0; j < numCuentas; j++)
            {
                std::getline(archivo, linea);
                std::stringstream ssCuenta(linea);
                std::string numeroCuenta, tipoStr, saldoStr, activaStr;

                std::getline(ssCuenta, numeroCuenta, ';');
                std::getline(ssCuenta, tipoStr, ';');
                std::getline(ssCuenta, saldoStr, ';');
                std::getline(ssCuenta, activaStr, ';');

                TipoCuenta tipo = (tipoStr == "0") ? AHORROS : CORRIENTE;
                double saldo = std::stod(saldoStr);

                // Crear cuenta
                auto nuevaCuenta = std::make_shared<Cuenta>(numeroCuenta, saldo, tipo);

                // Establecer estado
                if (activaStr == "0")
                {
                    nuevaCuenta->desactivar();
                }

                // Leer número de transacciones
                std::getline(archivo, linea);
                int numTransacciones = std::stoi(linea);

                // Leer transacciones (simplificado, en realidad esto requeriría más trabajo)
                for (int k = 0; k < numTransacciones; k++)
                {
                    std::getline(archivo, linea); // Simplemente saltamos las líneas de transacciones
                }

                // Agregar cuenta al cliente
                nuevoCliente->agregarCuenta(nuevaCuenta);
            }

            // Agregar cliente al banco
            clientes[cedula] = nuevoCliente;
        }

        archivo.close();
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error al cargar datos: " << e.what() << std::endl;
        archivo.close();
        return false;
    }
}