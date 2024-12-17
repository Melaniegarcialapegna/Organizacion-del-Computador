section .text
global agregarAdelante_asm
extern malloc

agregarAdelante_asm:
    push rbp
    mov rbp, rsp
    push r12
    push r14

    mov r12, rdi     ; r12 = valor (primer argumento)
    mov r14, rsi     ; r14 = siguiente (segundo argumento)

    ; Llamar a malloc para reservar espacio para el nodo
    mov rdi, 16      ; 16 bytes para un nodo
    call malloc
    ; rax ahora tiene el puntero al nuevo nodo

    ; Almacena el siguiente nodo
    mov [rax], r14   ; [rax] = siguiente

    ; Almacena el valor en el nuevo nodo
    mov [rax + 8], r12 ; [rax + 8] = valor

    ; Retornar el puntero al nuevo nodo
    pop r14
    pop r12
    pop rbp
    ret