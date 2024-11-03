#include "mainop2.h"

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

    destruirLista(cabeza);
    if (nodo1 == NULL){
        printf("Se libero el nodo 1");
    }
    if (nodo2 == NULL){
        printf("Se libero el nodo 2");
    }

    if (nodo3 == NULL){
        printf("Se libero el nodo 3");
    }

    return 0;
}
