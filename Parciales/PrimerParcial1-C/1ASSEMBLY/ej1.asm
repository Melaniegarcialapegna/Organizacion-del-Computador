.section text
global arrayMap
extern malloc

ARRAY_T_OFF_TYPE EQU 0
ARRAY_T_OFF_SIZE EQU 4
ARRAY_T_OFF_CAPACITY EQU 5
ARRAY_T_OFF_DATA EQU 8
ARRAY_T_TAM_TOTAL EQU 16

SIZE_VOID_ASTERISCO EQU 8 ; este es para el malloc

arrayMap:
	push rbp 
    mov rbp , rsp
	
    push r12
    push r14
    push r15
    push r13

    mov r12 ,rdi ; r12 : array_t
    mov r14, rsi ; r14 : funcion a aplicar

    mov rdi, ARRAY_T_TAM_TOTAL
    call malloc ;rax : puntero nuevoArr
    
    ;podemos usar volatiles siempre y cuando los terminemos de usar antes de hacer otro call
    mov r15 ,rax ; r15 : nuevoArreglo
    mov DWORD r8d, [r12] ; r8: array->type
    mov BYTE cl, [r12+ARRAY_T_OFF_SIZE] ; r9 array->size
    mov BYTE dl, [r12+ARRAY_T_OFF_CAPACITY] ;r10 array-> capacity

    ;inicializamos valores del nuevoArr (linea 6-8)
    mov DWORD [r15] , r8d
    mov BYTE [r15+ARRAY_T_OFF_SIZE] , cl
    mov BYTE [r15+ARRAY_T_OFF_CAPACITY] , dl
    
    ;multiplicacion
    mov rax ,SIZE_VOID_ASTERISCO
    mul [r12+ARRAY_T_OFF_SIZE]
    ;rax : sizeof(void*)*(nuevoArr->capacity)

    ; le asignamos la data
    mov rdi , rax
    call malloc ; en rax tenemos la data
    mov [r15+ARRAY_T_OFF_DATA], rax ; nuevoArr->data 

    mov r13, 0;contador
    
    .while:
        cmp r13 ,[r15+ARRAY_T_OFF_SIZE]
        jl .finWhile
        

    .finWhile:



    pop r13
    pop r15
    pop r14
    pop r12
    pop rbp 
    ret	 