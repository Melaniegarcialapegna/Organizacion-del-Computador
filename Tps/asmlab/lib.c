#include "lib.h"

funcCmp_t *getCompareFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcCmp_t *)&intCmp;
        break;
    case TypeString:
        return (funcCmp_t *)&strCmp;
        break;
    case TypeCard:
        return (funcCmp_t *)&cardCmp;
        break;
    default:
        break;
    }
    return 0;
}
funcClone_t *getCloneFunction(type_t t) //Lo clona y devuelve
{
    switch (t)
    {
    case TypeInt:
        return (funcClone_t *)&intClone;
        break;
    case TypeString:
        return (funcClone_t *)&strClone;
        break;
    case TypeCard:
        return (funcClone_t *)&cardClone;
        break;
    default:
        break;
    }
    return 0;
}
funcDelete_t *getDeleteFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcDelete_t *)&intDelete;
        break;
    case TypeString:
        return (funcDelete_t *)&strDelete;
        break;
    case TypeCard:
        return (funcDelete_t *)&cardDelete;
        break;
    default:
        break;
    }
    return 0;
}
funcPrint_t *getPrintFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcPrint_t *)&intPrint;
        break;
    case TypeString:
        return (funcPrint_t *)&strPrint;
        break;
    case TypeCard:
        return (funcPrint_t *)&cardPrint;
        break;
    default:
        break;
    }
    return 0;
}

/** Int **/

int32_t intCmp(int32_t *a, int32_t *b)
{
    if(*a > *b){
        return -1;
    }else if (*a < *b){
        return 1;
    }
    return 0;
    
}

void intDelete(int32_t *a)
{
    *a = 0;
    free(a);
}

void intPrint(int32_t *a, FILE *pFile)
{
    //stream: flujo de datos que permite la entrada y salida de info(se usan para manejar datos de dist fuentes)
    fprintf(pFile, "%d", *a);
}

int32_t *intClone(int32_t *a)
{
    int32_t *p = malloc(4);
    *p = *a;
    return p; //Asi retorna el puntero (si le pongo el * retorna el dato)
}

/** Lista **/

list_t *listNew(type_t t)
{
    list_t *l = malloc(sizeof(list_t));
    l->type = t;
    l->size = 0;
    l->first = NULL;
    l->last = NULL;
    return l;
}

uint8_t listGetSize(list_t *l)
{
    return l->size;
}

void *listGet(list_t *l, uint8_t i)
{
    if (i >= l->size){
        return 0;
    }
    listElem_t* n = l->first;
    for(uint8_t j = 0 ; j < i ; j++){
        n = n->next;
    }
    return n->data;
}

void listAddFirst(list_t *l, void *data)
{
    listElem_t *n = malloc(sizeof(listElem_t));
    n->prev = NULL;
    n->next = NULL;
    n->data = (getCloneFunction(l->type))(data);
    if (l->first == NULL){
        l->first = n;
        l->last = n;
    } else{
        n->next = l->first;
        (l->first)->prev = n;
        l->first = n;
    }
    (l->size)++;
}

void listAddLast(list_t *l, void *data)
{
    listElem_t *n = malloc(sizeof(listElem_t));
    n->prev = NULL;
    n->next = NULL;
    n->data = (getCloneFunction(l->type))(data);
    if (l->first == NULL){
        l->first = n;
        l->last = n;
    } else{
        (l->last)->next = n;
        n->prev = l->last;
        l->last = n;
    }
    (l->size)++;
}

list_t *listClone(list_t *l)
{
    list_t *listaNueva = listNew(l->type);
    listElem_t *n = l->first;
    //Mientras el nodo sea distinto de null
    while (n != NULL){
        //Insertamos el elemento en la listaClonada
        listAddLast(listaNueva, n->data);
        //Pasamos al siguiente nodo (nexteamos)
        n = n->next;
    }
    return listaNueva;
}

void *listRemove(list_t *l, uint8_t i)
{   
    // Si el índice está fuera de rango
    if (i >= l->size) {
        return 0;
    }

    listElem_t *tempN = NULL;
    void *data = NULL;
    
    // Si borra el primero
    if (i == 0) {
        tempN = l->first;
        data = (l->first)->data;
        l->first = (l->first)->next; // Pongo al siguiente como primero
        if (l->first != NULL) {
            (l->first)->prev = NULL;
        } else { // Si la lista tiene solo un nodo -> el primero es el último
            l->last = NULL;
        }
    } else if (i == ((l->size) - 1)) { // Si borra el último
        tempN = l->last;
        data = (l->last)->data;
        (l->last) = (l->last)->prev;
        if (l->last != NULL) {
            (l->last)->next = NULL;
        }else{
            l->first = NULL;
            l->last = NULL;
        }
    } else { // Si borra de la mitad  
        listElem_t *n = l->first;
        for (uint8_t j = 0; j < i - 1; j++) {
            n = n->next;
        }
        tempN = n->next;
        data = (n->next)->data;
        n->next = (n->next)->next;
        if (n->next != NULL) {
            (n->next)->prev = n;
        }
    }
    free(tempN);
    (l->size)--;
    return data;
}

void listSwap(list_t *l, uint8_t i, uint8_t j)
{
    if (i>= l->size || j>= l->size || i == j){
        return;        
    }
    
    void *datoI = NULL;
    void *datoJ = NULL;
    //*
    listElem_t *n = l->first;
    for (uint8_t m = 0; (m < (l->size)) || (datoI == NULL || datoJ == NULL); m++){
        if (m == i){
            datoI = n->data; //NO le ponemos * pq cuando desreferenciamos (le ponemos *) -> rompe (CON PUNTEROS VOID)
        } else if (m == j){
            datoJ = n->data;
        }
        n = n->next;
    }
    
    n = l->first; //Reiniciamos
    
    for (uint8_t m = 0; m < (l->size); m++){
        if (m == i){
            n->data = datoJ;
        } else if (m == j){
            n->data = datoI;
        }
        n = n->next;
    }
}

void listDelete(list_t *l)
{  
    listElem_t *n = l->first;
    while (n != NULL) {
        listElem_t *next = n->next;  // Guardamos el siguiente nodo
        getDeleteFunction(l->type)(n->data);  // Liberamos los datos del nodo actual
        free(n);  // Liberamos el nodo actual
        n = next;
    }
    free(l);
 }

void listPrint(list_t *l, FILE *pFile)
{
    listElem_t *n = l->first;
    fprintf(pFile, "[");
    while(n != NULL){
        listElem_t *next = n->next;
        getPrintFunction(l->type)(n->data, pFile);
        if (next != NULL){
            fprintf(pFile, ",");
        }
        n = next;
    }
    
    fprintf(pFile, "]");
}


/** Game **/

game_t *gameNew(void *cardDeck, funcGet_t *funcGet, funcRemove_t *funcRemove, funcSize_t *funcSize, funcPrint_t *funcPrint, funcDelete_t *funcDelete)
{
    game_t *game = (game_t *)malloc(sizeof(game_t));
    game->cardDeck = cardDeck;
    game->funcGet = funcGet;
    game->funcRemove = funcRemove;
    game->funcSize = funcSize;
    game->funcPrint = funcPrint;
    game->funcDelete = funcDelete;
    return game;
}
int gamePlayStep(game_t *g)
{
    int applied = 0;
    uint8_t i = 0;
    while (applied == 0 && i + 2 < g->funcSize(g->cardDeck))
    {
        card_t *a = g->funcGet(g->cardDeck, i);
        card_t *b = g->funcGet(g->cardDeck, i + 1);
        card_t *c = g->funcGet(g->cardDeck, i + 2);
        if (strCmp(cardGetSuit(a), cardGetSuit(c)) == 0 || intCmp(cardGetNumber(a), cardGetNumber(c)) == 0)
        {
            card_t *removed = g->funcRemove(g->cardDeck, i);
            cardAddStacked(b, removed);
            cardDelete(removed);
            applied = 1;
        }
        i++;
    }
    return applied;
}
uint8_t gameGetCardDeckSize(game_t *g)
{
    return g->funcSize(g->cardDeck);
}
void gameDelete(game_t *g)
{
    g->funcDelete(g->cardDeck);
    free(g);
}
void gamePrint(game_t *g, FILE *pFile)
{
    g->funcPrint(g->cardDeck, pFile);
}
