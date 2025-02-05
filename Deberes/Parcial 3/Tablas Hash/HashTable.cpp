#include "HashTable.h"
#include <iostream>
#include <windows.h>
#include <cmath>
#include <algorithm>

using namespace std;

float HashTable::prevx = 0;
float HashTable::prevy = 0;

HashTable::HashTable(bool letterMode) : isLetterMode(letterMode)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i] = nullptr;
    }
    initializeGraphicsDimensions();
}

void HashTable::initializeGraphicsDimensions()
{
    WINDOW_WIDTH = GetSystemMetrics(SM_CXSCREEN);
    WINDOW_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
    CELL_WIDTH = (WINDOW_WIDTH / (TABLE_SIZE + 2));
    CELL_HEIGHT = CELL_WIDTH / 2;
    VERTICAL_SPACING = CELL_HEIGHT * 2;
    ARROW_HEIGHT = VERTICAL_SPACING / 2;
    START_X = (WINDOW_WIDTH - (TABLE_SIZE * CELL_WIDTH)) / 2;
    START_Y = (WINDOW_HEIGHT * 3) / 4;
    MAX_ELEMENTS_VERTICAL = (START_Y - 100) / VERTICAL_SPACING;
}

HashTable::~HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *current = table[i];
        while (current != nullptr)
        {
            HashNode *next = current->next;
            delete current;
            current = next;
        }
    }
}

int HashTable::calculateXORHash(const std::string &value)
{
    int hash = 0;
    for (char c : value)
    {
        hash = (hash * 31 + (isLetterMode ? toupper(c) : c)) % TABLE_SIZE;
    }
    return hash;
}

int HashTable::hashFunction(std::string value)
{
    if (value.empty())
        return 0;
    return calculateXORHash(value);
}

void HashTable::drawCurvedArrow(int x1, int y1, int x2, int y2)
{
    // Set a bright color that will be clearly visible
    setcolor(LIGHTGREEN);

    // Draw the main connecting line
    line(x1, y1, x2, y2);

    // Draw a simple arrowhead (two short lines)
    int arrowLength = 8; // Shorter arrow head
    int dx = x2 - x1;
    int dy = y2 - y1;
    double angle = atan2(dy, dx);

    // Calculate arrow head points
    int ax1 = x2 - arrowLength * cos(angle - 0.5);
    int ay1 = y2 - arrowLength * sin(angle - 0.5);
    int ax2 = x2 - arrowLength * cos(angle + 0.5);
    int ay2 = y2 - arrowLength * sin(angle + 0.5);

    // Draw arrow head lines
    line(x2, y2, ax1, ay1);
    line(x2, y2, ax2, ay2);
}
void HashTable::insert(std::string value)
{
    if (value.empty())
        return;

    if (isLetterMode)
    {
        if (!std::all_of(value.begin(), value.end(), ::isalpha))
        {
            std::cout << "Error: Solo se permiten letras en esta tabla.\n";
            system("pause");
            return;
        }
        std::transform(value.begin(), value.end(), value.begin(), ::toupper);
    }
    else
    {
        if (!std::all_of(value.begin(), value.end(), ::isdigit))
        {
            std::cout << "Error: Solo se permiten numeros en esta tabla.\n";
            system("pause");
            return;
        }
    }

    int index = hashFunction(value);
    HashNode *newNode = new HashNode(value);
    newNode->next = table[index];
    table[index] = newNode;

    // Debug: verificar que el valor se insertó
    std::cout << "Insertado: " << value << " en indice: " << index << std::endl;
}

void HashTable::visualize()
{
    int gd = DETECT, gm;
    initwindow(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, "Visualizacion de Tabla Hash");

    setbkcolor(BLACK);
    cleardevice();

    // Título
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(LIGHTBLUE);
    std::string title = isLetterMode ? "Tabla Hash para Letras" : "Tabla Hash para Numeros";
    int titleWidth = textwidth((char *)title.c_str());
    int titleX = (getmaxx() - titleWidth) / 2;
    outtextxy(titleX, 30, (char *)title.c_str());

    std::cout << "Visualizando tabla hash..." << std::endl; // Debug

    // Dibujar tabla base
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int cellX = START_X + i * CELL_WIDTH;

        // Dibujar celda base (sin relleno)
        setfillstyle(EMPTY_FILL, WHITE);
        setcolor(WHITE);
        rectangle(cellX, START_Y, cellX + CELL_WIDTH - 10, START_Y + CELL_HEIGHT);

        // Dibujar índice
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        setcolor(YELLOW);
        char index[5];
        sprintf(index, "[%d]", i);
        outtextxy(cellX + 10, START_Y + CELL_HEIGHT + 5, index);

        // Dibujar nodos
        HashNode *current = table[i];
        int nodeY = START_Y - VERTICAL_SPACING;

        if (current == nullptr)
        {
            std::cout << "Indice " << i << " esta vacio." << std::endl; // Debug
        }

        while (current != nullptr)
        {
            std::cout << "Dibujando: " << current->data << " en indice: " << i << std::endl; // Debug

            // Dibujar rectángulo sin relleno para el nodo
            setfillstyle(EMPTY_FILL, WHITE);
            setcolor(WHITE);
            rectangle(cellX, nodeY, cellX + CELL_WIDTH - 10, nodeY + CELL_HEIGHT);

            // Dibujar el valor dentro del rectángulo
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            setcolor(WHITE);
            int textWidth = textwidth((char *)current->data.c_str());
            int textX = cellX + ((CELL_WIDTH - 10) - textWidth) / 2;
            outtextxy(textX, nodeY + CELL_HEIGHT / 4, (char *)current->data.c_str());

            // Dibujar línea conectora si hay un siguiente nodo
            if (current->next != nullptr)
            {
                setcolor(WHITE);
                int lineX = cellX + (CELL_WIDTH - 10) / 2;
                line(lineX, nodeY + CELL_HEIGHT, lineX, nodeY + VERTICAL_SPACING);
            }

            current = current->next;
            nodeY -= VERTICAL_SPACING;
        }
    }

    // Mensaje de salida
    setcolor(LIGHTGREEN);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    const char *msg = "Presione cualquier tecla para volver al menu...";
    int msgWidth = textwidth((char *)msg);
    outtextxy((getmaxx() - msgWidth) / 2, getmaxy() - 30, (char *)msg);

    while (!kbhit())
    {
        delay(100);
    }
    getch();
    closegraph();
}
