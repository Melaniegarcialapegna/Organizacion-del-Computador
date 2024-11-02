section .text
global valorEn
extern malloc

valorEn:
    push rbp
    mov rbp , rsp

    push r12
    mov r12, rdi ; arg indice

    push r14
    mov r14 , rsi ; arg cabeza -> puntero a primer nodo

    ; [reg] -> agarrando la posicion de memoria que esta guardada dentro del registro (puntero)
    ; reg -> agarra el valor/ lo q tiene el registro dentro como tal
    mov rax, r12 ; el indice * 16 -> sig struct/nodo

    push r15
    mov r15, 16
    ;para multiplicar -> rax hay q poner el r12
    mul r15

    mov r14, [r14+rax] ; sumamos a r14 q es la cabeza para llegar hasta el nodo q queramos // LO SOBRESCRIBIMOS PQ NO NOS INTERESA GUARDAR LO DE ANTES - SE PODRIA PONER EN OTRO REG (ES LO MISMO)
    mov rax, [r14+8] ; por lo de abajo
    ;ssssssss
    ;vvvvpppp - ppppvvvv

    pop r15
    pop r14
    pop r12
    pop rbp
    ret