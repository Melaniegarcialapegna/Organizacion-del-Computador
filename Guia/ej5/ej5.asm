section .text
global strArrayNew
global strArrayGetSize
global strArrayGet
global strArrayRemove
global strArrayDelete
extern malloc
extern free

STR_ARRAY_OFF_SIZE EQU 0
STR_ARRAY_OFF_CAPACITY EQU 1
STR_ARRAY_OFF_DATA EQU 8
STR_ARRAY_TOTAL_SIZE EQU 16

.strArrayNew:
    ;desalineada
    push rbp ; alineada
    mov rbp , rsp

    ; LO HACEMOS GUARDANDO VARIABLES LOCALES EN LA PILA 
    
    sub rsp, 8 ; dejamos un espacio para una variable local en la pila
    mov [rbp-8], rdi ; guardamos la capacidad (argumento 1) en el espacio que dejamos
    ; siempre en rbp-8 vamos a tener el valor del argumento 1 guardado (podemos acceder al arg1 desde esa direccion de la pila(stack))
    
    ;HASTA ACA LO UNICO QUE HICIMOS FUE GUARDAR EL REGISTRO(ARG CAPACITY) EN LA PILA

    mov rdi, 

    mov rdi, 

    pop rbp
    ret