/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Crear PDFs                                 *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef PDF_GENERATOR_H
#define PDF_GENERATOR_H

#include <string>

// Función para crear el PDF a partir de un archivo .txt
void createPDF(const std::string &inputFile);

#endif // PDF_GENERATOR_H
