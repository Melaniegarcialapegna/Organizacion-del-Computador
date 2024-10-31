extern rand

devolverStruct:
    push rbp
    mov rbp, rsp
    
    push r12
    push r14
    
    mov r12, rdi    ; puntero al arreglo de estructuras
    mov r14, rsi    ; longitud del arreglo
    
    call rand       ; llama a rand, resultado en rax
    
    ; Calcula el módulo para obtener un índice aleatorio
    xor rdx, rdx    ; limpia rdx antes de la división
    mov rbx, r14    ; mueve la longitud del arreglo a rbx
    mov rax, rax    ; valor aleatorio en rax
    div rbx         ; divide rax entre rbx, resultado en rax y resto en rdx
    ; rdx ahora contiene el índice aleatorio

    ; Acceder al elemento aleatorio
    mov rax, [r12 + rdx * 32] ; tamaño de la estructura es 32 bytes

    pop r14
    pop r12
    pop rbp

    ret
