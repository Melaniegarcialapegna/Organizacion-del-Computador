typedef struct node_str { // tiene que estar alineado a 8
    struct node_str* siguiente;//8 bytes ->0(arranca)
    int32_t valor; //4 bytes              ->8(arranca)
} node_t;
// 0X00 12345678
// 0x08 1234pppp 
//-> Total de 16

node_t* agregarAdelante(int32_t valor, node_t* siguiente){
    node_t *nodo = malloc(sizeof(node_t));
    nodo->valor = valor;
    nodo->siguiente = siguiente;
    return nodo;
}


//r14: ssssssss


//r12d: xxxxnnnn
//
//En memoria lo queremos:  nnnnxxxx -> shifteamos a izq