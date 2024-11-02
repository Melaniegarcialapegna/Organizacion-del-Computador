#include "main.h"

int main(void){
    int32_t valor = 4;
    node_t *nodo = malloc(sizeof(node_t));
    nodo->siguiente = NULL;
    nodo->valor = 2;
    nodo = agregarAdelante_asm(valor, nodo);
    printf("%d\n", nodo->valor); //Deberia imprimir 4
    free(nodo);
    return 0;
}

//PONER EL SECTION.TEXT AL PRINCIPIO DEL ASM

//Ejecutar:

//Compilar el archivo C:
//gcc -c main.c -o main.o

//Compilar el archivo en asm
//nasm -f elf64 ej4.asm -o ej4.o


//OPCIONAL: as -o ej4.o ej4.asm


//Vincular:
//gcc main.o ej4.o -o ejecutable -no-pie

//Ejecutar:
//./ejecutable