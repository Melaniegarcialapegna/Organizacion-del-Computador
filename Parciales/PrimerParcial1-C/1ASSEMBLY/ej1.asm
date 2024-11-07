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

    mov r12 ,rdi ; r12 : array_t
    mov r14, rsi ; r14 : funcion a aplicar

    mov rdi, ARRAY_T_TAM_TOTAL
    call malloc ;rax : puntero nuevoArr

    aca no volatiles
    



    pop rbp 
    ret	 