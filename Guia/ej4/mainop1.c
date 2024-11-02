#include "mainop1.h"

int main() {
    // Crear nodos de la lista enlazada
    node_t* nodo1 = malloc(sizeof(node_t));
    node_t* nodo2 = malloc(sizeof(node_t));
    node_t* nodo3 = malloc(sizeof(node_t));

    // Asignar valores y punteros
    nodo1->valor = 10;
    nodo1->siguiente = nodo2;

    nodo2->valor = 20;
    nodo2->siguiente = nodo3;

    nodo3->valor = 30;
    nodo3->siguiente = NULL;

    // Cabeza de la lista
    node_t* cabeza = nodo1;

    // Probar la función valorEn
    int32_t valor = valorEn(0, nodo1);
    printf("El valor es: %d \n", valor);

    // Liberar memoria
    free(nodo1);
    free(nodo2);
    free(nodo3);

    return 0;
}

// 2da opcion
//nnnnpppp