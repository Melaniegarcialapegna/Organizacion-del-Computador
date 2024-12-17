
section .data
TEXTO: db "NULL", 0; db es para declarar byte por by
CORCHETE_ABIERTO: db "[", 0
COMA : db ",", 0
CORCHETE_CERRADO: db "]", 0
LLAVE_ABIERTA: db "{" , 0
GUION: db "-", 0
LLAVE_CERRADA: db "}" , 0

global strClone
global strPrint
global strCmp
global strLen
global strDelete

global arrayNew
global arrayDelete
global arrayPrint
global arrayGetSize
global arrayAddLast
global arrayGet
global arrayRemove
global arraySwap

global cardCmp
global cardClone
global cardAddStacked
global cardDelete
global cardGetSuit
global cardGetNumber
global cardGetStacked
global cardPrint
global cardNew
extern malloc
extern fprintf
extern free
extern getCompareFunction
extern getCloneFunction
extern getDeleteFunction
extern getPrintFunction
extern listNew
extern listAddFirst
extern listDelete
extern listPrint
extern listClone
extern intCmp
section .text

TAM_CHAR_ASTERISCO EQU 8

ARR_OFF_TYPE EQU 0
ARR_OFF_SIZE EQU 4
ARR_OFF_CAPACITY EQU 5
ARR_OFF_DATA EQU 8
ARR_STRUCT_TAM EQU 16
TAM_PUNTERO EQU 8


CARD_OFF_SUIT EQU 0
CARD_OFF_NUMBER EQU 8
CARD_OFF_STACKED EQU 16
CARD_STRUCT_TAM EQU 24


; ** String **
;char* strClone(char* a);
strClone:
;desalineada
    push rbp
    mov rbp,rsp

    push r12; metemos el valor anterior de r12 a la pila
    mov r12 , rdi; r12 : arg : char a*
    ; char* cadena = malloc(20);

    push rbx ; des
    mov rbx, 0; rbx es el contador / al final va a tener la cantidad de bytes o letra
    .while:
        cmp byte [r12+rbx], 0
        je .finwhile
        inc rbx
        jmp .while
    
    ; en rbx el len del char*
    .finwhile:
        inc rbx
        mov edi , ebx; primer argumento del malloc el mas 1 es por el /0
        call malloc
        ; en rax tenemos un puntero al espacio que guardara la palabra clonada
    
    mov rdx, 0
    mov rcx , 0
    .whiledos:
        cmp rbx , rdx
        je .fin
        mov byte cl , [r12+rdx] ; cl es el 1byte de rcx
        mov byte [rax+rdx], cl
        inc rdx
        jmp .whiledos

    .fin:
    dec rbx
    mov byte [rax+rbx], 0; cadena[largoCadena] = \0
    
    pop rbx
    pop r12
    pop rbp
    ret

;void strPrint(char* a, FILE* pFile)
strPrint:
    push rbp ; alineada
    mov rbp,rsp
    
    push r12 ;guardamos r12 a la piladesalineada
    push r14 ;guardamos r14 ralineada

    mov r12, rdi; en r12 arg char*
    mov r14, rsi; en r14 queda el arg2 (file)

    ;[r12] -> apunta al primer caracter
    mov rdi, r14; le pasamos el file como primer arg
    mov rsi, 0 ; limpiamos el rsi
    cmp byte [r12], 0 ;comparamos la cadena para ver si esta vacia
    je .vacio
    
    ;fprintf recibe 
    ;2arg->str
    ;1arg-> archivo 
    
    mov rsi, r12
    jmp .fin

    .vacio:
        mov rsi, TEXTO
    
    .fin:
    call fprintf
    
    pop r14
    pop r12
    pop rbp
    ret


;uint32_t strLen(char* a);
strLen:
    push rbp
    mov rbp,rsp

    push r12; metemos el valor anterior de r12 a la pila
    mov r12 , rdi; r12 : arg : char a*
    ; char* cadena = malloc(20);

    push rbx ; des
    mov rbx, 0; rbx es el contador / al final va a tener la cantidad de bytes o letra
    .while:
        cmp byte [r12+rbx], 0
        je .finwhile
        inc rbx
        jmp .while
        
    .finwhile:
    mov rax, 0 ; limpiamos el registro
    mov eax , ebx
    
    pop rbx
    pop r12
    pop rbp
    ret

strCmp:
    ; Prologue
    push rbp
    mov rbp, rsp

    push r12
    push r14
    push rbx
    push r15

    mov r12, rdi ; guardamos en r12 el 1er arg -> primera palabra
    mov r14, rsi ; guardamos en r14 el 2do arg -> segunda palabra

    ;en el rdi ya tenemos el char* a
    call strLen
    mov ebx, eax ; rbx = len(primera palabra)

    mov rdi, r14 ; movemos la palabra 2 a rdi (primer argumento del strLen)
    call strLen 
    mov r15d, eax ; r15 = len(segunda palabra)

    mov r10, 0 ; contador

    .while:
        cmp dword ebx, 0
        je .checkearUnoOCero

        cmp dword r15d, 0
        je .devolverMenosUno

        mov byte r11b, [r12+r10]
        mov byte r8b, [r14+r10]
        cmp r11b, r8b
        jne .compararLetras

        inc r10
        dec rbx
        dec r15
        jmp .while

    .checkearUnoOCero:
        cmp dword r15d, 0
        je .devolverCero
        jne .devolverUno

    .compararLetras:
        jg .devolverMenosUno
        jl .devolverUno

    .devolverUno:
        mov dword eax, 1
        jmp .fin

    .devolverMenosUno:
        mov dword eax, -1
        jmp .fin

    .devolverCero:
        mov dword eax, 0
        jmp .fin

    .fin:
    pop r15
    pop rbx
    pop r14
    pop r12
    pop rbp
    ret


; 
;void strDelete(char* a);
strDelete:
    push rbp
    mov rbp, rsp
    
    call free

    pop rbp
    ret
; ** Array **

; uint8_t arrayGetSize(array_t* a)
arrayGetSize:
    push rbp
    mov rbp,rsp
    push rbx

    mov rbx, 0
    mov byte bl, [rdi + ARR_OFF_SIZE]
    mov rax, 0
    mov al , bl

    pop rbx
    pop rbp
    ret

; void arrayAddLast(array_t* a, void* data)
arrayAddLast:
    push rbp
    mov rbp,rsp
    push r12
    push r14
    push r15
    push rbx

    mov r12 , rdi ; r12 : arreglo
    mov r14 , rsi ; r14 : dato

    mov byte r15b ,  [r12 + ARR_OFF_SIZE]
    cmp [r12 + ARR_OFF_CAPACITY], r15b
    je .fin
    

    ;aca hacemos el void** data
    mov DWORD edi, [r12+ARR_OFF_TYPE]
    call getCloneFunction ;en rax tenemos la funcion para clonar un dato
    mov rdi, r14
    call rax 
    mov rbx, rax ;en rax vamos a tener el puntero al dato clonado

    mov r11, 0 ; contador
    .while:
        cmp byte r11b, [r12+ARR_OFF_SIZE] ; size cuenta desde 1 (como len)
        je .finwhile
        inc r11b
        jmp .while

    .finwhile:
        mov rax, TAM_PUNTERO ; 8
        mul r11b
        mov r9, [r12+ARR_OFF_DATA] ;mueve a r9 el puntero al primer dato del arreglo
        mov [r9+rax], rbx
        
        mov byte r10b, [r12+ARR_OFF_SIZE]
        inc r10b
        mov [r12+ARR_OFF_SIZE], r10b

    .fin:
    pop rbx
    pop r15
    pop r14
    pop r12
    pop rbp
    ret

; void* arrayGet(array_t* a, uint8_t i)
arrayGet:
    push rbp 
    mov rbp , rsp
    
    push r12
    push r14
    push r15
    
    mov r12, rdi
    mov r14, rsi
    ;rdi a
    ;rsi i
    
    cmp byte r14b, [r12+ARR_OFF_SIZE] ; es 1byte de rsi
    jge .finLimite ; 

    cmp byte r14b, 0
    jl .finLimite

    mov rax, TAM_PUNTERO  
    imul rax, rsi   
    add rax, [r12+ARR_OFF_DATA]  
    mov rax, [rax]; r14 : a[I] -> probar con [rax]
    jmp .fin
    
    .finLimite:
    mov rax, 0

    .fin:
    pop r15
    pop r14
    pop r12
    pop rbp
    ret

; array_t* arrayNew(type_t t, uint8_t capacity)
arrayNew:
    push rbp 
    mov rbp , rsp
    
    push r12
    push rbx 
    mov rbx, rsi 
    
    mov r12, rdi ; type
    
    mov rdi, ARR_STRUCT_TAM
    call malloc

    ; en rax tenemos el puntero al arrNuevo

    mov [rax+ARR_OFF_CAPACITY], bl ; le pasamos el arg Capacity que esta en bl , ->(bl pq usamos 1 byte del rbx para guardar un uint8 -> 8 bites = byte) 
    
    mov byte [rax+ARR_OFF_SIZE], 0 ; le ponemos byte -> para q no se pasen 8 ceros (queremos -> 00000000)

    push r14
    mov r14, rax; nos guardamos el arrNuevo

    ;MULTIPLICAMOS  ->  sizeof(char*)*capacity
    mov rax , TAM_CHAR_ASTERISCO
    ; el capacity lo tenemos en bl
    mul bl; multiplicar bl(capacity)*rax(size (char*)=8)

    sub rsp, 8 ; alineamos
    
    ;Ahora el rax tenemos el RESULTADO(MULTIPLICACION)-> sizeof(char*)*capacity
    mov rdi, rax ; ahora cargamos en el rdi la multiplicacion para mandarsela al malloc
    call malloc
    ;en el rax tenemos el PUNTERO char*

    mov [r14+ARR_OFF_TYPE], r12d
    mov [r14+ARR_OFF_DATA], rax ; arrNuevo->data= malloc(sizeof(char*)*capacity);
    
    mov rax, r14; devolvemos el arrNuevo -> sin corchetes pq tenemos que devolver un puntero al arrNuevo

    add rsp, 8
    pop r14
    pop rbx
    pop r12
    pop rbp
    ret

; void* arrayRemove(array_t* a, uint8_t i)
arrayRemove:
    ;desalineada
    push rbp
    mov rbp, rsp
    push r12
    push r14
    push r15

    ;rdi a (arreglo)
    ;rsi i (indice)
    ;RAX -> data 

    mov r12, rdi ; r12: arreglo
    mov r14, rsi ; r15 : i

    ;Vemos que indices i y j esten dentro en rango
    cmp byte r14b, [r12+ARR_OFF_SIZE]
    jge .finInvalido 
    ; Queremos :  [rdi+ARR_OFF_DATA]+rsi*TAM_PUNTERO

    mov rax, TAM_PUNTERO  
    imul rax, rsi   
    add rax, [r12+ARR_OFF_DATA]  
    mov r15, [rax]; r14 : a[I] -> probar con [rax]

    mov byte bl, [r12+ARR_OFF_SIZE]
    dec bl
    .while:
        cmp r14b, bl
        je .finWhile
        
        mov rax, TAM_PUNTERO  
        imul rax, r14   
        add rax, [r12+ARR_OFF_DATA]  
        mov r11, rax ; r11 -> puntero a arreglo[i]

        mov rcx, r11
        add rcx, TAM_PUNTERO ; rcx -> r11+8
        mov r8, rcx ; puntero al siguiente

        mov r9, [r8]; nos guardamos en r9 el valor del siguiente 
        mov [r11], r9
        ;)
        
        inc r14
        jmp .while


    .finWhile:
        mov byte [r12+ARR_OFF_SIZE], bl
        mov rax, r15
        jmp .fin
    
    .finInvalido:
    mov rax, 0

    .fin:
    pop r15
    pop r14
    pop r12
    pop rbp
    ret
    
; void arraySwap(array_t* a, uint8_t i, uint8_t j)
arraySwap:
    push rbp
    mov rbp, rsp

    push r13
    push r14
    push r15

    ;Vemos que indices i y j esten dentro en rango
    ;Ponemos el tamaño del arr en rax
    cmp byte sil, [rdi+ARR_OFF_SIZE]
    jge .fin

    cmp byte dl, [rdi+ARR_OFF_SIZE]
    jge .fin

    mov r13, [rdi+ARR_OFF_DATA] 

    ;Calculamos a[i]
    mov rax, TAM_PUNTERO  
    imul rax, rsi   
    add rax, r13  
    mov r14, rax; r14 : a[I]
    ; Calculamos a[j]
    mov rax, TAM_PUNTERO
    imul rax, rdx ; 
    add rax, r13  
    mov r15, rax; R15 : a[j] 

    ;Momento SWAP
    mov eax, [r14]  
    mov ebx, [r15]   
    mov [r14], ebx ;ponemos de a[j] en a[i]
    mov [r15], eax ;ponemos a[i] en a[j]  

    .fin:
    pop r15
    pop r14
    pop r13
    pop rbp
    ret


; void arrayDelete(array_t* a) {
arrayDelete:
    push rbp
    mov rbp, rsp
    push r12
    push r14
    push r15
    push r13

    mov r12, rdi ; r12 : array
    mov r15 , [r12+ARR_OFF_DATA] ; aca tenemos la data
    
    mov dword edi, [r12+ARR_OFF_TYPE]
    call getDeleteFunction
    mov r13 , rax ; en r13 tenemos la funcion para eliminar ese tipo de dato
    
    
    cmp r12 , 0 ; chequeamos que el a no sea nulo
    je .fin

    mov r14 , 0; contador
    .while:
        cmp byte r14b , [r12+ARR_OFF_SIZE]
        jge .finWhile ; 

        mov rdi , [r15+r14*TAM_PUNTERO] ;-> (contador*8) : para pasar al prox dato del arr
        call r13

        inc r14
        jmp .while

    .finWhile:
    mov rdi , r15
    call free

    mov rdi , r12
    call free

    .fin:
    pop r13
    pop r15
    pop r14
    pop r12
    pop rbp
    ret

;void arrayPrint(array_t* a, FILE* pFile)
arrayPrint:
    push rbp
    mov rbp, rsp

    push r12
    push r14
    push r15
    push r13
    push rbx
    sub rsp , 8

    mov r12, rdi
    mov r14, rsi
    mov r13 , [r12+ARR_OFF_DATA]

    ;fprintf recibe 
    ;1arg-> archivo
    ;2arg->str

    ;print para el type recibe 
    ;1arg-> str
    ;2arg->archivo

    mov rdi, r14
    mov rsi, 0
    mov rsi, CORCHETE_ABIERTO ; 91 = [   en ASCII
    call fprintf


    cmp byte [r12+ARR_OFF_SIZE], 0
    je .fin

    mov rdi, 0 
    mov dword edi, [r12+ARR_OFF_TYPE]
    call getPrintFunction ;rax -> funcion
    mov rbx, rax

    mov r15, 0
    mov byte r12b, [r12+ARR_OFF_SIZE] ; en r12b tenemos el tamaño
    dec r12b
    .while:
        cmp byte r15b, r12b
        je .finWhile

        mov rax, TAM_PUNTERO
        mul r15 ; rax -> i8

        add rax, r13 ;direccion del primero + i8
        mov rdi, [rax]
        mov rsi, r14
        call rbx ; rbx es la funcion de print para un tipo de dato 

        mov rdi, r14
        mov rsi, 0
        mov rsi, COMA ; 44 = ,   en ASCII
        call fprintf

        inc r15
        jmp .while


    .finWhile:
    mov rax, TAM_PUNTERO
    mul r15 ; rax -> i*8
    add rax, r13 ;direccion del primero + i*8
    mov rdi, [rax]  ; rax: arreglo[i]
    mov rsi, r14 ; r14: archivo 
    call rbx ; rbx es la funcion de print para un tipo de dato 

    .fin:
    mov rdi, r14
    mov rsi, 0
    mov rsi, CORCHETE_CERRADO ; 93 = ]   en ASCII
    call fprintf

    add rsp ,8
    pop rbx
    pop r13
    pop r15
    pop r14
    pop r12
    pop rbp
    ret



; ** Card **

; card_t* cardNew(char* suit, int32_t* number)
cardNew:
    push rbp
    mov rbp, rsp
    push r14
    push r12
    push r13
    push r15
    push rbx
    sub rsp , 8

    mov r14 , rdi ; r14 : suit
    mov r12 , rsi ; r12 : number

    mov rdi, 0
    mov rdi , CARD_STRUCT_TAM
    call malloc
    mov r15 , rax ; r15 tenemos e puntero a la carta

    mov rdi ,0
    mov rdi, 2
    call getCloneFunction ; rax -> puntero a funcion clonadora :)
    mov rdi, r14
    call rax
    mov r13, rax ; r13 -> suit clonado!!!
    
    mov rdi, 0
    mov rdi, 1
    call getCloneFunction
    mov rdi, r12
    call rax
    mov rbx, rax ; r15 -> number clonado!!

    mov rdi, 0
    mov rdi, 3
    call listNew ;rax -> puntero a la lista

    mov [r15+CARD_OFF_SUIT] , r13
    mov [r15+CARD_OFF_NUMBER] , rbx
    mov [r15+CARD_OFF_STACKED] , rax

    mov rax, r15

    add rsp, 8
    pop rbx
    pop r15
    pop r13
    pop r12
    pop r14
    pop rbp
    ret

;char* cardGetSuit(card_t* c)
cardGetSuit:
    push rbp
    mov rbp, rsp 

    mov rax, [rdi + CARD_OFF_SUIT]

    pop rbp
    ret

;int32_t* cardGetNumber(card_t* c)
cardGetNumber:
    push rbp
    mov rbp, rsp 

    mov rax, [rdi + CARD_OFF_NUMBER]

    pop rbp
    ret

;list_t* cardGetStacked(card_t* c)
cardGetStacked:
    push rbp
    mov rbp, rsp 

    mov rax, [rdi + CARD_OFF_STACKED]

    pop rbp
    ret


;void cardPrint(card_t* c, FILE* pFile)
cardPrint:
    push rbp
    mov rbp, rsp
    push r14
    push r12

    mov r12, rdi ; rdi : c
    mov r14 , rsi ; rsi : archivo
    
    ;IMPRIMIMOS {
    mov rdi, r14
    mov rsi, 0
    mov rsi, LLAVE_ABIERTA
    call fprintf

    ;IMPRIMIMOS SUIT
    mov rdi, 2
    call getPrintFunction
    mov rdi, 0 ;limpio
    mov rdi, [r12+CARD_OFF_SUIT]
    mov rsi, r14
    call rax
    
    ;IMPRIMIMOS -
    mov rdi, r14
    mov rsi, GUION
    call fprintf

    ; IMPRIMIMOS NUMBER
    mov rdi, 1
    call getPrintFunction
    mov rdi, 0
    mov rdi, [r12+CARD_OFF_NUMBER]
    mov rsi, r14
    call rax
    
    ;IMPRIMIMOS -
    mov rdi, r14
    mov rsi, GUION
    call fprintf
    
    ;IMPRIMIMOS LA LISTA
    mov rdi, [r12+CARD_OFF_STACKED]
    mov rsi, r14
    call listPrint

    ;IMPRIMIMOS }
    mov rdi, r14
    mov rsi, 0
    mov rsi, LLAVE_CERRADA
    call fprintf
    
    pop r12
    pop r14
    pop rbp
    ret


;int32_t cardCmp(card_t* a, card_t* b)
cardCmp:
    push rbp
    mov rbp, rsp
    push r12
    push r14

    mov r12, rdi ; r12 : cartaA
    mov r14 ,rsi ; r14 : cartaB


    mov rdi, [r12+CARD_OFF_SUIT]
    mov rsi, [r14+CARD_OFF_SUIT]
    call strCmp
    cmp dword eax, 0
    jne .fin
    
    .compararNumero:
        mov rdi, [r12+CARD_OFF_NUMBER]
        mov rsi, [r14+CARD_OFF_NUMBER]
        call intCmp
        
    .fin:
    pop r14
    pop r12
    pop rbp
    ret

;void cardAddStacked(card_t* c, card_t* card)
cardAddStacked:
    push rbp
    mov rbp, rsp
    push r14
    push r12
    push r15
    sub rsp, 8

    mov r14 , rdi ; r14 : c
    mov r12 , rsi ; r12 : card


    mov rdi, [r14+CARD_OFF_STACKED]
    mov rsi, r12
    call listAddFirst ; agregamos el clon al principio de la pila
    
    add rsp, 8
    pop r15
    pop r12
    pop r14
    pop rbp
    ret

;card_t* cardClone(card_t* c)
cardClone:
    push rbp
    mov rbp, rsp
    push r12
    push r14

    mov r12, rdi


    ;CREAMOS UNA CARTA NUEVA
    mov rdi , CARD_STRUCT_TAM
    call malloc
    mov r14 , rax


    ; CLONAMOS EL SUIT
    mov rdi, 2
    call getCloneFunction
    mov rdi ,[r12+CARD_OFF_SUIT]
    call rax
    mov [r14+CARD_OFF_SUIT] , rax

    ; CLONAMOS EL NUMBER
    mov rdi, 1
    call getCloneFunction
    mov rdi, [r12+CARD_OFF_NUMBER]
    call rax
    mov [r14+CARD_OFF_NUMBER] , rax

    ;CLONAMOS LA LISTA
    mov rdi, [r12+CARD_OFF_STACKED]
    call listClone
    mov [r14+CARD_OFF_STACKED] , rax
    
    mov rax , r14

    pop r14
    pop r12
    pop rbp
    ret

;void cardDelete(card_t* c)
cardDelete:
    push rbp
    mov rbp, rsp
    push r14
    sub rsp, 8

    mov r14 , rdi ; r14  : carta

    mov rdi, 0
    mov rdi, 1
    call getDeleteFunction
    mov rdi, [r14+CARD_OFF_NUMBER]
    call rax ; aca adentro hace el free 
    
    mov rdi, 2
    call getDeleteFunction
    mov rdi, [r14+CARD_OFF_SUIT]
    call rax 

    mov rdi , [r14+CARD_OFF_STACKED]
    call listDelete
    
    mov rdi, r14
    call free

    add rsp ,8
    pop r14
    pop rbp
    ret

