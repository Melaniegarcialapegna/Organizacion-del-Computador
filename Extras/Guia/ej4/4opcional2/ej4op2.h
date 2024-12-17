#ifndef EJ4OP2
#define EJ4OP2

#include <stdint.h>

typedef struct node_str { 
    struct node_str* siguiente;//8 bytes      offset:0
    int32_t valor;             //4 bytes      offset:8 
} node_t; //size: 16 bytes

#endif