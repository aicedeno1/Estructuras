#include <graphics.h>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <type_traits>
#include <limits>
#include <algorithm>
#include <cctype>
using namespace std;

template <typename T>
class TablaHashVisual
{
private:
    vector<T> tabla;
    int tamano;
    int metodoColision;
    int ANCHO_CELDA = 60;
    int ALTO_CELDA = 40;
    int PANTALLA_ANCHO;
    int PANTALLA_ALTO;
    int celdaPorPagina = 16;
    int paginaActual = 0;

    bool validarEntero(const string &input)
    {
        if (input.empty())
            return false;
        for (char c : input)
        {
            if (!isdigit(c) && c != '-')
                return false;
        }
        return true;
    }

    bool validarString(const string &input)
    {
        return !input.empty() && std::all_of(input.begin(), input.end(), [](char c)
                                             { return std::isalpha(c) || std::isspace(c); });
    }

    void iniciarGraficos()
    {
        PANTALLA_ANCHO = GetSystemMetrics(SM_CXSCREEN);
        PANTALLA_ALTO = GetSystemMetrics(SM_CYSCREEN);
        initwindow(PANTALLA_ANCHO, PANTALLA_ALTO, "Tabla Hash Grafica", -3, -3);
        ANCHO_CELDA = (PANTALLA_ANCHO - 100) / 16;
    }
    void dibujarTabla()
    {
        cleardevice();
        setbkcolor(BLACK);
        cleardevice();

        settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        setcolor(YELLOW);
        outtextxy(50, 30, const_cast<char *>("Tabla Hash Grafica"));

        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(LIGHTGREEN);
        string textoMetodo = "Metodo: " + obtenerNombreMetodo();
        outtextxy(50, 80, const_cast<char *>(textoMetodo.c_str()));

        setcolor(WHITE);
        for (int i = 0; i < tamano; i++)
        {
            int x = 50 + (i % 16) * (ANCHO_CELDA + 5);
            int y = PANTALLA_ALTO / 3 + (i / 16) * (ALTO_CELDA + 20);

            setcolor(LIGHTBLUE);
            rectangle(x, y, x + ANCHO_CELDA, y + ALTO_CELDA);

            setcolor(LIGHTGREEN);
            char idx[10];
            sprintf(idx, "%d", i);
            outtextxy(x + ANCHO_CELDA / 3, y - 20, idx);

            if (tabla[i] != T())
            {
                setcolor(WHITE);
                settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
                string contenido;
                if constexpr (is_same<T, int>::value)
                {
                    contenido = to_string(tabla[i]);
                }
                else
                {
                    contenido = tabla[i];
                }
                outtextxy(x + 5, y + ALTO_CELDA / 3, const_cast<char *>(contenido.c_str()));
            }
        }
    }

    string obtenerNombreMetodo()
    {
        switch (metodoColision)
        {
        case 1:
            return "Sondeo Lineal";
        case 2:
            return "Sondeo Cuadratico";
        case 3:
            return "Hash Doble";
        default:
            return "Desconocido";
        }
    }

    int funcionHash(const T &clave)
    {
        if constexpr (is_same<T, int>::value)
        {
            return clave % tamano; // Aplicamos módulo tamaño aquí
        }
        else
        {
            int hash = 0;
            for (char c : clave)
            {
                hash = (hash * 31 + c) % tamano;
            }
            return hash;
        }
    }

    template <typename U>
    int obtenerHashEspecifico(const U &valor)
    {
        return static_cast<int>(valor) % 7;
    }

    int obtenerHashEspecifico(const string &valor)
    {
        int hash = 0;
        for (char c : valor)
        {
            hash = (hash * 31 + c) % tamano;
        }
        return hash;
    }

    int hashSecundario(const T &elem)
    {
        if constexpr (is_same<T, int>::value)
        {
            // Modificamos para asegurar un valor positivo
            return 7 - (elem % 7); // Esto asegura que siempre sea positivo
        }
        else
        {
            int suma = 0;
            for (char c : elem)
            {
                suma += c;
            }
            return 7 - (suma % 7); // Igualmente aseguramos valor positivo
        }
    }

    template <typename U>
    int obtenerHashSecundarioEspecifico(const U &valor)
    {
        return 1 - (static_cast<int>(valor) % 7);
    }

    int obtenerHashSecundarioEspecifico(const string &valor)
    {
        int suma = 0;
        for (char c : valor)
        {
            suma += c;
        }
        return 1 - (suma % 7);
    }

public:
    TablaHashVisual() : tamano(0), metodoColision(1) {}

    void inicializar(int tamanioTabla, int metodo)
    {
        tamano = tamanioTabla;
        metodoColision = metodo;
        tabla.clear();
        tabla.resize(tamano, T());
        iniciarGraficos();
        dibujarTabla();
    }

    int obtenerSiguientePosicion(int posOriginal, int i, const T &elem)
    {
        switch (metodoColision)
        {
        case 1: // Sondeo Lineal
            return (posOriginal + i) % tamano;
        case 2: // Sondeo Cuadrático
            return (posOriginal + i * i) % tamano;
        case 3: // Hash Doble
        {
            // Calculamos el hash secundario una sola vez
            int h2 = hashSecundario(elem);
            if (h2 <= 0)
                h2 = 1; // Nos aseguramos que h2 sea positivo y no sea 0

            // La fórmula correcta para hash doble es:
            // pos = (h1 + i * h2) % tamano
            // donde h1 es posOriginal
            return (posOriginal + i * h2) % tamano;
        }
        default:
            return posOriginal;
        }
    }

    bool insertar(const T &elem)
    {
        int i = 0;
        int posOriginal = funcionHash(elem);

       

        while (i < tamano)
        {
            int pos = obtenerSiguientePosicion(posOriginal, i, elem);
            if (tabla[pos] == T())
            {
                tabla[pos] = elem;
                dibujarTabla();
                return true;
            }
            i++;
        }
        return false;
    }

    bool eliminar(const T &elem)
    {
        int posOriginal = funcionHash(elem);
        int i = 0;

        while (i < tamano)
        {
            int pos = obtenerSiguientePosicion(posOriginal, i, elem);
            if (tabla[pos] == elem)
            {
                tabla[pos] = T();
                dibujarTabla();
                return true;
            }
            i++;
        }
        return false;
    }

    void mostrarGrafico()
    {
        int totalPaginas = (tamano + celdaPorPagina - 1) / celdaPorPagina;
        while (true)
        {
            dibujarTabla();
            if (getch() == 27)
                return;
        }
    }

    void cerrar()
    {
        closegraph();
    }
};

template <typename T>
T obtenerEntradaValida()
{
    T entrada;
    while (true)
    {
        if (cin >> entrada)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return entrada;
        }
        cout << "Entrada invalida. Intente nuevamente: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void mostrarMenuPrincipal()
{
    system("cls");
    cout << "\n=== SIMULADOR DE TABLA HASH ===\n";
    cout << "1. Crear Tabla Hash para Enteros\n";
    cout << "2. Crear Tabla Hash para Strings\n";
    cout << "3. Salir\n";
    cout << "\nElija una opcion: ";
}

void mostrarMenuMetodos()
{
    system("cls");
    cout << "\n=== SELECCIONE METODO DE COLISION ===\n";
    cout << "1. Sondeo Lineal\n";
    cout << "2. Sondeo Cuadratico\n";
    cout << "3. Hash Doble\n";
    cout << "\nElija una opcion: ";
}

template <typename T>
void procesarTablaHash()
{
    TablaHashVisual<T> tabla;
    int tamano, metodo;

    mostrarMenuMetodos();
    metodo = obtenerEntradaValida<int>();
    while (metodo < 1 || metodo > 3)
    {
        cout << "Metodo invalido. Ingrese un numero entre 1 y 3: ";
        metodo = obtenerEntradaValida<int>();
    }

    cout << "Ingrese tamano de la tabla: ";
    tamano = obtenerEntradaValida<int>();
    while (tamano <= 0)
    {
        cout << "Tamano invalido. Ingrese un numero positivo: ";
        tamano = obtenerEntradaValida<int>();
    }

    tabla.inicializar(tamano, metodo);

    while (true)
    {
        system("cls");
        cout << "\n=== TABLA HASH " << (is_same<T, int>::value ? "ENTEROS" : "STRINGS") << " ===\n";
        cout << "1. Insertar Elemento\n";
        cout << "2. Eliminar Elemento\n";
        cout << "3. Volver al Menu Principal\n";
        cout << "\nElija una opcion: ";

        int opcion = obtenerEntradaValida<int>();

        switch (opcion)
        {
        case 1:
        {
            cout << "Ingrese elemento a insertar: ";
            T elemento = obtenerEntradaValida<T>();
            if (tabla.insertar(elemento))
            {
                cout << "Elemento insertado exitosamente.\n";
            }
            else
            {
                cout << "No se pudo insertar el elemento.\n";
            }
            break;
        }
        case 2:
        {
            cout << "Ingrese elemento a eliminar: ";
            T elemento = obtenerEntradaValida<T>();
            if (tabla.eliminar(elemento))
            {
                cout << "Elemento eliminado exitosamente.\n";
            }
            else
            {
                cout << "Elemento no encontrado.\n";
            }
            break;
        }
        case 3:
            tabla.cerrar();
            return;
        default:
            cout << "Opcion invalida.\n";
        }
        system("pause");
    }
}

int main()
{
    while (true)
    {
        mostrarMenuPrincipal();
        int opcion = obtenerEntradaValida<int>();

        switch (opcion)
        {
        case 1:
            procesarTablaHash<int>();
            break;
        case 2:
            procesarTablaHash<string>();
            break;
        case 3:
            return 0;
        default:
            cout << "Opcion invalida.\n";
            system("pause");
        }
    }
    return 0;
}