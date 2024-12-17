#ifndef EJERCICIO4OP
#define EJERCICIO4OP

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct node_str {
    struct node_str* siguiente;
    int32_t valor;
} node_t;

void destruirLista(node_t* cabeza);

#endif