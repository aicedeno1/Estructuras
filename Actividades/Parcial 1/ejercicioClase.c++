#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

float ingresar(char *);
float ingresoDatos();
float ingresoDatos(){
    //(!((c>='0'&&c<='9')|| c=='.')&&!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))||(((c>='0'&&c<='9')|| c=='.')&&((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
    
    char cad[10],c;
    int i=0;
    while((c=getch())!=13){
        if(!((((c>='0'&&c<='9')|| c=='.')&&((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))||(!((c>='0'&&c<='9')|| c=='.')&&!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))))){
            printf("%c",c);
            cad[i++]=c;
        }
    }
    cad[i++]='\0';
    float valor=atof(cad);
    return valor;


}

float ingresar( char *msj){
    printf("%s",msj);
    float valor= ingresoDatos();
    return valor;

}

int main(){
    
    printf("\n %f\n",ingresar ("Ingrese un valor entero :"));

return 0;

}