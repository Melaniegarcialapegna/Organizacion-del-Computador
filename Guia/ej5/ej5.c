#include "ej5.h"

str_array_t *strArrayNew(uint8_t capacity){
    str_array_t *arrNuevo = malloc(sizeof(str_array_t));
    arrNuevo->capacity = capacity;
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
    char *borrado = malloc(sizeof(char));//malloc pq nos pide que devolvamos un puntero
    borrado = a->data[i];
    //Meanie/0
    // a[i] = a[i+1]
    // if a[i] == "\0"{
    //     break;
    // }
    while (a->data[i] != "\0"){
        a[i] = a[i+1];
        i++;
    }
    return borrado;
}


void strArrayDelete(str_array_t* a){
    int32_t cont = 0;

    

    free(a);
}
