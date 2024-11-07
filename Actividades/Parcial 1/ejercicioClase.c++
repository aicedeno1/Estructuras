#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
int ingresar (char *);
int ingresar (char *msj){
    printf("%s",msj);
    char cad[10],c;
    int valor, i=0;
    while((c=getch())!=13){
        if(c>='0'&& c<='9'){
            printf("%c",c);
            cad[i++]=c;
        }
    }
    cad[i++]='\0';
    valor=atoi(cad);
    return valor;
}
int main(){
    printf("\n%d\n",ingresar("ingrese un valor entero"));
    return 0;
}