nom_func:
    push rbp ; meter la direccion de RBP anterior a la pila (va a ser el nuevo tope por lo qeu ele RSP va a apuntar a este)
    mov rbp, rsp ; como el RSP apunta siempre al TOPE DE LA PILA, le mandamos la direccion en la que esta el tope para que el RBP tmb apunte a este

    

    pop rbp ; (desapilar xd)El RCP vuelve a puntar al rip(la direccion de arriba(extope)) y ese valor que desapilamos que era la direccion a la que apuntaba el RBP viejo se borra y el RBP vuelve a apuntar a esa direccion(valor viejo del rbp)
    ret
