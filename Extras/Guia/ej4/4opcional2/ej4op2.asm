section .text ; sirve para decir que este es el codigo de nuestro programa
global destruirLista
extern free

destruirLista:
    ;desalineada
    push rbp ; alineada
    mov rbp , rsp
    
    push r12 ; desalineada
    mov r12 , rdi; arg cabeza
    
    push r14 ; para guardar el nodoSiguiente ; alineada
    

    .while:
        ; el QWORD es para cuando COMPARAMOS VALORES DE MEMORIA
        cmp r12 , 0
        je .finWhile
        mov r14 , [r12] ; guardamos el nodo siguiente (VER STRUCT) 
        mov rdi, r12 ; ponemos en el arg1 la direccion de la cabeza
        ;le pasamos sin [ ]-> pq le pasamos un PUNTERO al free

        call free

        mov r12 , r14 ; actualizamos la cabeza 
        jmp .while
        

    .finWhile:
    pop r14
    pop r12
    pop rbp
    ret