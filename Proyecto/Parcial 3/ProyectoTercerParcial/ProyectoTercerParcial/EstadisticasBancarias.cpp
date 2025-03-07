/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación de estadísticas bancarias                 *
 * Autor:                         Diaz Stiven, Cedenio Andres                               *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "EstadisticasBancarias.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <cmath>

using namespace std;

EstadisticasBancarias::EstadisticasBancarias(ArbolCuentas &arbolCuentas, GestorClientes &gestorClientes)
    : arbolCuentas(arbolCuentas), gestorClientes(gestorClientes) {}

// Métodos auxiliares para procesamiento de datos
vector<pair<string, double>> EstadisticasBancarias::calcularMovimientosPorMes(const vector<Transaccion> &transacciones)
{
    // Agrupar transacciones por mes y calcular movimiento total
    map<string, double> movimientosPorMes;

    for (const auto &transaccion : transacciones)
    {
        Fecha fecha = transaccion.getFecha();
        string mes = to_string(fecha.getMes()) + "/" + to_string(fecha.getAnio());

        if (transaccion.getTipo() == DEPOSITO || transaccion.getTipo() == INTERESES)
        {
            movimientosPorMes[mes] += transaccion.getMonto();
        }
        else
        {
            movimientosPorMes[mes] -= transaccion.getMonto();
        }
    }

    // Convertir map a vector para retorno
    vector<pair<string, double>> resultado;
    for (const auto &par : movimientosPorMes)
    {
        resultado.push_back(par);
    }

    // Ordenar por mes
    sort(resultado.begin(), resultado.end());

    return resultado;
}

vector<pair<string, int>> EstadisticasBancarias::calcularCuentasPorTipo()
{
    // Contar cuentas por tipo
    map<string, int> contadorPorTipo;
    vector<Cuenta> cuentas = arbolCuentas.listarCuentas();

    for (const auto &cuenta : cuentas)
    {
        contadorPorTipo[cuenta.getTipoString()]++;
    }

    // Convertir map a vector para retorno
    vector<pair<string, int>> resultado;
    for (const auto &par : contadorPorTipo)
    {
        resultado.push_back(par);
    }

    return resultado;
}

vector<pair<string, double>> EstadisticasBancarias::calcularSaldoPromedioPorTipo()
{
    // Calcular saldo promedio por tipo de cuenta
    map<string, pair<double, int>> sumaYContador;
    vector<Cuenta> cuentas = arbolCuentas.listarCuentas();

    for (const auto &cuenta : cuentas)
    {
        string tipo = cuenta.getTipoString();
        sumaYContador[tipo].first += cuenta.getSaldo();
        sumaYContador[tipo].second++;
    }

    // Calcular promedios
    vector<pair<string, double>> resultado;
    for (const auto &par : sumaYContador)
    {
        double promedio = 0;
        if (par.second.second > 0)
        {
            promedio = par.second.first / par.second.second;
        }
        resultado.push_back(make_pair(par.first, promedio));
    }

    return resultado;
}

// Métodos para gráficos
void EstadisticasBancarias::mostrarGraficoBarrasTransaccionesMensuales(const string &cedulaCliente)
{
    vector<Cuenta> cuentas;

    if (cedulaCliente.empty())
    {
        cuentas = arbolCuentas.listarCuentas();
    }
    else
    {
        cuentas = arbolCuentas.buscarCuentasPorCliente(cedulaCliente);
    }

    // Recopilar todas las transacciones
    vector<Transaccion> todasLasTransacciones;
    for (const auto &cuenta : cuentas)
    {
        vector<Transaccion> transacciones = cuenta.getHistorialTransacciones();
        todasLasTransacciones.insert(todasLasTransacciones.end(),
                                     transacciones.begin(),
                                     transacciones.end());
    }

    // Calcular movimientos por mes
    vector<pair<string, double>> movimientosPorMes = calcularMovimientosPorMes(todasLasTransacciones);

    // Mostrar título
    cout << "\n===========================================" << endl;
    cout << "  GRÁFICO DE TRANSACCIONES MENSUALES" << endl;
    cout << "===========================================" << endl;

    if (cedulaCliente.empty())
    {
        cout << "Datos de todas las cuentas del banco" << endl;
    }
    else
    {
        Cliente *cliente = gestorClientes.buscarCliente(cedulaCliente);
        if (cliente)
        {
            cout << "Cliente: " << cliente->getNombreCompleto() << " (" << cedulaCliente << ")" << endl;
        }
    }
    cout << "-------------------------------------------" << endl;

    // Determinar el valor máximo para escalar el gráfico
    double maxValor = 0;
    for (const auto &par : movimientosPorMes)
    {
        if (abs(par.second) > maxValor)
        {
            maxValor = abs(par.second);
        }
    }

    // Factor de escala para que el gráfico ocupe aproximadamente 50 caracteres en ancho
    double factorEscala = 50.0 / maxValor;

    // Mostrar el gráfico
    for (const auto &par : movimientosPorMes)
    {
        cout << setw(10) << par.first << " | ";

        int barras = static_cast<int>(abs(par.second) * factorEscala);
        string barra = "";

        // Colorear barras según sean positivas o negativas
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        if (par.second >= 0)
        {
            // Verde para valores positivos
            SetConsoleTextAttribute(hConsole, 10); // Verde
            barra = string(barras, '#');
        }
        else
        {
            // Rojo para valores negativos
            SetConsoleTextAttribute(hConsole, 12); // Rojo
            barra = string(barras, '#');
        }

        cout << barra << " " << fixed << setprecision(2) << par.second << endl;

        // Restaurar color
        SetConsoleTextAttribute(hConsole, 7); // Blanco (color por defecto)
    }

    cout << "===========================================" << endl;
}

void EstadisticasBancarias::mostrarGraficoPastelDistribucionCuentas()
{
    // Calcular cuentas por tipo
    vector<pair<string, int>> cuentasPorTipo = calcularCuentasPorTipo();

    // Calcular total de cuentas
    int totalCuentas = 0;
    for (const auto &par : cuentasPorTipo)
    {
        totalCuentas += par.second;
    }

    // Mostrar título
    cout << "\n===========================================" << endl;
    cout << "  DISTRIBUCIÓN DE TIPOS DE CUENTAS" << endl;
    cout << "===========================================" << endl;

    // Mostrar el gráfico tipo pastel (ASCII art)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorIndex = 9; // Comenzar con color azul

    for (const auto &par : cuentasPorTipo)
    {
        double porcentaje = (totalCuentas > 0) ? (par.second * 100.0 / totalCuentas) : 0;
        int barras = static_cast<int>(porcentaje / 2); // Cada # representa 2%

        // Cambiar color para cada tipo de cuenta
        SetConsoleTextAttribute(hConsole, colorIndex);

        cout << setw(15) << par.first << " | ";
        cout << string(barras, '#') << " " << fixed << setprecision(1) << porcentaje << "% (" << par.second << ")" << endl;

        // Cambiar al siguiente color
        colorIndex = (colorIndex % 6) + 9; // Colores del 9 al 14
    }

    // Restaurar color
    SetConsoleTextAttribute(hConsole, 7);

    cout << "===========================================" << endl;
    cout << "Total de cuentas: " << totalCuentas << endl;
}

void EstadisticasBancarias::mostrarGraficoLineaSaldosPromedios()
{
    // Calcular saldo promedio por tipo
    vector<pair<string, double>> promediosPorTipo = calcularSaldoPromedioPorTipo();

    // Mostrar título
    cout << "\n================================================" << endl;
    cout << "  SALDO PROMEDIO POR TIPO DE CUENTA" << endl;
    cout << "================================================" << endl;

    // Determinar el valor máximo para escalar el gráfico
    double maxValor = 0;
    for (const auto &par : promediosPorTipo)
    {
        if (par.second > maxValor)
        {
            maxValor = par.second;
        }
    }

    // Factor de escala para que el gráfico ocupe aproximadamente 50 caracteres en ancho
    double factorEscala = 50.0 / maxValor;

    // Mostrar el gráfico
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (const auto &par : promediosPorTipo)
    {
        cout << setw(15) << par.first << " | ";

        int barras = static_cast<int>(par.second * factorEscala);

        // Usar color azul para la línea
        SetConsoleTextAttribute(hConsole, 11); // Cian claro
        cout << string(barras, '=') << "O" << " ";

        // Restaurar color para el valor
        SetConsoleTextAttribute(hConsole, 7);
        cout << fixed << setprecision(2) << "$" << par.second << endl;
    }

    cout << "================================================" << endl;
}

void EstadisticasBancarias::generarReporteMovimientos(const string &numeroCuenta)
{
    NodoCuenta *nodoCuenta = arbolCuentas.buscarCuenta(numeroCuenta);
    if (!nodoCuenta)
    {
        cout << "Error: No se encontró la cuenta con número " << numeroCuenta << endl;
        return;
    }

    Cuenta cuenta = nodoCuenta->cuenta;
    vector<Transaccion> transacciones = cuenta.getHistorialTransacciones();

    // Mostrar encabezado
    cout << "\n===============================================================" << endl;
    cout << "  REPORTE DE MOVIMIENTOS - CUENTA " << numeroCuenta << endl;
    cout << "===============================================================" << endl;
    cout << "Titular: " << cuenta.getTitular().getNombreCompleto() << endl;
    cout << "Tipo de cuenta: " << cuenta.getTipoString() << endl;
    cout << "Saldo actual: $" << fixed << setprecision(2) << cuenta.getSaldo() << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << left << setw(12) << "FECHA" << setw(15) << "TIPO" << setw(12) << "MONTO" << "CONCEPTO" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // Mostrar transacciones
    double totalCreditos = 0;
    double totalDebitos = 0;

    for (const auto &trans : transacciones)
    {
        string tipoStr = trans.getTipoString();
        double monto = trans.getMonto();

        // Sumar a totales según el tipo
        if (trans.getTipo() == DEPOSITO || trans.getTipo() == INTERESES)
        {
            totalCreditos += monto;
        }
        else
        {
            totalDebitos += monto;
        }

        cout << left << setw(12) << trans.getFecha().mostrar();
        cout << setw(15) << tipoStr;

        // Formato para montos
        cout << "$" << setw(11) << fixed << setprecision(2) << monto;
        cout << trans.getConcepto() << endl;
    }

    // Mostrar resumen
    cout << "---------------------------------------------------------------" << endl;
    cout << "Total créditos: $" << fixed << setprecision(2) << totalCreditos << endl;
    cout << "Total débitos: $" << fixed << setprecision(2) << totalDebitos << endl;
    cout << "===============================================================" << endl;
}

void EstadisticasBancarias::generarReporteClientesMayorSaldo(int cantidad)
{
    vector<Cuenta> cuentas = arbolCuentas.listarCuentas();

    // Crear mapa para acumular saldos por cliente
    map<string, pair<double, string>> saldosPorCliente; // cédula -> (saldo, nombre)

    for (const auto &cuenta : cuentas)
    {
        string cedula = cuenta.getTitular().getCedula();
        string nombre = cuenta.getTitular().getNombreCompleto();

        saldosPorCliente[cedula].first += cuenta.getSaldo();
        saldosPorCliente[cedula].second = nombre;
    }

    // Convertir a vector para ordenar
    vector<pair<string, pair<double, string>>> clientesSaldo;
    for (const auto &par : saldosPorCliente)
    {
        clientesSaldo.push_back(par);
    }

    // Ordenar por saldo (mayor a menor)
    sort(clientesSaldo.begin(), clientesSaldo.end(),
         [](const auto &a, const auto &b)
         { return a.second.first > b.second.first; });

    // Ajustar cantidad si es mayor al número de clientes
    if (cantidad > clientesSaldo.size())
    {
        cantidad = clientesSaldo.size();
    }

    // Mostrar encabezado
    cout << "\n===============================================================" << endl;
    cout << "  TOP " << cantidad << " CLIENTES CON MAYOR SALDO" << endl;
    cout << "===============================================================" << endl;
    cout << left << setw(5) << "POS" << setw(15) << "CÉDULA" << setw(25) << "NOMBRE" << "SALDO TOTAL" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // Mostrar clientes
    for (int i = 0; i < cantidad; i++)
    {
        const auto &cliente = clientesSaldo[i];
        cout << left << setw(5) << (i + 1)
             << setw(15) << cliente.first
             << setw(25) << cliente.second.second
             << "$" << fixed << setprecision(2) << cliente.second.first << endl;
    }

    cout << "===============================================================" << endl;
}

void EstadisticasBancarias::exportarEstadisticasHTML(const string &nombreArchivo)
{
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "Error al crear el archivo HTML: " << nombreArchivo << endl;
        return;
    }

    // Obtener datos para los gráficos
    vector<pair<string, int>> cuentasPorTipo = calcularCuentasPorTipo();
    vector<pair<string, double>> saldoPromedioPorTipo = calcularSaldoPromedioPorTipo();

    // Escribir encabezado HTML
    archivo << "<!DOCTYPE html>\n"
            << "<html lang=\"es\">\n"
            << "<head>\n"
            << "    <meta charset=\"UTF-8\">\n"
            << "    <title>Estadísticas Bancarias</title>\n"
            << "    <script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>\n"
            << "    <style>\n"
            << "        body { font-family: Arial, sans-serif; margin: 20px; }\n"
            << "        .chart-container { width: 80%; margin: 20px auto; }\n"
            << "        h1, h2 { color: #003366; }\n"
            << "        .footer { margin-top: 30px; font-size: 12px; color: #666; }\n"
            << "    </style>\n"
            << "</head>\n"
            << "<body>\n"
            << "    <h1>Estadísticas del Sistema Bancario</h1>\n"
            << "    <p>Reporte generado el " << Fecha::obtenerFechaActual().mostrar() << "</p>\n";

    // Gráfico de tipos de cuenta (pastel)
    archivo << "    <div class=\"chart-container\">\n"
            << "        <h2>Distribución de Tipos de Cuenta</h2>\n"
            << "        <canvas id=\"cuentasChart\"></canvas>\n"
            << "    </div>\n";

    // Gráfico de saldos promedio (barras)
    archivo << "    <div class=\"chart-container\">\n"
            << "        <h2>Saldo Promedio por Tipo de Cuenta</h2>\n"
            << "        <canvas id=\"saldosChart\"></canvas>\n"
            << "    </div>\n";

    // Script para generar los gráficos
    archivo << "    <script>\n"
            << "        // Datos para el gráfico de cuentas\n"
            << "        const ctxCuentas = document.getElementById('cuentasChart').getContext('2d');\n"
            << "        new Chart(ctxCuentas, {\n"
            << "            type: 'pie',\n"
            << "            data: {\n"
            << "                labels: [";

    // Agregar etiquetas para el gráfico de pastel
    bool primero = true;
    for (const auto &par : cuentasPorTipo)
    {
        if (!primero)
            archivo << ", ";
        archivo << "'" << par.first << "'";
        primero = false;
    }

    archivo << "],\n"
            << "                datasets: [{\n"
            << "                    data: [";

    // Agregar datos para el gráfico de pastel
    primero = true;
    for (const auto &par : cuentasPorTipo)
    {
        if (!primero)
            archivo << ", ";
        archivo << par.second;
        primero = false;
    }

    archivo << "],\n"
            << "                    backgroundColor: ['#FF6384', '#36A2EB', '#FFCE56', '#4BC0C0', '#9966FF']\n"
            << "                }]\n"
            << "            },\n"
            << "            options: {\n"
            << "                responsive: true,\n"
            << "                plugins: {\n"
            << "                    legend: { position: 'top' },\n"
            << "                    title: { display: false }\n"
            << "                }\n"
            << "            }\n"
            << "        });\n\n";

    // Configuración para el gráfico de barras
    archivo << "        // Datos para el gráfico de saldos\n"
            << "        const ctxSaldos = document.getElementById('saldosChart').getContext('2d');\n"
            << "        new Chart(ctxSaldos, {\n"
            << "            type: 'bar',\n"
            << "            data: {\n"
            << "                labels: [";

    // Agregar etiquetas para el gráfico de barras
    primero = true;
    for (const auto &par : saldoPromedioPorTipo)
    {
        if (!primero)
            archivo << ", ";
        archivo << "'" << par.first << "'";
        primero = false;
    }

    archivo << "],\n"
            << "                datasets: [{\n"
            << "                    label: 'Saldo Promedio ($)',\n"
            << "                    data: [";

    // Agregar datos para el gráfico de barras
    primero = true;
    for (const auto &par : saldoPromedioPorTipo)
    {
        if (!primero)
            archivo << ", ";
        archivo << fixed << setprecision(2) << par.second;
        primero = false;
    }

    archivo << "],\n"
            << "                    backgroundColor: '#36A2EB',\n"
            << "                    borderColor: '#2980B9',\n"
            << "                    borderWidth: 1\n"
            << "                }]\n"
            << "            },\n"
            << "            options: {\n"
            << "                responsive: true,\n"
            << "                scales: {\n"
            << "                    y: { beginAtZero: true }\n"
            << "                }\n"
            << "            }\n"
            << "        });\n"
            << "    </script>\n";

    // Pie de página
    archivo << "    <div class=\"footer\">\n"
            << "        <p>Sistema Bancario ESPE - Desarrollado por Diaz Stiven y Cedenio Andres</p>\n"
            << "    </div>\n"
            << "</body>\n"
            << "</html>";

    archivo.close();
    cout << "Estadísticas exportadas correctamente a " << nombreArchivo << endl;
    string comando = "start " + nombreArchivo;
    system(comando.c_str());
}

void EstadisticasBancarias::generarPDFReporte(const string &nombreArchivo, const string &contenido)
{
    // Esta función requeriría una biblioteca de generación de PDF como pdflib, libharu o similares
    // Por simplicidad, crearemos un archivo de texto con formato que simule un PD

    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "Error al crear el archivo de reporte: " << nombreArchivo << endl;
        return;
    }

    // Encabezado del reporte
    archivo << "========================================================================================\n";
    archivo << "                            SISTEMA BANCARIO ESPE - REPORTE                             \n";
    archivo << "========================================================================================\n\n";

    archivo << "Fecha de generación: " << Fecha::obtenerFechaActual().mostrar() << "\n\n";

    // Contenido del reporte
    archivo << contenido << "\n\n";

    // Pie de página
    archivo << "========================================================================================\n";
    archivo << "                    Desarrollado por Diaz Stiven y Cedenio Andres                           \n";
    archivo << "========================================================================================\n";

    archivo.close();
    cout << "Reporte generado correctamente en " << nombreArchivo << endl;
}
void EstadisticasBancarias::generarAbrirReporteHTML()
{
    string nombreArchivo = "estadisticas_bancarias.html";
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "Error al crear el archivo HTML: " << nombreArchivo << endl;
        return;
    }

    // Obtener datos para los gráficos
    vector<pair<string, int>> cuentasPorTipo = calcularCuentasPorTipo();
    vector<pair<string, double>> saldoPromedioPorTipo = calcularSaldoPromedioPorTipo();

    // Recopilar datos para el gráfico de transacciones mensuales (todos los clientes)
    vector<Cuenta> cuentas = arbolCuentas.listarCuentas();
    vector<Transaccion> todasLasTransacciones;
    for (const auto &cuenta : cuentas)
    {
        vector<Transaccion> transacciones = cuenta.getHistorialTransacciones();
        todasLasTransacciones.insert(todasLasTransacciones.end(),
                                     transacciones.begin(),
                                     transacciones.end());
    }

    vector<pair<string, double>> movimientosPorMes = calcularMovimientosPorMes(todasLasTransacciones);

    // Escribir encabezado HTML con estilo mejorado
    archivo << "<!DOCTYPE html>\n"
            << "<html lang=\"es\">\n"
            << "<head>\n"
            << "    <meta charset=\"UTF-8\">\n"
            << "    <title>Estadísticas Bancarias</title>\n"
            << "    <script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>\n"
            << "    <script src=\"https://cdnjs.cloudflare.com/ajax/libs/jspdf/2.5.1/jspdf.umd.min.js\"></script>\n"
            << "    <script src=\"https://cdnjs.cloudflare.com/ajax/libs/html2canvas/1.4.1/html2canvas.min.js\"></script>\n"
            << "    <style>\n"
            << "        body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 0; padding: 0; background-color: #f5f5f5; color: #333; }\n"
            << "        .container { width: 90%; max-width: 1200px; margin: 20px auto; background-color: white; padding: 20px; box-shadow: 0 0 10px rgba(0,0,0,0.1); border-radius: 8px; }\n"
            << "        .header { background-color: #003366; color: white; padding: 15px; margin-bottom: 20px; border-radius: 4px; display: flex; justify-content: space-between; align-items: center; }\n"
            << "        .header h1 { margin: 0; font-size: 24px; }\n"
            << "        .header-info { font-size: 14px; }\n"
            << "        .chart-container { margin: 30px 0; padding: 20px; border: 1px solid #eee; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.05); }\n"
            << "        h2 { color: #003366; border-bottom: 2px solid #003366; padding-bottom: 10px; margin-top: 30px; }\n"
            << "        .btn { display: inline-block; padding: 10px 15px; background-color: #003366; color: white; text-decoration: none; border-radius: 4px; cursor: pointer; }\n"
            << "        .btn:hover { background-color: #004080; }\n"
            << "        .footer { margin-top: 50px; padding-top: 20px; border-top: 1px solid #ddd; font-size: 12px; color: #666; text-align: center; }\n"
            << "    </style>\n"
            << "</head>\n"
            << "<body>\n"
            << "    <div class=\"container\" id=\"capture\">\n"
            << "        <div class=\"header\">\n"
            << "            <h1>Estadísticas del Sistema Bancario</h1>\n"
            << "            <div class=\"header-info\">Reporte generado el " << Fecha::obtenerFechaActual().mostrar() << "</div>\n"
            << "        </div>\n"
            << "        <p>Este reporte muestra un análisis detallado de las cuentas y transacciones del sistema bancario.</p>\n";

    // Gráfico de transacciones mensuales (agregado según el requerimiento)
    archivo << "        <h2>Transacciones Mensuales</h2>\n"
            << "        <div class=\"chart-container\">\n"
            << "            <canvas id=\"transaccionesChart\"></canvas>\n"
            << "        </div>\n";

    // Gráfico de tipos de cuenta (pastel)
    archivo << "        <h2>Distribución de Tipos de Cuenta</h2>\n"
            << "        <div class=\"chart-container\">\n"
            << "            <canvas id=\"cuentasChart\"></canvas>\n"
            << "        </div>\n";

    // Gráfico de saldos promedio (barras)
    archivo << "        <h2>Saldo Promedio por Tipo de Cuenta</h2>\n"
            << "        <div class=\"chart-container\">\n"
            << "            <canvas id=\"saldosChart\"></canvas>\n"
            << "        </div>\n";

    // Botón para exportar a PDF
    archivo << "        <div style=\"text-align: center; margin-top: 30px;\">\n"
            << "            <button class=\"btn\" onclick=\"generarPDF()\">Exportar a PDF</button>\n"
            << "        </div>\n"
            << "        <div class=\"footer\">\n"
            << "            <p>Sistema Bancario ESPE - Desarrollado por Diaz Stiven y Cedenio Andres </p>\n"
            << "        </div>\n"
            << "    </div>\n";

    // Script para generar los gráficos y exportar a PDF
    archivo << "    <script>\n"
            << "        // Función para exportar a PDF\n"
            << "        function generarPDF() {\n"
            << "            const { jsPDF } = window.jspdf;\n"
            << "            const doc = new jsPDF('p', 'mm', 'a4');\n"
            << "            const content = document.getElementById('capture');\n"
            << "            \n"
            << "            html2canvas(content, {\n"
            << "                scale: 2,  // Aumentar resolución\n"
            << "                useCORS: true,  // Manejar imágenes cross-origin\n"
            << "                logging: false  // Desactivar logging\n"
            << "            }).then(canvas => {\n"
            << "                const imgData = canvas.toDataURL('image/png');\n"
            << "                const imgProps = doc.getImageProperties(imgData);\n"
            << "                const pdfWidth = doc.internal.pageSize.getWidth();\n"
            << "                const pdfHeight = (imgProps.height * pdfWidth) / imgProps.width;\n"
            << "                \n"
            << "                // Añadir primera página\n"
            << "                doc.addImage(imgData, 'PNG', 0, 0, pdfWidth, pdfHeight);\n"
            << "                \n"
            << "                // Si la imagen es más alta que una página, dividirla\n"
            << "                if (pdfHeight > doc.internal.pageSize.getHeight()) {\n"
            << "                    const totalPages = Math.ceil(pdfHeight / doc.internal.pageSize.getHeight());\n"
            << "                    \n"
            << "                    for (let page = 1; page < totalPages; page++) {\n"
            << "                        doc.addPage();\n"
            << "                        doc.addImage(\n"
            << "                            imgData, \n"
            << "                            'PNG', \n"
            << "                            0, \n"
            << "                            -page * doc.internal.pageSize.getHeight(), \n"
            << "                            pdfWidth, \n"
            << "                            pdfHeight\n"
            << "                        );\n"
            << "                    }\n"
            << "                }\n"
            << "                \n"
            << "                doc.save('estadisticas_bancarias.pdf');\n"
            << "            }).catch(error => {\n"
            << "                console.error('Error generando PDF:', error);\n"
            << "            });\n"
            << "        }\n\n";

    // Datos para el gráfico de transacciones mensuales
    archivo << "        // Datos para el gráfico de transacciones mensuales\n"
            << "        const ctxTransacciones = document.getElementById('transaccionesChart').getContext('2d');\n"
            << "        new Chart(ctxTransacciones, {\n"
            << "            type: 'line',\n"
            << "            data: {\n"
            << "                labels: [";

    bool primero = true;
    for (const auto &par : movimientosPorMes)
    {
        if (!primero)
            archivo << ", ";
        archivo << "'" << par.first << "'";
        primero = false;
    }

    archivo << "],\n"
            << "                datasets: [{\n"
            << "                    label: 'Movimientos Mensuales ($)',\n"
            << "                    data: [";

    primero = true;
    for (const auto &par : movimientosPorMes)
    {
        if (!primero)
            archivo << ", ";
        archivo << fixed << setprecision(2) << par.second;
        primero = false;
    }

    archivo << "],\n"
            << "                    borderColor: '#4bc0c0',\n"
            << "                    backgroundColor: 'rgba(75, 192, 192, 0.2)',\n"
            << "                    tension: 0.1,\n"
            << "                    fill: true,\n"
            << "                    pointBackgroundColor: '#4bc0c0',\n"
            << "                    pointBorderColor: '#fff',\n"
            << "                    pointRadius: 5\n"
            << "                }]\n"
            << "            },\n"
            << "            options: {\n"
            << "                responsive: true,\n"
            << "                plugins: {\n"
            << "                    legend: { position: 'top' },\n"
            << "                    title: { display: false }\n"
            << "                },\n"
            << "                scales: {\n"
            << "                    y: { beginAtZero: true }\n"
            << "                }\n"
            << "            }\n"
            << "        });\n\n";

    // Datos para el gráfico de tipos de cuenta (pastel)
    archivo << "        // Datos para el gráfico de cuentas\n"
            << "        const ctxCuentas = document.getElementById('cuentasChart').getContext('2d');\n"
            << "        new Chart(ctxCuentas, {\n"
            << "            type: 'pie',\n"
            << "            data: {\n"
            << "                labels: [";

    primero = true;
    for (const auto &par : cuentasPorTipo)
    {
        if (!primero)
            archivo << ", ";
        archivo << "'" << par.first << "'";
        primero = false;
    }

    archivo << "],\n"
            << "                datasets: [{\n"
            << "                    data: [";

    primero = true;
    for (const auto &par : cuentasPorTipo)
    {
        if (!primero)
            archivo << ", ";
        archivo << par.second;
        primero = false;
    }

    archivo << "],\n"
            << "                    backgroundColor: ['#FF6384', '#36A2EB', '#FFCE56', '#4BC0C0', '#9966FF'],\n"
            << "                    borderWidth: 1\n"
            << "                }]\n"
            << "            },\n"
            << "            options: {\n"
            << "                responsive: true,\n"
            << "                plugins: {\n"
            << "                    legend: { position: 'top' },\n"
            << "                    title: { display: false }\n"
            << "                }\n"
            << "            }\n"
            << "        });\n\n";

    // Configuración para el gráfico de barras (saldos promedio)
    archivo << "        // Datos para el gráfico de saldos\n"
            << "        const ctxSaldos = document.getElementById('saldosChart').getContext('2d');\n"
            << "        new Chart(ctxSaldos, {\n"
            << "            type: 'bar',\n"
            << "            data: {\n"
            << "                labels: [";

    primero = true;
    for (const auto &par : saldoPromedioPorTipo)
    {
        if (!primero)
            archivo << ", ";
        archivo << "'" << par.first << "'";
        primero = false;
    }

    archivo << "],\n"
            << "                datasets: [{\n"
            << "                    label: 'Saldo Promedio ($)',\n"
            << "                    data: [";

    primero = true;
    for (const auto &par : saldoPromedioPorTipo)
    {
        if (!primero)
            archivo << ", ";
        archivo << fixed << setprecision(2) << par.second;
        primero = false;
    }

    archivo << "],\n"
            << "                    backgroundColor: '#36A2EB',\n"
            << "                    borderColor: '#2980B9',\n"
            << "                    borderWidth: 1\n"
            << "                }]\n"
            << "            },\n"
            << "            options: {\n"
            << "                responsive: true,\n"
            << "                scales: {\n"
            << "                    y: { beginAtZero: true }\n"
            << "                }\n"
            << "            }\n"
            << "        });\n"
            << "    </script>\n"
            << "</body>\n"
            << "</html>";

    archivo.close();
    cout << "Estadísticas generadas correctamente en " << nombreArchivo << endl;

    // Abrir automáticamente el archivo HTML en el navegador predeterminado
    string comando = "start " + nombreArchivo;
    system(comando.c_str());
}

// Método para exportar a PDF directamente (puede añadirse si se prefiere separar esta funcionalidad)
void EstadisticasBancarias::exportarReportePDF(const string &nombreArchivo)
{
    // Primero generamos el HTML
    generarAbrirReporteHTML();

    cout << "Para exportar a PDF, utilice el botón 'Exportar a PDF' en el informe web." << endl;
}
void EstadisticasBancarias::generarReporteGeneralUsuarios()
{
    vector<Cliente> clientes = gestorClientes.listarClientes();

    system("cls");
    cout << "================================================================================" << endl;
    cout << "                      REPORTE GENERAL DE USUARIOS Y CUENTAS                     " << endl;
    cout << "================================================================================" << endl;
    cout << "Fecha: " << Fecha::obtenerFechaActual().mostrar() << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    if (clientes.empty())
    {
        cout << "No hay clientes registrados en el sistema." << endl;
    }
    else
    {
        cout << "TOTAL DE CLIENTES: " << clientes.size() << endl
             << endl;

        for (const auto &cliente : clientes)
        {
            // Información del cliente
            cout << "CLIENTE: " << cliente.getNombreCompleto() << endl;
            cout << "Cédula: " << cliente.getCedula() << endl;
            cout << "Teléfono: " << cliente.getTelefono() << endl;
            cout << "Email: " << cliente.getEmail() << endl;

            // Buscar las cuentas del cliente
            vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(cliente.getCedula());

            if (cuentasCliente.empty())
            {
                cout << "El cliente no tiene cuentas registradas." << endl;
            }
            else
            {
                cout << "\nCUENTAS ASOCIADAS: " << endl;
                cout << left << setw(15) << "NÚMERO" << setw(15) << "TIPO"
                     << setw(15) << "ESTADO" << "SALDO" << endl;
                cout << "--------------------------------------------------------------------------------" << endl;

                for (const auto &cuenta : cuentasCliente)
                {
                    cout << left << setw(15) << cuenta.getNumeroCuenta()
                         << setw(15) << cuenta.getTipoString()
                         << setw(15) << cuenta.getEstadoPersonalizado()
                         << "$" << fixed << setprecision(2) << cuenta.getSaldo() << endl;
                }

                // Calcular saldo total de todas las cuentas del cliente
                double saldoTotal = 0;
                for (const auto &cuenta : cuentasCliente)
                {
                    saldoTotal += cuenta.getSaldo();
                }

                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "Saldo total del cliente: $" << fixed << setprecision(2) << saldoTotal << endl;
            }

            cout << "================================================================================" << endl;
        }
    }

    cout << "\nPresione cualquier tecla para volver..." << endl;
    _getch();
}

// Reporte de usuarios con cuentas activas (lista depurada)
void EstadisticasBancarias::generarReporteUsuariosActivos()
{
    vector<Cliente> clientes = gestorClientes.listarClientes();

    system("cls");
    cout << "================================================================================" << endl;
    cout << "                   REPORTE DE USUARIOS CON CUENTAS ACTIVAS                      " << endl;
    cout << "================================================================================" << endl;
    cout << "Fecha: " << Fecha::obtenerFechaActual().mostrar() << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    if (clientes.empty())
    {
        cout << "No hay clientes registrados en el sistema." << endl;
    }
    else
    {
        int clientesConCuentasActivas = 0;

        for (const auto &cliente : clientes)
        {
            // Buscar las cuentas del cliente
            vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(cliente.getCedula());

            // Filtrar solo cuentas activas
            vector<Cuenta> cuentasActivas;
            for (const auto &cuenta : cuentasCliente)
            {
                if (cuenta.isActiva())
                {
                    cuentasActivas.push_back(cuenta);
                }
            }

            // Solo mostrar clientes con cuentas activas
            if (!cuentasActivas.empty())
            {
                clientesConCuentasActivas++;

                // Información del cliente
                cout << "CLIENTE: " << cliente.getNombreCompleto() << endl;
                cout << "Cédula: " << cliente.getCedula() << endl;
                cout << "Teléfono: " << cliente.getTelefono() << endl;
                cout << "Email: " << cliente.getEmail() << endl;

                cout << "\nCUENTAS ACTIVAS: " << endl;
                cout << left << setw(15) << "NÚMERO" << setw(15) << "TIPO" << "SALDO" << endl;
                cout << "--------------------------------------------------------------------------------" << endl;

                double saldoTotalActivo = 0;
                for (const auto &cuenta : cuentasActivas)
                {
                    cout << left << setw(15) << cuenta.getNumeroCuenta()
                         << setw(15) << cuenta.getTipoString()
                         << "$" << fixed << setprecision(2) << cuenta.getSaldo() << endl;

                    saldoTotalActivo += cuenta.getSaldo();
                }

                cout << "--------------------------------------------------------------------------------" << endl;
                cout << "Saldo total activo: $" << fixed << setprecision(2) << saldoTotalActivo << endl;
                cout << "================================================================================" << endl;
            }
        }

        if (clientesConCuentasActivas == 0)
        {
            cout << "No hay clientes con cuentas activas en el sistema." << endl;
        }
        else
        {
            cout << "\nTOTAL DE CLIENTES CON CUENTAS ACTIVAS: " << clientesConCuentasActivas << endl;
        }
    }

    cout << "\nPresione cualquier tecla para volver..." << endl;
    _getch();
}