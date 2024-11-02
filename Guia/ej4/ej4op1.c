#include <stddef.h>
#include "ej4op1.h"

//int32_t valorEn(uint32_t indice, node_t* cabeza){   
    //return (cabeza[indice*16])->valor; tiene que avanzar 16 bytes para ir al siguiente stuckt q es el siguiente nodo de la lista
//}

// puntero: direccion que guarda una direccion de memoria

//Con while :p

int32_t valorEn(uint32_t indice, node_t* cabeza){   
    node_t* actual = cabeza; // Iniciamos en el cabeza de la lista
    uint32_t i = 0;     // Inicializamos el índice

    while (actual != NULL) { // Mientras no lleguemos al final de la lista
        if (i == indice) {     // Comparamos el índice actual con i
            return actual->valor; // Devolvemos el valor del nodo
        }
        actual = actual->siguiente; // Avanzamos al siguiente nodo
        i++;                 // Incrementamos el índice
    }

    return -1; // Si no se encontró el elemento, devolvemos -1
}