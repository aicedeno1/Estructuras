/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Crear PDFs                                               *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
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
vector<string> split(const string &line, char delimiter) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Función para crear el PDF
void createPDF(const std::string& inputFile) {
    // Crea el objeto de documento PDF
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf) {
        cerr << "Error al crear el PDF" << endl;
        return;
    } else {
        cout << "PDF generado correctamente!" << endl;
    }

    // Crear una página
    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    // Establecer la fuente
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(page, font, 10);

    // Leer el archivo .txt
    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        HPDF_Free(pdf);
        return;
    }

    // Establecer posición inicial en la página
    float yPosition = 750;
    float xPosition = 50;

    // Títulos de las columnas
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, xPosition, yPosition, "Titulo");
    HPDF_Page_TextOut(page, xPosition + 150, yPosition, "Autor");
    HPDF_Page_TextOut(page, xPosition + 300, yPosition, "ISBN");
    HPDF_Page_TextOut(page, xPosition + 450, yPosition, "Anio");
    HPDF_Page_EndText(page);

    // Dibuja la línea que separa los títulos de los datos
    yPosition -= 20;
    HPDF_Page_MoveTo(page, xPosition, yPosition);
    HPDF_Page_LineTo(page, xPosition + 500, yPosition);
    HPDF_Page_Stroke(page);

    // Leer las líneas del archivo .txt y escribir en el PDF
    while (!file.eof()) {
        string line;
        getline(file, line);
        if (line.empty()) continue;

        vector<string> fields = split(line, ';');

        // Escribir cada campo en el PDF
        yPosition -= 20;
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, xPosition, yPosition, fields.size() > 0 ? fields[0].c_str() : "");
        HPDF_Page_TextOut(page, xPosition + 150, yPosition, fields.size() > 1 ? fields[1].c_str() : "");
        HPDF_Page_TextOut(page, xPosition + 300, yPosition, fields.size() > 2 ? fields[2].c_str() : "");
        HPDF_Page_TextOut(page, xPosition + 450, yPosition, fields.size() > 3 ? fields[3].c_str() : "");
        HPDF_Page_EndText(page);

        // Si la página se llena, añadir una nueva página
        if (yPosition < 100) {
            page = HPDF_AddPage(pdf);
            HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
            HPDF_Page_SetFontAndSize(page, font, 10);
            yPosition = 750;
        }
    }

    file.close();

    // Guardar el PDF
    HPDF_SaveToFile(pdf, "output.pdf");

    // Liberar el objeto PDF
    HPDF_Free(pdf);
}
