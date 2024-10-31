extern rand

devolverStruct:
    ;entra desalineado
    push rbp ;si o si primero :D ;alineamos
    mov rbp, rip
    push r12
    push r14 
    mov r12, rdi ; el arr en si 
    mov r14, rsi ; 2do arr es la cant de stucts q tiene el arr

    call rand
    ;sacamos modulo
    mov eax, [rax]
    mov edx, [r14]; dividimos sobre el valor de r14

    div ebx; aca tenemos el resto -> modulo 
    ;finish
    mov rax, [r12+(32*ebx)]; arr con structs + 32(lo q ocupa en bytes c/u)*ebx que es el num random de a hasta cual queremos ir

    pop r14

    pop r12
    
    pop rbp

    ret


