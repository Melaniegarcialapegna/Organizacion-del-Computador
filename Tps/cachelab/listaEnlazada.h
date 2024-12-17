#ifndef _LISTA_H_
#define _LISTA_H_

typedef enum e_type {
	TypeNone = 0,
	TypeInt = 1,
	TypeString = 2,
} type_t;

char* strClone(char* a);
void strDelete(char* a);

typedef int32_t (funcCmp_t)(void*, void*);
typedef void* (funcClone_t)(void*);
typedef void (funcDelete_t)(void*);
typedef void (funcPrint_t)(void*, FILE* pFile);
funcDelete_t *getDeleteFunction(type_t t);
funcClone_t *getCloneFunction(type_t t);
funcPrint_t *getPrintFunction(type_t t);

typedef struct s_list {
	type_t   type;
	uint8_t  size;
	struct s_listElem* first;
	struct s_listElem* last;
} list_t;

typedef struct s_listElem {
	void* data;
	struct s_listElem* next;
	struct s_listElem* prev;
} listElem_t;

void intDelete(int32_t *a);
list_t* listNew(type_t t);
uint8_t  listGetSize(list_t* l);
void  listAddFirst(list_t* l, void* data);
void  listAddLast(list_t* l, void* data);
void* listGet(list_t* l, uint8_t i);
void* listRemove(list_t* l, uint8_t i);
void  listSwap(list_t* l, uint8_t i, uint8_t j);
void  listDelete(list_t* l);
list_t* listClone(list_t* l);
void  listPrint(list_t* l, FILE* pFile);
int listGetIndex(list_t *l, void* elem);


#endif