section .text
global strArrayNew
global strArrayGetSize
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

strArrayNew:
    ;desalineada
    push rbp ; alineada
    mov rbp , rsp
    
    
    push rbx ; desalineada 
    mov rbx, rdi ; arg capacity 
    sub rsp, 8 ;alineamos
    
    
    mov rdi, STR_ARRAY_TOTAL_SIZE
    call malloc

    ; en rax tenemos el puntero al arrNuevo

    mov [rax+STR_ARRAY_OFF_CAPACITY], bl ; le pasamos el arg Capacity que esta en bl , ->(bl pq usamos 1 byte del rbx para guardar un uint8 -> 8 bites = byte) 
    
    mov byte [rax+STR_ARRAY_OFF_SIZE], 0 ; le ponemos byte -> para q no se pasen 8 ceros (queremos -> 00000000)

    push r14 ; desalineada
    mov r14, rax; nos guardamos el arrNuevo

    ;MULTIPLICAMOS  ->  sizeof(char*)*capacity
    mov rax , SIZE_CHAR_ASTERISCO 
    ; el capacity lo tenemos en bl
    mul bl; multiplicar bl(capacity)*rax(size (char*)=8)

    sub rsp, 8 ; alineamos
    
    ;Ahora el rax tenemos el RESULTADO(MULTIPLICACION)-> sizeof(char*)*capacity
    mov rdi, rax ; ahora cargamos en el rdi la multiplicacion para mandarsela al malloc
    call malloc
    ;en el rax tenemos el PUNTERO char*

    mov [r14+STR_ARRAY_OFF_DATA], rax ; arrNuevo->data= malloc(sizeof(char*)*capacity);
    
    mov rax, r14; devolvemos el arrNuevo -> sin corchetes pq tenemos que devolver un puntero al arrNuevo
    ; [rax] -> accede a la direccion de memoria que guarda rax
    ; rax -> lo que tiene adentro rax

    add rsp, 8
    pop r14
    add rsp, 8
    pop rbx
    pop rbp
    ret


strArrayGetSize:
    ;desalineada
    push rbp ; alineada
    mov rbp , rsp
    
    ;rdi arg a
    push rbx
    mov rbx , [rdi+STR_ARRAY_TOTAL_SIZE]
    ;esta direccion guarda: sxxxxxxx
    shr rbx, 7; lo shifteamos porque esta al principio y queremos que este al final-> para desp agarrarlo con el bl

    ;Lo que devolvemos:
    mov al , bl ; queremos devolver un uint8->1 byte entonces usamos el (al)->(rax) y (bl)->rbx
    ;Adentro de bl estamos guardando el NUMERO no la direccion 
    pop rbx
    pop rbp
    ret