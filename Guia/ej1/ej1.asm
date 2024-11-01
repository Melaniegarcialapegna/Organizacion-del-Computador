

;Declaramos funciones
global cesar ; exportamos la fun asm
extern chr 
extern ord


cesar:
    push rbp ; DESPUES DE ESTE PUSH LA PILA ESTA ALINAEDA
    mov rbp, rsp

    push r14 ; preservamos el valor de r14-> no volatil (checkear que no perdemos el valor lo guardamos en la pila)

    ;DESPUES DE ESTE PUSH SE VOLVIO A DESALINEAR

    mov r14,0 ; inicializamos el contador
    push r12 ; ponemos en la pila lo q antes tenia el r12
    mov r12, rdi ; guardamos el arg1
    push r15
    mov r15, rsi

    sub rsp, 8; para alinear la pila


    .while: ; definimos etiqueta while

    mov rdi, [r12+r14] ; ponemos r12 que corresponde a la primera letra de la palabra q nos pasan + el r14 que es el contador q nos va a permitir ir letra por letra (lina22) -> guardamos el valor

    call ord ; -> me puede cambiar el rdi pq es volatil!!1 , pero NO el r12/r14 pq son NO volatiles

    add rax, [rsi] ; linea 22 (Le sumamos el valor del segundo elemento a RAX que es el resultado de ord)

    ;momento modulo (linea 23) -> chequear NOTION
    mov eax, [rax]
    mov edx, 26

    div ebx; aca tenemos el resto xd

    ;finish

    ;en r13 tenemos el indice guardado
    push r13 ; para el indice que lo podemos perder sino
    mov r13, rax ; nos guardamos el rax en r13

    sub rsp, 8; para alinear la pila

    mov rdi, rax; Movemos la suma del indice(22) -> que esta en rax a RDI, que es el primer argumento para hacer el acall a CHR

    call chr

    ; en rax tenemos el resultado de la fun de la linea (24)
    mov r12+[r14] , rax ; r12+r14 -> palabra+indice

    inc r14; incrementamos el contador
    cmp [r12+r14] , 0 ; veo que no estoy en el 0
    jne .while ; si el [r12+r14] NO contiene un 0 sigue en loop

    ; AVERIGUAR COMO RESERVAR MEMORIA EN ASM PARA DEVOLVER !!!!


    ; restauramos los valores originales

    add rsp, 8; desalineamos lo q alineamos antes con el SUB (linea 48)

    pop r13

    add rsp, 8; desalineamos lo q alineamos antes con el SUB (linea 48)

    pop r15

    pop r12

    pop r14

    pop rbp
    ret