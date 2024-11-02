#include "main.h"

int main(void){
    int32_t valor = 4;
    node_t *nodo = malloc(sizeof(node_t));
    nodo->siguiente = NULL;
    nodo->valor = 2;
    nodo = agregarAdelante_asm(valor, nodo);
    printf("%d\n", nodo->valor);
    return 0;
}