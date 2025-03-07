

#ifndef ESTADISTICAS_BANCARIAS_H
#define ESTADISTICAS_BANCARIAS_H

#include <vector>
#include <string>
#include <utility>
#include "Cuenta.h"
#include "Cliente.h"
#include "Transaccion.h"
#include "ArbolCuentas.h"
#include "GestorClientes.h"

class EstadisticasBancarias
{
private:
    ArbolCuentas &arbolCuentas;
    GestorClientes &gestorClientes;

    // Métodos auxiliares para procesamiento de datos
    std::vector<std::pair<std::string, double>> calcularMovimientosPorMes(const std::vector<Transaccion> &transacciones);
    std::vector<std::pair<std::string, int>> calcularCuentasPorTipo();
    std::vector<std::pair<std::string, double>> calcularSaldoPromedioPorTipo();

public:
    // Constructor
    EstadisticasBancarias(ArbolCuentas &arbolCuentas, GestorClientes &gestorClientes);

    // Métodos para diferentes tipos de gráficos y reportes
    void mostrarGraficoBarrasTransaccionesMensuales(const std::string &cedulaCliente = "");
    void mostrarGraficoPastelDistribucionCuentas();
    void mostrarGraficoLineaSaldosPromedios();
    void generarReporteMovimientos(const std::string &numeroCuenta);
    void generarReporteClientesMayorSaldo(int cantidad);

    // Métodos de exportación
    void exportarEstadisticasHTML(const std::string &nombreArchivo);
    void generarPDFReporte(const std::string &nombreArchivo, const std::string &contenido);
    void generarAbrirReporteHTML();

    // Método para exportar directamente a PDF
    void exportarReportePDF(const std::string &nombreArchivo);
    void generarReporteGeneralUsuarios();
    void generarReporteUsuariosActivos();
};

#endif // ESTADISTICAS_BANCARIAS_H