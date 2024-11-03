section .text
global strArrayNew
;global strArrayGetSize
;global strArrayGet
;global strArrayRemove
;global strArrayDelete
extern malloc
extern free

STR_ARRAY_OFF_SIZE EQU 0
STR_ARRAY_OFF_CAPACITY EQU 1
STR_ARRAY_OFF_DATA EQU 8
STR_ARRAY_TOTAL_SIZE EQU 16
SIZE_CHAR_ASTERISCO EQU 8

.strArrayNew:
    ;desalineada
    push rbp ; alineada
    mov rbp , rsp
    ;------------------------------------------------------
    ; LO HACEMOS GUARDANDO VARIABLES LOCALES EN LA PILA 
    
    sub rsp, 16 ; dejamos un espacio para dos variable local en la pila
    mov [rbp-8], rdi ; guardamos la capacidad (argumento 1) en el espacio que dejamos
    ; siempre en rbp-8 vamos a tener el valor del argumento 1 guardado (podemos acceder al arg1 desde esa direccion de la pila(stack))
    ;-------------------------------------------------------
    ;HASTA ACA LO UNICO QUE HICIMOS FUE GUARDAR EL REGISTRO(ARG CAPACITY) EN LA PILA

    ;en este punto la pila esta alineada -> puedo hacer el CALL
    mov rdi, STR_ARRAY_TOTAL_SIZE
    call malloc
    ; en rax tenemos el puntero al arrNuevo
    mov [rax+STR_ARRAY_OFF_CAPACITY], [rbp-8] ; le pasamos el argCapacity que esta en [rbp-8]
    mov byte [rax+STR_ARRAY_OFF_SIZE], 0 ; byte para q no se pasen 8

    mov [rbp-16], [rax]; nos guardamos el arrNuevo

    ;MULTIPLICAMOS  ->  sizeof(char*)*capacity
    mov rax , SIZE_CHAR_ASTERISCO 
    ; el capacity lo tenemos en [rbp-8]
    mul [rbp-8]

    ;Ahora el rax tenemos el resultado sizeof(char*)*capacity
    mov rdi, rax ; ahora cargamos en el rdi la multiplicacion para mandarsela al rax
    call malloc
    ;en el malloc tenemos el char*

    push r12
    mov r12 ,[rbp-16]
    mov [r12+STR_ARRAY_OFF_DATA], rax ; la linea 7
    
    mov rax, rbp-16; devolvemos el arrNuevo
    ; [rax] -> accede a la direccion de memoria que guarda rax
    ; rax -> lo que tiene adentro rax
    pop r12
    add rsp, 16
    pop rbp
    ret