char *hexaABin(char* hexadecimal){
    //Momento Falopa
    size_t cantDigitos = strlen(hexadecimal) - 2;
    char *numeroHex = malloc(cantDigitos + 1); //El +1 es por el /0.. C no se da cuenta :/
    //Averiguar bien como usar el strncpy.. pero podria agarrar desde el 3ero (¿)
    numeroHex[cantDigitos] = "/0"; //Al final ponerle el /0 (sino rompia)


    int tamCadena = cantDigitos *4;
    char * numDecimal = malloc (tamCadena +1);//Por el barra 0 pq lo estoy haciendo un char (se lo pongo al final)

    for (size_t i = 0; numeroHex[i]; i++){//Con un for en vez de un while para q qde mas fachero
        switch (numeroHex[i])
        {
        case '0': 
            agregarDigitos("0000", resultado, i*4);
            break;
        
        case '1':
            agregarDigitos("0001", resultado, i*4);
            break;

        case '2':
            agregarDigitos("0010", resultado, i*4);
            break;
            
        case '3':
            agregarDigitos("0011", resultado, i*4);
            break;
            
        case '4':
            agregarDigitos("0100", resultado, i*4);
            break;
        
        case '5': 
            agregarDigitos("0101", resultado, i*4);
            break;
        
        case '6':
            agregarDigitos("0110", resultado, i*4);
            break;

        case '7':
            agregarDigitos("0111", resultado, i*4);
            break;
            
        case '8':
            agregarDigitos("1000", resultado, i*4);
            break;
            
        case '9':
            agregarDigitos("1001", resultado, i*4);
            break;
        
        case 'A':
            agregarDigitos("1010", resultado, i*4);
            break;

        case 'B':
            agregarDigitos("1011", resultado, i*4);
            break;
            
        case 'C':
            agregarDigitos("1100", resultado, i*4);
            break;
            
        case 'D':
            agregarDigitos("1101", resultado, i*4);
            break;
        
        case 'E':
            agregarDigitos("1110", resultado, i*4);
            break;
        
        case 'F':
            agregarDigitos("1111", resultado, i*4);
            break;

        default:
            break;
        }
    }
    numDecimal[tamCadena] = "/0";
    free(numeroHex);
    return numDecimal;
}

void agregarDigitos(char* digitos, char* destino, size_t i ){
    for(size_t j = 0; j < 3; j++){
        destino[i+j] = digitos[j];
    }
}

//----------------------------------------------------------------



char *hexaABin(char* hexadecimal){
    
    //Nos falta el /0 --CREO QUE ESTA PARTE NO FUNCA------------
    //Sacamos el 0x
    size_t cantDigitos = strlen(hexadecimal) - 2;
    char numeroHex[cantDigitos];

    for(size_t i = 2; i < strlen(hexadecimal); i++){
        numeroHex[i-2] = hexadecimal[i];
    }
    
    int tamCadena = strlen(numeroHex)*4;
    char resultado[tamCadena]; //No es un malloc(??)
    char * decimal;
    //------------------------------------------------------------

    for (size_t i = 0; numeroHex[i]; i++){//Con un for en vez de un while para q qde mas fachero
        switch (numeroHex[i])
        {
        case '0': 
            agregarDigitos("0000", resultado, i*4);
            break;
        
        case '1':
            agregarDigitos("0001", resultado, i*4);
            break;

        case '2':
            agregarDigitos("0010", resultado, i*4);
            break;
            
        case '3':
            agregarDigitos("0011", resultado, i*4);
            break;
            
        case '4':
            agregarDigitos("0100", resultado, i*4);
            break;
        
        case '5': 
            agregarDigitos("0101", resultado, i*4);
            break;
        
        case '6':
            agregarDigitos("0110", resultado, i*4);
            break;

        case '7':
            agregarDigitos("0111", resultado, i*4);
            break;
            
        case '8':
            agregarDigitos("1000", resultado, i*4);
            break;
            
        case '9':
            agregarDigitos("1001", resultado, i*4);
            break;
        
        case 'A':
            agregarDigitos("1010", resultado, i*4);
            break;

        case 'B':
            agregarDigitos("1011", resultado, i*4);
            break;
            
        case 'C':
            agregarDigitos("1100", resultado, i*4);
            break;
            
        case 'D':
            agregarDigitos("1101", resultado, i*4);
            break;
        
        case 'E':
            agregarDigitos("1110", resultado, i*4);
            break;
        
        case 'F':
            agregarDigitos("1111", resultado, i*4);
            break;

        default:
            break;
        }
    }
}
