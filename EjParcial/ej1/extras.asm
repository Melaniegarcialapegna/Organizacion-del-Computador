

;VERSION MEJORADA (ponele-> usa malloc)

global cesar
extern chr
extern ord
extern malloc
extern memcpy

cesar:
    push rbp
    mov rbp, rsp

    ; Reservamos memoria para la cadena de resultado
    mov rdi, rsi                ; tamaño x 1 para cadena de salida
    call malloc
    mov rdi, rax                ; resultado será el puntero a la memoria reservada
    mov r12, rdi                ; guardamos el puntero de resultado

    mov r14, 0                  ; contador
    mov r15, rsi                ; guardamos x

    .while:
        movzx rdi, byte [rdi + r14] ; cargamos el caracter
        call ord                     ; llamamos a ord
        add rax, r15                 ; sumamos x
        xor rdx, rdx                 ; limpiamos rdx para la división
        mov rbx, 26                  ; divisor
        div rbx                      ; rax = (ord(c) + x) / 26, rdx = (ord(c) + x) % 26
        add rax, 65                  ; convertir a ASCII (A = 65)
        mov [r12 + r14], al          ; almacenamos el resultado en la cadena

        inc r14                      ; avanzamos al siguiente carácter
        cmp byte [rdi + r14], 0     ; comprobamos el final de la cadena
        jne .while                   ; si no es nulo, seguimos

    mov byte [r12 + r14], 0        ; añadimos el nulo al final

    mov rax, r12                    ; devolvemos el puntero al resultado
    pop rbp
    ret


;Otra forma mas ordenada

;Declaramos funciones
global cesar ; exportamos la fun asm
extern chr 
extern ord

cesar:
    push rbp ; DESPUES DE ESTE PUSH LA PILA ESTA ALINEADA
    mov rbp, rsp

    push r14 ; preservamos el valor de r14 (no volátil)
    push r12 ; preservamos r12
    push r15 ; preservamos r15

    mov r14, 0 ; inicializamos el contador
    mov r12, rdi ; guardamos el arg1 (cadena de entrada)
    mov r15, rsi ; guardamos el desplazamiento x

    .while: ; definimos etiqueta while

    mov rdi, [r12 + r14] ; cargamos la letra de la cadena
    call ord ; llamamos a ord, el resultado estará en rax

    add rax, r15 ; sumamos el desplazamiento x

    ; Momento módulo
    xor rdx, rdx ; limpiamos rdx
    mov rbx, 26 ; divisor
    div rbx ; ahora rax tiene el cociente y rdx el resto

    ; Convertimos de nuevo a ASCII (A = 65)
    add rax, 65 

    ; Guardamos el resultado en la cadena de salida
    mov [r12 + r14], al ; guardamos el resultado

    inc r14 ; incrementamos el contador
    cmp byte [r12 + r14], 0 ; comprobamos el final de la cadena
    jne .while ; si no es nulo, seguimos

    mov byte [r12 + r14], 0 ; añadimos el nulo al final

    ; Restauramos los valores originales
    pop r15
    pop r12
    pop r14

    pop rbp
    ret
