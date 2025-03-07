#ifndef QR_GENERATOR_H
#define QR_GENERATOR_H

#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Clase simplificada para generar códigos QR básicos para transferencias bancarias
class QRGenerator
{
private:
    // Estructura para los datos de transferencia
    struct TransferenciaQR
    {
        std::string numeroCuenta;
        std::string nombreTitular;
        double monto;
        std::string concepto;
    };

    // Matriz para el código QR (para simplificar, usamos una matriz de 0s y 1s)
    std::vector<std::vector<bool>> qrMatrix;

    // Codificar un texto en formato ASCII
    std::vector<uint8_t> encodeText(const std::string &text)
    {
        std::vector<uint8_t> encoded;
        for (char c : text)
        {
            encoded.push_back(static_cast<uint8_t>(c));
        }
        return encoded;
    }

    // Método para generar una matriz simple para visualizar
    void generateMatrix(const std::string &data, int size = 21)
    {
        // Inicializar matriz con bordes (para simplificar)
        qrMatrix.resize(size, std::vector<bool>(size, false));

        // Agregar patrones de búsqueda (simplificado)
        // Esquina superior izquierda
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if ((i == 0 || i == 6 || j == 0 || j == 6) ||
                    (i >= 2 && i <= 4 && j >= 2 && j <= 4))
                {
                    qrMatrix[i][j] = true;
                }
            }
        }

        // Esquina superior derecha
        for (int i = 0; i < 7; i++)
        {
            for (int j = size - 7; j < size; j++)
            {
                if ((i == 0 || i == 6 || j == size - 7 || j == size - 1) ||
                    (i >= 2 && i <= 4 && j >= size - 5 && j <= size - 3))
                {
                    qrMatrix[i][j] = true;
                }
            }
        }

        // Esquina inferior izquierda
        for (int i = size - 7; i < size; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if ((i == size - 7 || i == size - 1 || j == 0 || j == 6) ||
                    (i >= size - 5 && i <= size - 3 && j >= 2 && j <= 4))
                {
                    qrMatrix[i][j] = true;
                }
            }
        }

        // Codificar datos (simplificado)
        int dataIndex = 0;
        for (char c : data)
        {
            // Convertir el carácter a binario y distribuirlo en la matriz
            for (int bit = 7; bit >= 0; bit--)
            {
                int row = 8 + (dataIndex / (size - 16));
                int col = 8 + (dataIndex % (size - 16));

                // Evitar colisionar con los patrones de búsqueda
                if (row < 8 && col < 8)
                    continue;
                if (row < 8 && col >= size - 8)
                    continue;
                if (row >= size - 8 && col < 8)
                    continue;

                qrMatrix[row][col] = (c & (1 << bit));
                dataIndex++;

                if (dataIndex >= (size - 16) * (size - 16))
                    return; // La matriz está llena
            }
        }
    }

public:
    QRGenerator() {}

    // Generar un código QR para transferencia
    bool generarQRTransferencia(const std::string &numeroCuenta, const std::string &nombreTitular,
                                double monto, const std::string &concepto, const std::string &rutaArchivo)
    {
        try
        {
            // Crear los datos para el QR
            std::ostringstream dataStream;
            dataStream << "BANCO-ESPE|"
                       << numeroCuenta << "|"
                       << nombreTitular << "|"
                       << std::fixed << std::setprecision(2) << monto << "|"
                       << concepto;

            std::string qrData = dataStream.str();

            // Generar la matriz del QR
            generateMatrix(qrData, 33); // Tamaño mayor para más datos

            // Guardar en un archivo HTML para visualizar
            std::ofstream htmlFile(rutaArchivo);
            if (htmlFile.is_open())
            {
                htmlFile << "<!DOCTYPE html>\n"
                         << "<html>\n"
                         << "<head>\n"
                         << "    <title>QR Code para Transferencia</title>\n"
                         << "    <style>\n"
                         << "        body { font-family: Arial, sans-serif; text-align: center; }\n"
                         << "        .qr-container { margin: 20px auto; width: 330px; }\n"
                         << "        .qr-code { border-collapse: collapse; margin: 0 auto; }\n"
                         << "        .qr-cell { width: 10px; height: 10px; }\n"
                         << "        .qr-black { background-color: black; }\n"
                         << "        .qr-white { background-color: white; }\n"
                         << "        .info { margin-top: 20px; text-align: left; padding: 10px; border: 1px solid #ddd; }\n"
                         << "    </style>\n"
                         << "</head>\n"
                         << "<body>\n"
                         << "    <h1>QR para Transferencia Bancaria</h1>\n"
                         << "    <div class='qr-container'>\n"
                         << "        <table class='qr-code'>\n";

                // Generar el código QR como una tabla HTML
                for (const auto &row : qrMatrix)
                {
                    htmlFile << "            <tr>\n";
                    for (bool cell : row)
                    {
                        htmlFile << "                <td class='" << (cell ? "qr-black" : "qr-white") << " qr-cell'></td>\n";
                    }
                    htmlFile << "            </tr>\n";
                }

                htmlFile << "        </table>\n"
                         << "    </div>\n"
                         << "    <div class='info'>\n"
                         << "        <h2>Información de Transferencia</h2>\n"
                         << "        <p><strong>Cuenta Destino:</strong> " << numeroCuenta << "</p>\n"
                         << "        <p><strong>Titular:</strong> " << nombreTitular << "</p>\n"
                         << "        <p><strong>Monto Sugerido:</strong> $" << std::fixed << std::setprecision(2) << monto << "</p>\n"
                         << "        <p><strong>Concepto:</strong> " << concepto << "</p>\n"
                         << "        <p><em>Escanee este código con la app bancaria para realizar la transferencia</em></p>\n"
                         << "    </div>\n"
                         << "</body>\n"
                         << "</html>";

                htmlFile.close();

                std::cout << "Código QR para transferencia generado en: " << rutaArchivo << std::endl;
                return true;
            }
            return false;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error al generar QR: " << e.what() << std::endl;
            return false;
        }
    }

    // Para uso futuro: guardar como imagen PNG
    bool guardarComoImagen(const std::string &rutaArchivo)
    {
        // Esta función requeriría una biblioteca gráfica como libpng
        // Por ahora devolvemos falso
        std::cerr << "La funcionalidad de guardar como imagen requiere bibliotecas adicionales." << std::endl;
        return false;
    }
};

#endif // QR_GENERATOR_H