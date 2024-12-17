#include "ej5.h"

str_array_t *strArrayNew(uint8_t capacity){
    str_array_t *arrNuevo = malloc(sizeof(str_array_t));
    arrNuevo->capacity = capacity;
    arrNuevo->size=0;
    arrNuevo->data= malloc(sizeof(char*)*capacity); //es un puntero a un arreglo en el cual cada casilla tiene unn puntero a un arreglo de char* (ver dibujito notion)
    return arrNuevo;
}

uint8_t strArrayGetSize(str_array_t* a){
    return a->size;
}

char* strArrayGet(str_array_t* a, uint8_t i){
    if (i >= a->size){
        return NULL;
    }
    return a->data[i];
    // en assembler lo hacemos con while y vamos sumando de a 16 bytes :))
}

char* strArrayRemove(str_array_t* a, uint8_t i){
    if (i >= a->size){
        return NULL;
    }
    char *borrado = a->data[i];
    //Meanie/0
    // a[i] = a[i+1]
    // if a[i] == "\0"{
    //     break;
    // }
    for (uint8_t j = i; j < a->size - 1; j++) {
        a->data[j] = a->data[j + 1];
    }
    a->size--;
    return borrado;
}


void strArrayDelete(str_array_t* a){
    if (a) {
        for (uint8_t i = 0; i < a->size; i++) {
            free(a->data[i]);
        }
        free(a->data);
        free(a);
    }
}
