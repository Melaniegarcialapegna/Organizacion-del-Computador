#include <stddef.h> // Agrega el null
// #include <stdint.h> este importa los numeros tipo int32_t
#include "ej4op2.h"


void destruirLista(node_t* cabeza){
    node_t *nodoSiguiente = malloc(sizeof(node_t));
    while(cabeza != NULL){
        nodoSiguiente = cabeza->siguiente;
        free(cabeza);
        cabeza = nodoSiguiente;
    }
}