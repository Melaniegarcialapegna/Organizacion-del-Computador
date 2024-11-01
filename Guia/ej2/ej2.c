#include <stdio.h>

int prefijo_de(char* palabra1 , char* palabra2){
    // int contador = malloc(sizeof(int)); -> el malloc es solo para devolver punteros 
    int contador = 0;
    while( palabra1[contador] == palabra2[contador]){
        contador++;
    }
    return contador;
}

int main(void){
    printf("%d\n", prefijo_de("Astrologia", "Astrobort"));
}