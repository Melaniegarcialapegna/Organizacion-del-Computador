#include <stdio.h>

// Función para obtener el índice de la letra (A=0, B=1, ..., Z=25)
int ord(char c) {
    return c - 'A';
}

// Función para obtener la letra correspondiente a un índice (0=A, 1=B, ..., 25=Z)
char chr(int n) {
    return 'A' + n;
}

char* cesar(char* palabra,int num){
    //Malloc te devuelve un puntero con ese espacio
    char* resultado = malloc(sizeof(char)*strlen(palabra)+1); //El +1 es por el /0 al final de la cadena
    
    //strlen -> no cuenta el /0
    //Ejemplo:
    //CASA/0
    //sterlen(CASA/0) = 4 (NO cuenta el /0) -> por eso lo agregamos al final
    for (int i=0; i< strlen(palabra); i++){   
        int indice = ord(palabra[i]) + num;
        indice = indice % 26; //Modulo
        resultado[i] = chr(indice); 
    }
    resultado[strlen(palabra)] = '\0';
    return resultado;
}
