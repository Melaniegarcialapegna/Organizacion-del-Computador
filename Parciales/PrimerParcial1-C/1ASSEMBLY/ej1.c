#include "ej1.h"


array_t* arrayMap(array_t* array, void* (*func)(void*)){    
    array_t* nuevoArr = malloc(sizeof(array_t));
    nuevoArr->type = array->type;
    nuevoArr->size = array->size;
    nuevoArr->capacity = array->capacity;
    nuevoArr->data = malloc(sizeof(void*)*(nuevoArr->capacity)); //el malloc devuelve un puntero a la primera cajita dentro de la cajota(de tamanio capacidad) nuevoArr
    
    int contador = 0;
    int largo = array->size;
    while (contador < largo){
        void *elemento  = (array->data)[contador];
        void *elementoFuncAplicada = func(elemento);
        (nuevoArr->data)[contador] = elementoFuncAplicada;
        contador++;
    }
    return nuevoArr;
}