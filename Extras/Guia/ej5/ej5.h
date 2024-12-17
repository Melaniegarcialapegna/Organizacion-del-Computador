#ifndef EJERCICIO5
#define EJERCICIO5

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct str_array {
uint8_t size;              // 1bytes         offset:0
uint8_t capacity;          // 1bytes         offset:1 (padding de 6)
char** data;               // 8bytes(pq puntero)         offset:8
//doble puntero a un arreglo pq LOS ARREGLOS SON UN PUNTERO AL PRIMER CHAR
} str_array_t;//size: 16 bytes

str_array_t* strArrayNew(uint8_t capacity);
uint8_t strArrayGetSize(str_array_t* a);
char* strArrayGet(str_array_t* a, uint8_t i);
char* strArrayRemove(str_array_t* a, uint8_t i);
void strArrayDelete(str_array_t* a);

#endif