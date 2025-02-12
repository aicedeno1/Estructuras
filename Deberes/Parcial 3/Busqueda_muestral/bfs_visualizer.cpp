#include <graphics.h>
#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
using namespace std;

struct Point {
    int x, y;
};

class BFSVisualizer {
private:
    vector<vector<int>> adjacencyMatrix;
    vector<vector<int>> adjacencyList;
    vector<bool> visited;
    vector<Point> nodePositions;
    int numNodes;
    int windowWidth;
    int windowHeight;
    bool isDirected;
    
    const int NODE_COLOR = WHITE;
    const int VISITED_COLOR = GREEN;
    const int EDGE_COLOR = WHITE;
    const int TEXT_COLOR = WHITE;

    char textBuffer[100];
    
    void initializeGraph(bool isLarge, bool directed) {
        numNodes = isLarge ? 17 : 7;
        isDirected = directed;
        
        // Limpiar completamente las estructuras de datos
        adjacencyMatrix.clear();
        adjacencyList.clear();
        visited.clear();
        nodePositions.clear();
        
        // Reinicializar con los nuevos tamaños
        adjacencyMatrix.resize(numNodes, vector<int>(numNodes, 0));
        adjacencyList.resize(numNodes);
        visited.resize(numNodes, false);
        nodePositions.resize(numNodes);
        
        srand(time(0));
        for(int i = 0; i < numNodes; i++) {
            for(int j = (isDirected ? 0 : i + 1); j < numNodes; j++) {
                if(i != j && (rand() % 100 < 30)) {  // 30% de probabilidad de conexión
                    adjacencyMatrix[i][j] = 1;
                    adjacencyList[i].push_back(j);
                    if(!isDirected) {
                        adjacencyMatrix[j][i] = 1;
                        adjacencyList[j].push_back(i);
                    }
                }
            }
        }
        
        calculateNodePositions();
    }
    
    void calculateNodePositions() {
        int centerX = windowWidth / 2;
        int centerY = windowHeight / 3;
        int radius = min(windowWidth, windowHeight) / 4;
        
        for(int i = 0; i < numNodes; i++) {
            double angle = 2 * M_PI * i / numNodes;
            nodePositions[i].x = centerX + radius * cos(angle);
            nodePositions[i].y = centerY + radius * sin(angle);
        }
    }
    
    void drawArrow(int x1, int y1, int x2, int y2) {
        const double PI = 3.14159265;
        int arrowLength = 15;
        double angle = atan2(y2 - y1, x2 - x1);
        
        line(x1, y1, x2, y2);
        
        if(isDirected) {
            int arrowX1 = x2 - arrowLength * cos(angle - PI/6);
            int arrowY1 = y2 - arrowLength * sin(angle - PI/6);
            int arrowX2 = x2 - arrowLength * cos(angle + PI/6);
            int arrowY2 = y2 - arrowLength * sin(angle + PI/6);
            
            line(x2, y2, arrowX1, arrowY1);
            line(x2, y2, arrowX2, arrowY2);
        }
    }
    
    void drawNode(int node, int color) {
        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        circle(nodePositions[node].x, nodePositions[node].y, 20);
        fillellipse(nodePositions[node].x, nodePositions[node].y, 20, 20);
        
        sprintf(textBuffer, "%d", node);
        setcolor(TEXT_COLOR);
        outtextxy(nodePositions[node].x - 6, nodePositions[node].y - 8, textBuffer);
    }
    
    void drawEdge(int from, int to, int color) {
        setcolor(color);
        
        if(isDirected) {
            double angle = atan2(nodePositions[to].y - nodePositions[from].y, 
                               nodePositions[to].x - nodePositions[from].x);
            int startX = nodePositions[from].x + 20 * cos(angle);
            int startY = nodePositions[from].y + 20 * sin(angle);
            int endX = nodePositions[to].x - 20 * cos(angle);
            int endY = nodePositions[to].y - 20 * sin(angle);
            drawArrow(startX, startY, endX, endY);
        } else {
            line(nodePositions[from].x, nodePositions[from].y,
                 nodePositions[to].x, nodePositions[to].y);
        }
    }
    
    void displayAdjacencyMatrix() {
        cleardevice();
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        
        int startX = 50;
        int startY = 50;
        int cellSize = 30;
        
        for(int i = 0; i < numNodes; i++) {
            for(int j = 0; j < numNodes; j++) {
                rectangle(startX + j*cellSize, startY + i*cellSize,
                         startX + (j+1)*cellSize, startY + (i+1)*cellSize);
                
                sprintf(textBuffer, "%d", adjacencyMatrix[i][j]);
                outtextxy(startX + j*cellSize + 10, startY + i*cellSize + 8, textBuffer);
            }
        }
    }
    
    void displayAdjacencyList() {
        cleardevice();
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        
        int startX = 50;
        int startY = 50;
        int lineHeight = 30;
        
        for(int i = 0; i < numNodes; i++) {
            sprintf(textBuffer, "%d -> ", i);
            outtextxy(startX, startY + i*lineHeight, textBuffer);
            
            int offsetX = 60;
            for(int neighbor : adjacencyList[i]) {
                sprintf(textBuffer, "%d ", neighbor);
                outtextxy(startX + offsetX, startY + i*lineHeight, textBuffer);
                offsetX += 30;
            }
        }
    }
    
    void displayGraph() {
        cleardevice();
        
        // Primero dibujamos las aristas
        for(int i = 0; i < numNodes; i++) {
            for(int j = 0; j < numNodes; j++) {
                if(adjacencyMatrix[i][j]) {
                    drawEdge(i, j, EDGE_COLOR);
                }
            }
        }
        
        // Luego los nodos para que queden encima
        for(int i = 0; i < numNodes; i++) {
            drawNode(i, NODE_COLOR);
        }
    }

    void runBFS() {
        char bfsPrompt[] = "Ingrese el nodo inicial para BFS (0-n): ";
        outtextxy(50, windowHeight - 100, bfsPrompt);
        char startNode[3];
        int idx = 0;
        char ch;
        while((ch = getch()) != 13 && idx < 2) {
            if(isdigit(ch)) {
                startNode[idx++] = ch;
                startNode[idx] = '\0';
                outtextxy(350, windowHeight - 100, startNode);
            }
        }
        
        int start = atoi(startNode);
        if(start >= 0 && start < numNodes) {
            queue<int> q;
            fill(visited.begin(), visited.end(), false);
            
            q.push(start);
            visited[start] = true;
            drawNode(start, VISITED_COLOR);
            
            while(!q.empty()) {
                int current = q.front();
                q.pop();
                
                for(int i = 0; i < numNodes; i++) {
                    if(adjacencyMatrix[current][i] && !visited[i]) {
                        q.push(i);
                        visited[i] = true;
                        drawNode(i, VISITED_COLOR);
                        delay(500);
                    }
                }
            }
        }
    }

public:
    BFSVisualizer() {
        windowWidth = 800;
        windowHeight = 600;
        int gd = DETECT, gm;
        initgraph(&gd, &gm, nullptr);
        
        int errorcode = graphresult();
        if (errorcode != grOk) {
            cout << "Error al inicializar graficos: " << grapherrormsg(errorcode) << endl;
            exit(1);
        }
        
        // Inicializar con un grafo por defecto
        initializeGraph(false, false);
    }
    
    void run() {
        char mainMenu[] = "Menu Principal:";
        char opt1[] = "1. Visualizar Grafo";
        char opt2[] = "2. Ver Lista de Adyacencia";
        char opt3[] = "3. Ver Matriz de Adyacencia";
        char opt4[] = "4. Generar Nuevo Grafo";
        char opt5[] = "5. Salir";
        char sizePrompt[] = "Seleccione el tamanio:";
        char sizeOpt1[] = "1. Pequenio (7 nodos)";
        char sizeOpt2[] = "2. Grande (17 nodos)";
        char typePrompt[] = "Seleccione el tipo de grafo:";
        char typeOpt1[] = "1. No Dirigido";
        char typeOpt2[] = "2. Dirigido";
        char continuePrompt[] = "Presione cualquier tecla para continuar...";

        while(true) {
            cleardevice();
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            
            // Menú principal
            outtextxy(50, 50, mainMenu);
            outtextxy(50, 100, opt1);
            outtextxy(50, 150, opt2);
            outtextxy(50, 200, opt3);
            outtextxy(50, 250, opt4);
            outtextxy(50, 300, opt5);
            
            char option = getch();
            
            if(option == '5') break;
            
            if(option == '4') {
                // Selección de tamaño
                cleardevice();
                outtextxy(50, 50, sizePrompt);
                outtextxy(50, 100, sizeOpt1);
                outtextxy(50, 150, sizeOpt2);
                char size = getch();
                bool isLarge = (size == '2');
                
                // Selección de tipo
                cleardevice();
                outtextxy(50, 50, typePrompt);
                outtextxy(50, 100, typeOpt1);
                outtextxy(50, 150, typeOpt2);
                char type = getch();
                bool isDirected = (type == '2');
                
                initializeGraph(isLarge, isDirected);
                continue;
            }
            
            switch(option) {
                case '1': {
                    displayGraph();
                    runBFS();
                    break;
                }
                case '2': {
                    displayAdjacencyList();
                    break;
                }
                case '3': {
                    displayAdjacencyMatrix();
                    break;
                }
            }
            
            outtextxy(50, windowHeight - 50, continuePrompt);
            getch();
        }
    }

    ~BFSVisualizer() {
        closegraph();
    }
};

int main() {
    BFSVisualizer visualizer;
    visualizer.run();
    return 0;
}