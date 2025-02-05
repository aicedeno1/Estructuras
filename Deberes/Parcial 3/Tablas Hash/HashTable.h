#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"
#include <graphics.h>
#include <string>
#include <windows.h>

class HashTable
{
private:
    static const int TABLE_SIZE = 13;
    HashNode *table[TABLE_SIZE];
    bool isLetterMode;
    static float prevx;
    static float prevy;

    // Dimensiones y configuración visual
    int CELL_WIDTH;
    int CELL_HEIGHT;
    int START_X;
    int START_Y;
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    int VERTICAL_SPACING;
    int ARROW_HEIGHT;
    int MAX_ELEMENTS_VERTICAL;

    // Constantes para las flechas
    static const int ARROW_HEAD_SIZE = 10;
    static const int ARROW_CURVE_OFFSET = 20;

    int hashFunction(std::string value);
    void drawCurvedArrow(int x1, int y1, int x2, int y2);
    void initializeGraphicsDimensions();
    int calculateXORHash(const std::string &value);

public:
    explicit HashTable(bool letterMode);
    ~HashTable();
    void insert(std::string value);
    void visualize();
    bool isLetterTable() const { return isLetterMode; }
};

#endif