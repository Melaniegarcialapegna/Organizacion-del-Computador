#ifndef CONSTANTE
#define CONSTANTE
#include <stdint.h> // importar numeros
#include <stdlib.h> //importar malloc y free

typedef struct s_array {
    type_t type; //4 bytes
    uint8_t size; //1 byte
    uint8_t capacity; //1 byte
    void** data; //8 bytes pq puntero
} array_t; //16 bytes

typedef enum e_type {
    TypeNone = 0, 
    TypeInt = 1, 
    TypeString = 2,
    TypeCard = 3
} type_t; //4 bytes(con signo)

//NO ES NECESARIO DECLARAR LA FUNCION -> void* (*func)(void*); PQ ES UN ARGUMENTO
array_t* arrayMap(array_t* array, void* (*func)(void*));

#endif