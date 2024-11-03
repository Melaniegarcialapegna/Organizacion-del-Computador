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
    mov [rbp-8], rdi ; guardamos la capacidad en el espacio que dejamos

    

    mov rdi, 

    pop rbp
    ret