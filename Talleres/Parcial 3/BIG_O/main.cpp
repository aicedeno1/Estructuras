#include <graphics.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Función para limpiar la pantalla
void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class AlgoritmoEjemplo
{
public:
    string nombre;
    string descripcion;
    string casoUso;
    vector<double> tiemposReales;
};

class ComplejidadData
{
public:
    string nombre;
    string descripcion;
    vector<AlgoritmoEjemplo> ejemplos;
    vector<string> puntosCriticos;
    string mejorCaso;
    string peorCaso;
    double (*funcion)(double);
};

// Funciones de complejidad
double constante(double n) { return 1; }
double logaritmico(double n) { return log2(n + 1); }
double lineal(double n) { return n; }
double nLogN(double n) { return n * log2(n + 1); }
double cuadratico(double n) { return n * n; }
double exponencial(double n) { return pow(1.5, n); }

// Función para simular tiempo de ejecución
double simularTiempoEjecucion(string complejidad, int n)
{
    if (complejidad == "O(1)")
        return 1.0;
    if (complejidad == "O(log n)")
        return log2(n + 1);
    if (complejidad == "O(n)")
        return n;
    if (complejidad == "O(n log n)")
        return n * log2(n + 1);
    if (complejidad == "O(n^2)")
        return n * n;
    if (complejidad == "O(2^n)")
        return pow(1.5, n);
    return 0.0;
}

// Función para mostrar tabla de tiempos
void mostrarTablaComparativa(const vector<ComplejidadData> &complejidades)
{
    vector<int> tamanos = {10, 100, 1000, 10000};

    cout << "\n=== Tabla Comparativa de Tiempos ===\n\n";

    // Encabezado
    cout << setw(15) << "Complejidad";
    for (int n : tamanos)
    {
        cout << setw(15) << "n=" + to_string(n);
    }
    cout << endl;

    // Línea separadora
    cout << string(75, '-') << endl;

    // Datos
    for (const auto &comp : complejidades)
    {
        cout << setw(15) << comp.nombre;
        for (int n : tamanos)
        {
            double tiempo = simularTiempoEjecucion(comp.nombre, n);
            if (tiempo > 1000000)
            {
                cout << setw(15) << "∞";
            }
            else
            {
                cout << setw(15) << fixed << setprecision(2) << tiempo;
            }
        }
        cout << endl;
    }
}

// Función para comparar dos complejidades específicas
void compararDosComplejidades(const ComplejidadData &comp1, const ComplejidadData &comp2)
{
    cout << "\n=== Comparación Detallada: " << comp1.nombre << " vs " << comp2.nombre << " ===\n\n";

    // Puntos de cruce y diferencias
    cout << "Análisis de diferencias:\n";
    vector<int> puntos = {10, 100, 1000};
    for (int n : puntos)
    {
        double tiempo1 = simularTiempoEjecucion(comp1.nombre, n);
        double tiempo2 = simularTiempoEjecucion(comp2.nombre, n);
        double ratio = tiempo2 / tiempo1;

        cout << "n = " << n << ":\n";
        cout << comp1.nombre << ": " << fixed << setprecision(2) << tiempo1 << "\n";
        cout << comp2.nombre << ": " << fixed << setprecision(2) << tiempo2 << "\n";
        cout << "Ratio: " << fixed << setprecision(2) << ratio << "x\n\n";
    }

    // Recomendaciones
    cout << "Recomendaciones de uso:\n";
    cout << comp1.nombre << ":\n";
    for (const auto &ejemplo : comp1.ejemplos)
    {
        cout << "- " << ejemplo.nombre << ": " << ejemplo.casoUso << "\n";
    }

    cout << "\n"
         << comp2.nombre << ":\n";
    for (const auto &ejemplo : comp2.ejemplos)
    {
        cout << "- " << ejemplo.nombre << ": " << ejemplo.casoUso << "\n";
    }
}

// Función para mostrar análisis detallado
void mostrarAnalisisDetallado(const ComplejidadData &comp)
{
    cout << "\n=== Analisis Detallado: " << comp.nombre << " ===\n\n";

    cout << "Descripción:\n"
         << comp.descripcion << "\n\n";

    cout << "Casos:\n";
    cout << "- Mejor caso: " << comp.mejorCaso << "\n";
    cout << "- Peor caso: " << comp.peorCaso << "\n\n";

    cout << "Algoritmos ejemplo:\n";
    for (const auto &ejemplo : comp.ejemplos)
    {
        cout << "- " << ejemplo.nombre << "\n";
        cout << "  Descripcion: " << ejemplo.descripcion << "\n";
        cout << "  Caso de uso: " << ejemplo.casoUso << "\n\n";
    }

    cout << "Puntos criticos:\n";
    for (const auto &punto : comp.puntosCriticos)
    {
        cout << "- " << punto << "\n";
    }
    cout << endl;
}
void graficarComplejidad(const string &nombre, double (*funcion)(double), int color)
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int maxX = getmaxx();
    int maxY = getmaxy();
    cleardevice();

    // Fondo negro para mejor contraste
    setbkcolor(BLACK);
    cleardevice();

    // Ejes
    setcolor(WHITE);
    line(50, maxY - 50, maxX - 50, maxY - 50); // Eje X
    line(50, maxY - 50, 50, 50);               // Eje Y

    // Cuadrícula para mejor referencia
    setcolor(DARKGRAY);
    setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
    for (int i = 1; i <= 10; i++)
    {
        int xPos = 50 + (i * (maxX - 100) / 10);
        line(xPos, maxY - 50, xPos, 50); // Líneas verticales

        int yPos = maxY - 50 - (i * (maxY - 100) / 10);
        line(50, yPos, maxX - 50, yPos); // Líneas horizontales
    }

    // Flechas en los ejes
    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    line(50, 50, 45, 60);                             // Flecha Y
    line(50, 50, 55, 60);                             // Flecha Y
    line(maxX - 50, maxY - 50, maxX - 60, maxY - 55); // Flecha X
    line(maxX - 50, maxY - 50, maxX - 60, maxY - 45); // Flecha X

    // Título
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(maxX / 2 - 100, 20, const_cast<char *>(nombre.c_str()));

    // Etiquetas
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    outtextxy(20, maxY / 2, "Tiempo");
    outtextxy(maxX / 2, maxY - 30, "Tamano de entrada (n)");

    // Marcas en los ejes X e Y con valores
    setcolor(LIGHTGRAY);
    for (int i = 0; i <= 10; i += 2)
    {
        int xPos = 50 + (i * (maxX - 100) / 10);
        line(xPos, maxY - 50, xPos, maxY - 45); // Marca en X
        char xLabel[10];
        sprintf(xLabel, "%d", i);
        outtextxy(xPos - 5, maxY - 40, xLabel);
    }

    // Graficar función - USAR ROJO PARA TODAS LAS COMPLEJIDADES
    setcolor(RED);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);

    vector<pair<double, double>> puntos;
    for (double n = 0; n <= 10; n += 0.05)
    { // Reducido el paso para líneas más suaves
        puntos.push_back({n, funcion(n)});
    }

    // Normalizar valores
    double maxY_value = 0;
    for (const auto &punto : puntos)
    {
        maxY_value = max(maxY_value, punto.second);
    }

    // Área bajo la curva (opcional)
    if (maxY_value > 0)
    {
        // Versión semitransparente del color principal (simulado con un patrón)
        setfillstyle(LTSLASH_FILL, color);

        int poly[202]; // Para 100 puntos (máx), cada punto tiene x,y
        int idx = 0;

        for (size_t i = 0; i < puntos.size(); i++)
        {
            int x = 50 + (puntos[i].first * (maxX - 100) / 10);
            int y = maxY - 50 - (puntos[i].second * 300 / maxY_value);

            if (idx < 200)
            {
                poly[idx++] = x;
                poly[idx++] = y;
            }
        }

        // Añadir los puntos base para cerrar el polígono
        poly[idx++] = 50 + (puntos.back().first * (maxX - 100) / 10);
        poly[idx++] = maxY - 50;
        poly[idx++] = 50;
        poly[idx++] = maxY - 50;

        fillpoly(idx / 2, poly);
    }

    // Dibujar la línea principal con más grosor
    setlinestyle(SOLID_LINE, 0, USERBIT_LINE); // Línea muy gruesa
    setcolor(RED);                             // Color rojo para todas las complejidades

    for (size_t i = 1; i < puntos.size(); i++)
    {
        int x1 = 50 + (puntos[i - 1].first * (maxX - 100) / 10);
        int x2 = 50 + (puntos[i].first * (maxX - 100) / 10);
        int y1 = maxY - 50 - (puntos[i - 1].second * 300 / maxY_value);
        int y2 = maxY - 50 - (puntos[i].second * 300 / maxY_value);

        // Dibujar línea gruesa usando múltiples líneas cercanas
        for (int offset = -1; offset <= 1; offset++)
        {
            line(x1, y1 + offset, x2, y2 + offset);
            line(x1 + offset, y1, x2 + offset, y2);
        }
    }

    // Leyenda
    setcolor(WHITE);
    rectangle(maxX - 200, 50, maxX - 50, 100);
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(maxX - 100, 75, WHITE);

    setcolor(RED);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(maxX - 180, 75, maxX - 150, 75);

    setcolor(WHITE);
    outtextxy(maxX - 140, 70, const_cast<char *>(nombre.c_str()));

    // Esperar por una tecla
    getch();
    closegraph();
}

// Función principal del menú
void mostrarMenu(const vector<ComplejidadData> &complejidades)
{
    while (true)
    {
        limpiarPantalla();
        cout << "\n=== Analisis de Complejidades Algoritmicas ===\n";
        cout << "1. Ver tabla comparativa de todos los modelos\n";
        cout << "2. Ver analisis detallado de una complejidad\n";
        cout << "3. Comparar dos complejidades\n";
        cout << "4. Salir\n";
        cout << "Elija una opcion: ";

        int opcion;
        cin >> opcion;

        limpiarPantalla();

        if (opcion == 1)
        {
            mostrarTablaComparativa(complejidades);
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        else if (opcion == 2)
        {
            cout << "\nSeleccione una complejidad:\n";
            for (size_t i = 0; i < complejidades.size(); i++)
            {
                cout << i + 1 << ". " << complejidades[i].nombre << "\n";
            }
            int seleccion;
            cin >> seleccion;

            if (seleccion >= 1 && seleccion <= complejidades.size())
            {
                limpiarPantalla();
                const auto &comp = complejidades[seleccion - 1];
                mostrarAnalisisDetallado(comp);

                cout << "\nPresione Enter para ver la grafica...";
                cin.ignore();
                cin.get();

                // Mostrar gráfica
                int color;
                switch (seleccion)
                {
                case 1:
                    color = YELLOW;
                    break;
                case 2:
                    color = GREEN;
                    break;
                case 3:
                    color = BLUE;
                    break;
                case 4:
                    color = MAGENTA;
                    break;
                case 5:
                    color = RED;
                    break;
                default:
                    color = WHITE;
                }
                graficarComplejidad(comp.nombre, comp.funcion, color);
            }
        }
        else if (opcion == 3)
        {
            cout << "\nSeleccione primera complejidad:\n";
            for (size_t i = 0; i < complejidades.size(); i++)
            {
                cout << i + 1 << ". " << complejidades[i].nombre << "\n";
            }
            int sel1, sel2;
            cin >> sel1;
            cout << "Seleccione segunda complejidad:\n";
            cin >> sel2;

            if (sel1 >= 1 && sel1 <= complejidades.size() &&
                sel2 >= 1 && sel2 <= complejidades.size())
            {
                limpiarPantalla();
                compararDosComplejidades(complejidades[sel1 - 1], complejidades[sel2 - 1]);
                cout << "\nPresione Enter para continuar...";
                cin.ignore();
                cin.get();
            }
        }
        else if (opcion == 4)
        {
            break;
        }
    }
}
int main()
{
    vector<ComplejidadData> complejidades = {
        {"O(1)",
         "Tiempo constante independiente del tamano de entrada",
         {{"Hash Table",
           "Acceso directo a elementos mediante clave",
           "Ideal para busquedas rapidas con clave unica",
           {}},
          {"Array Indexing",
           "Acceso a elemento por indice",
           "Acceso directo a posiciones conocidas",
           {}}},
         {"Operacion mas rapida posible",
          "Excelente para operaciones frecuentes"},
         "Acceso directo",
         "Igual al mejor caso",
         constante},
        {"O(log n)",
         "Tiempo logaritmico - crece muy lentamente",
         {{"Binary Search",
           "Busqueda en datos ordenados",
           "Busquedas eficientes en grandes conjuntos ordenados",
           {}},
          {"Binary Tree Operations",
           "Operaciones en arboles balanceados",
           "Estructuras de datos jerarquicas",
           {}}},
         {"Muy eficiente para grandes datos",
          "Cada operacion reduce el problema a la mitad"},
         "Elemento encontrado en primera division",
         "Elemento encontrado en ultima division",
         logaritmico},
        {"O(n)",
         "Tiempo lineal - crece proporcionalmente al input",
         {{"Linear Search",
           "Busqueda secuencial en array",
           "Busquedas en datos no ordenados",
           {}},
          {"Array Traversal",
           "Recorrido completo de array",
           "Procesamiento secuencial de datos",
           {}}},
         {"Recorre cada elemento una vez",
          "Tiempo proporcional al tamano de entrada"},
         "Elemento encontrado al inicio",
         "Elemento encontrado al final",
         lineal},
        {"O(n log n)",
         "Tiempo lineal-logaritmico",
         {{"Merge Sort",
           "Ordenamiento por mezcla",
           "Ordenamiento estable de grandes conjuntos",
           {}},
          {"Quick Sort",
           "Ordenamiento rapido",
           "Ordenamiento eficiente en memoria",
           {}}},
         {"Mejor complejidad posible para ordenamiento por comparacion",
          "Balance entre eficiencia y complejidad"},
         "Array casi ordenado",
         "Array en orden inverso",
         nLogN},
        {"O(n^2)",
         "Tiempo cuadratico - crece con el cuadrado del input",
         {{"Bubble Sort",
           "Ordenamiento por burbuja",
           "Ordenamiento simple para conjuntos pequenos",
           {}},
          {"Nested Loops",
           "Bucles anidados",
           "Comparaciones elemento a elemento",
           {}}},
         {"Ineficiente para grandes conjuntos",
          "Tiempo crece rapidamente con el tamano"},
         "Array ordenado",
         "Array en orden inverso",
         cuadratico},
        {"O(2^n)",
         "Tiempo exponencial - crece extremadamente rapido",
         {{"Recursive Fibonacci",
           "Fibonacci recursivo sin memorizacion",
           "Problemas con subproblemas superpuestos",
           {}},
          {"Traveling Salesman",
           "Problema del viajante (fuerza bruta)",
           "Problemas NP-completos",
           {}}},
         {"Impracticable para entradas grandes",
          "Tiempo crece exponencialmente"},
         "Problema minimal",
         "Problema completo",
         exponencial}};
    mostrarMenu(complejidades);
    return 0;
}