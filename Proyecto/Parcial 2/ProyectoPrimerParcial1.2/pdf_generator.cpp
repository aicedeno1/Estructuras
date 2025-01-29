/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "pdf_generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "hpdf.h"

using namespace std;

// Función para dividir una línea por el delimitador ';'
vector<string> split(const string &line, char delimiter)
{
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
void createPDF(const std::string &inputFile)
{
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf)
    {
        cerr << "Error al crear el PDF" << endl;
        return;
    }
    else
    {
        cout << "PDF generado correctamente!" << endl;
    }

    // Crear una página
    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    // Establecer la fuente
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(page, font, 9);

    // Leer el archivo .txt
    ifstream file(inputFile);
    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo" << endl;
        HPDF_Free(pdf);
        return;
    }

    // Establecer posición inicial y espaciado
    float yPosition = 750;
    float xPosition = 20;
    float columnWidth = 90;

    // Ajustar posición específica para ISNI
    float isniOffset = columnWidth * 1.8; // Reducido de 2 a 1.8

    // Títulos de las columnas
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, xPosition, yPosition, "Titulo");
    HPDF_Page_TextOut(page, xPosition + columnWidth, yPosition, "Autor");
    HPDF_Page_TextOut(page, xPosition + isniOffset, yPosition, "ISNI");
    HPDF_Page_TextOut(page, xPosition + columnWidth * 3, yPosition, "Fecha Registro");
    HPDF_Page_TextOut(page, xPosition + columnWidth * 4, yPosition, "ISBN");
    HPDF_Page_TextOut(page, xPosition + columnWidth * 5, yPosition, "Fecha Venc.");
    HPDF_Page_EndText(page);

    // Línea separadora
    yPosition -= 20;
    HPDF_Page_MoveTo(page, xPosition, yPosition);
    HPDF_Page_LineTo(page, xPosition + (columnWidth * 6), yPosition);
    HPDF_Page_Stroke(page);

    // Leer y escribir datos
    while (!file.eof())
    {
        string line;
        getline(file, line);
        if (line.empty())
            continue;

        vector<string> fields = split(line, ';');

        // Escribir campos en el PDF
        yPosition -= 20;
        HPDF_Page_BeginText(page);

        // Título
        HPDF_Page_TextOut(page, xPosition, yPosition,
                          fields.size() > 0 ? fields[0].c_str() : "");

        // Autor
        HPDF_Page_TextOut(page, xPosition + columnWidth, yPosition,
                          fields.size() > 1 ? fields[1].c_str() : "");

        // ISNI (con nueva posición)
        HPDF_Page_TextOut(page, xPosition + isniOffset, yPosition,
                          fields.size() > 2 ? fields[2].c_str() : "");

        // Fecha de Registro
        HPDF_Page_TextOut(page, xPosition + columnWidth * 3, yPosition,
                          fields.size() > 3 ? fields[3].c_str() : "");

        // ISBN
        HPDF_Page_TextOut(page, xPosition + columnWidth * 4, yPosition,
                          fields.size() > 4 ? fields[4].c_str() : "");

        // Fecha de Vencimiento
        HPDF_Page_TextOut(page, xPosition + columnWidth * 5, yPosition,
                          fields.size() > 5 ? fields[5].c_str() : "");

        HPDF_Page_EndText(page);

        // Nueva página si es necesario
        if (yPosition < 100)
        {
            page = HPDF_AddPage(pdf);
            HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
            HPDF_Page_SetFontAndSize(page, font, 9);
            yPosition = 750;

            // Repetir los títulos en la nueva página con la nueva posición de ISNI
            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, xPosition, yPosition, "Titulo");
            HPDF_Page_TextOut(page, xPosition + columnWidth, yPosition, "Autor");
            HPDF_Page_TextOut(page, xPosition + isniOffset, yPosition, "ISNI");
            HPDF_Page_TextOut(page, xPosition + columnWidth * 3, yPosition, "Fecha Registro");
            HPDF_Page_TextOut(page, xPosition + columnWidth * 4, yPosition, "ISBN");
            HPDF_Page_TextOut(page, xPosition + columnWidth * 5, yPosition, "Fecha Venc.");
            HPDF_Page_EndText(page);

            // Línea separadora en la nueva página
            yPosition -= 20;
            HPDF_Page_MoveTo(page, xPosition, yPosition);
            HPDF_Page_LineTo(page, xPosition + (columnWidth * 6), yPosition);
            HPDF_Page_Stroke(page);
        }
    }

    file.close();
    HPDF_SaveToFile(pdf, "output.pdf");
    HPDF_Free(pdf);
}