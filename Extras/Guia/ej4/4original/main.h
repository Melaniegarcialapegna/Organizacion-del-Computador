#ifndef EJERCICIO4
#define EJERCICIO4
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct node_str { // tiene que estar alineado a 8
    struct node_str* siguiente;//8 bytes ->0(arranca)
    int32_t valor; //4 bytes              ->8(arranca)
} node_t;

node_t* agregarAdelante(int32_t valor, node_t* siguiente);
node_t* agregarAdelante_asm(int32_t valor, node_t* siguiente);

#endif