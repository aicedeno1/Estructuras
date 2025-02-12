#include <graphics.h>
#include <iostream>
using namespace std;

int main() {
    // Inicializar modo gráfico
    int gd = DETECT, gm;
    initgraph(&gd, &gm, nullptr);
    
    // Verificar si la inicialización fue exitosa
    int errorcode = graphresult();
    if (errorcode != grOk) {
        cout << "Error al inicializar graficos: " << grapherrormsg(errorcode) << endl;
        return 1;
    }
    
    // Dibujar un círculo simple
    circle(200, 200, 100);
    
    // Mostrar texto
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(150, 300, "Test de Graphics");
    
    // Esperar 3 segundos
    delay(3000);
    
    // Cerrar modo gráfico
    closegraph();
    return 0;
}