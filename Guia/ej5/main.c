#include "main.h"

int main(void){
    str_array_t *arreglo = strArrayNew(4); 
    printf("Capacidad: %d\n", arreglo->capacity);   
    printf("Tamaño: %d\n", arreglo->size);
    printf("Puntero: %p\n", (void*)arreglo->data);
    //Probamos la otr
    uint8_t tam = strArrayGetSize(arreglo);
    printf("Tamaño (con funcion): %d\n", tam);
    return 0;
}