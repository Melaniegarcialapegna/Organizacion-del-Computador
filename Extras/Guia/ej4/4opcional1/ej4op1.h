#ifndef EJ4OP1
#define EJ4OP1

#include <stdint.h>

typedef struct node_str { // tiene que estar alineado a 8
    struct node_str* siguiente;//8 bytes ->0(arranca)
    int32_t valor; //4 bytes              ->8(arranca)
} node_t;

#endif