section .data

global strClone
global strDelete
extern malloc
extern free
section .text

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

; 
;void strDelete(char* a);
strDelete:
    push rbp
    mov rbp, rsp
    
    call free

    pop rbp
    ret
; ** Array **