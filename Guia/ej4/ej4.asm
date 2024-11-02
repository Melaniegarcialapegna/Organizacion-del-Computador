section .text
global agregarAdelante_asm
extern malloc

agregarAdelante_asm:
    ;siempre desalineada
    push rbp ; alineamos
    mov rbp, rsp
    push r12 ; desalineada
    ;mov r12, 0 ; solo queremos los ultimos 4 bytes pq (int32)-
    mov r12, rdi 
    ;AL FINAL NOOOOOOOO guardamos en r12 en primer argumento (valor) -> ponemos r12d pq solo nos interesan los ult4bytes mas significat.
    push r14  ; alineada
    mov r14, rsi ; guardamos en r14 en primer argumento (valor)

    ;rdi -> lo q va a recibir el malloc
    mov rdi, 16; ; 16bytes por lo explicado en ej4.c
    call malloc
    ;en rax tenemos un puntero a un NODO -> al byte 0 (primero) de un NODO

    ;Struct:
    ;En los primeros 8 bytes tenemos que poner el valor del siguiente
    ;En los siguientes 4 bytes el valor de este
    ;En los siguientes 4 bytes padding
    
    ;Obs-> Las partes bajas de los DATOS se guardan en las posiciones bajas de MEMORIA

    mov [rax], r14 ; le pasamos el nodo   
    ;shl r12, 32 ; shifteamos 4bytes a la izq
    mov [rax+8], r12 ;rax+8 -> para ir a la prox pos (MEMORIA ES DIRECCIONABLE A NIVEL BYTE)-> para bajar + 8 pq alineada a 8
    
    ;el RAX ya es el puntero al nodo (al primer byte) , asi q ya se esta dev eso
    pop r14
    pop r12
    pop rbp
    ret

    