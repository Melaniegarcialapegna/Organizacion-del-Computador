section .text
global strArrayNew
extern malloc
extern free

; Definición de constantes para los offsets y tamaños
STR_ARRAY_OFF_SIZE      EQU 0        ; Offset para el tamaño del arreglo
STR_ARRAY_OFF_CAPACITY  EQU 1        ; Offset para la capacidad del arreglo
STR_ARRAY_OFF_DATA      EQU 8        ; Offset para el puntero de datos
STR_ARRAY_TOTAL_SIZE    EQU 16       ; Tamaño total de la estructura
SIZE_CHAR_ASTERISCO     EQU 8        ; Tamaño de un puntero a char

strArrayNew:
    ; Inicio de la función para crear un nuevo arreglo de cadenas
    push rbp                  ; Guardar el puntero base
    mov rbp, rsp              ; Establecer el nuevo puntero base

    push rbx                  ; Guardar el registro rbx
    mov rbx, rdi              ; Cargar el argumento de capacidad en rbx
    sub rsp, 8                ; Alinear la pila

    ; Llamar a malloc para asignar memoria para la estructura del arreglo
    mov rdi, STR_ARRAY_TOTAL_SIZE
    call malloc               ; Llamar a malloc para asignar memoria

    ; En rax ahora tenemos el puntero al nuevo arreglo
    ; Configurar el campo de capacidad
    mov [rax + STR_ARRAY_OFF_CAPACITY], bl ; Almacenar la capacidad en la estructura

    ; Inicializar el campo de tamaño a 0
    mov byte [rax + STR_ARRAY_OFF_SIZE], 0 ; Establecer tamaño a 0

    push r14                  ; Guardar el registro r14
    mov r14, rax              ; Guardar el puntero al nuevo arreglo

    ; Calcular el tamaño para la asignación de datos: sizeof(char*) * capacidad
    mov rax, SIZE_CHAR_ASTERISCO ; Cargar el tamaño de un puntero a char
    ; La capacidad está en bl
    mul bl                    ; Multiplicar bl (capacidad) por rax (tamaño de un puntero a char)

    sub rsp, 8                ; Alinear la pila
    
    ; Ahora rax contiene el resultado de la multiplicación: sizeof(char*) * capacidad
    mov rdi, rax              ; Cargar el resultado en rdi para pasárselo a malloc
    call malloc               ; Llamar a malloc para asignar memoria para los datos

    ; En rax tenemos el puntero a char*
    mov [r14 + STR_ARRAY_OFF_DATA], rax ; arrNuevo->data = malloc(sizeof(char*) * capacidad);
    
    mov rax, r14              ; Devolver el puntero al nuevo arreglo
    ; [rax] -> accede a la dirección de memoria que guarda rax
    ; rax -> lo que tiene adentro rax

    add rsp, 8                ; Restaurar el espacio de la pila
    pop r14                   ; Recuperar r14
    add rsp, 8                ; Restaurar el espacio de la pila
    pop rbx                   ; Recuperar rbx
    pop rbp                   ; Recuperar el puntero base
    ret                       ; Retornar de la función
