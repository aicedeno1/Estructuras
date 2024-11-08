#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

int ingresar(char *);
float ingresoDatos();
float ingresoDatos(){
    
    char cad[10],c;
    int i=0;
    while((c=getch())!=13){
        if((c>='0'&&c<='9')|| c=='.'){
            printf("%c",c);
            cad[i++]=c;
        }
    }
    cad[i++]='\0';
    //cadena
    float valor=atof(cad);
    //int valor=atoi(cad);
    return valor;
}

int ingresar( char *msj){
    printf("%s",msj);
    int valor= ingresoDatos();
    return valor;

}

int main(){
    
    printf("\n %d\n",ingresar ("Ingrese un valor entero"));

return 0;

}