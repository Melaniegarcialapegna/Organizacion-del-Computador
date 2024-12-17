#include "cachesim.h"

const int TAM_BUS = 32;

int main (int argc, char *argv[]){
    uint8_t modoVerboso = 0;
    int verbosoPrincipio = 0;
    int verbosoFinal = 0;
    info_t info;

    if (argc != 5 && argc != 8) {
        fprintf(stderr, "Uso: %s <archivo> <tamaño_cache> <asociatividad> <num_sets> [-v <start> <end>]\n", argv[0]);
        return 1;
    }
    char* archivoNombre = argv[1];
    uint32_t tamanioCache = (uint32_t)atoi(argv[2]);
    uint32_t asociatividad = (uint32_t)atoi(argv[3]);
    uint32_t numSets = (uint32_t)atoi(argv[4]);

    if (argc == 8) {
        if (strcmp(argv[5], "-v") == 0) {
            modoVerboso = 1;
            verbosoPrincipio = atoi(argv[6]);
            verbosoFinal = atoi(argv[7]);
        } else {
            fprintf(stderr, "Uso: %s <archivo> <tamaño_cache> <asociatividad> <num_sets> [-v <start> <end>]\n", argv[0]);
            return 1;
        }
    }
    
    FILE *archivo = fopen(archivoNombre, "r");
    if (archivo == NULL) {
        perror("ERROR al abrir el archivo");
        return 1;
    }

    uint32_t cantSets = numSets;
    uint32_t cantLineas = asociatividad;
    uint32_t tamBloque = tamanioCache / (cantSets * cantLineas);

    uint32_t contadorLecturas = 0;
    uint32_t contadorEscrituras = 0;
    uint32_t rmiss = 0;
    uint32_t wmiss = 0;
    uint32_t rdmiss = 0;
    uint32_t wdmiss = 0;
    uint32_t rtime = 0;
    uint32_t wtime = 0;
    uint32_t bytesRead = 0;
    uint32_t bytesWritten = 0;

    // Matriz
    line_t **sets = malloc(cantSets * sizeof(line_t*)); // sets[[set],[set]]->> set[linea,linea]
    for (uint32_t i = 0; i < cantSets; i++) {
        sets[i] = malloc(cantLineas * sizeof(line_t));
    }

    list_t **listasLRU = malloc(cantSets * sizeof(list_t*));
    for (uint32_t i = 0; i < cantSets; i++) {
        listasLRU[i] = listNew(1);
    }

    // Inicializar todo en 0
    for (uint32_t i = 0; i < cantSets; i++) {
        for (uint32_t j = 0; j < cantLineas; j++) {
            sets[i][j].valid = 0;
            sets[i][j].dirty = 0;
            sets[i][j].tag = 0;
        }
    }

    char linea[50];
    size_t i = 0;
    while (fgets(linea, 50, archivo) != NULL) {
        entrada_t *entrada = parsear(linea);

        info = obtenerLinea(entrada, cantSets, cantLineas, tamBloque, sets, listasLRU,i);
        borrarEntrada(entrada);
        
        bytesRead += info.bytesLeidos;
        bytesWritten += info.bytesEscritos;
        rtime += info.clocksRead;
        wtime += info.clocksWrite;

        if(info.tipo == TipoEscritura){
            contadorEscrituras++;
            switch(info.resultado){
                case ResultadoMiss: wmiss++ ;break;
                case ResultadoDirtyMiss: 
                    wmiss++;
                    wdmiss++; 
                    break;
            }
        } else{
            contadorLecturas++;
            switch(info.resultado){
                case ResultadoMiss: rmiss++ ;break;
                case ResultadoDirtyMiss: 
                rmiss++; 
                rdmiss++ ;
                break;
            }
        }

        if (modoVerboso && i>= verbosoPrincipio && i <=verbosoFinal) {
            printf("%lu ", i);
            printf("%s ", info.caso);
            printf("%x ", info.cacheIndex);
            printf("%x ", info.cacheTag);
            printf("%x ", info.cacheLine);
            if(info.lineTag == -1){
                printf("%d ", info.lineTag);
            } else{
                printf("%x ", info.lineTag);
            }
            printf("%d ", info.validBit);
            printf("%d", info.dirtyBit);
            if(cantLineas != 1){
                printf(" %d\n", info.lastUsed);
            } else{
                printf("\n");
            }
        }
        i++;
    }
    fclose(archivo);

    // Imprimir resumen de la ejecución y estadísticas
    uint32_t totalAccesos = contadorLecturas + contadorEscrituras;
    uint32_t totalMisses = rmiss + wmiss;
    uint32_t totalDirtyMisses = rdmiss + wdmiss;
    float missRate = (float)totalMisses / totalAccesos;
    char* way;
    
    if(asociatividad == 1){
        printf("direct-mapped, %d sets, size = %dKB\n", numSets, (tamanioCache / 1024)); //Para ponerlo en Kb
    } else{
        printf("%d-way, %d sets, size = %dKB\n", asociatividad, numSets, (tamanioCache / 1024)); //Para ponerlo en Kb
    }
    printf("loads %d stores %d total %d\n", contadorLecturas, contadorEscrituras, totalAccesos);
    printf("rmiss %d wmiss %d total %d\n", rmiss, wmiss, totalMisses);
    printf("dirty rmiss %d dirty wmiss %d\n", rdmiss, wdmiss);
    printf("bytes read %d bytes written %d\n", bytesRead, bytesWritten);
    printf("read time %d write time %d\n", rtime, wtime);
    printf("miss rate %f\n", missRate);

    // Liberar memoria
    for (uint32_t i = 0; i < cantSets; i++) {
        free(sets[i]);
        listDelete(listasLRU[i]);
    }

    free(sets);
    free(listasLRU);
    return 0;
}

entrada_t *parsear(char* linea){
    entrada_t *entrada = malloc(sizeof(entrada_t));
    list_t *lista = listNew(2);
    char *token = strtok(linea," ");
    while (token != NULL) {
        listAddLast(lista, token);
        token = strtok(NULL, " ");
    }//🤓
    
    //Obtenemos el instPointer de la entrada
    char *primerCampo = listRemove(lista, 0);
    size_t largoPrimerCampo = strlen(primerCampo);
    primerCampo[largoPrimerCampo-1] = '\0';
    
    // Obtenemos el tipo de lectura
    char *tipoStr = listRemove(lista, 0);
    tipo_t tipo = TipoEscritura;
    if(strcmp(tipoStr, "R") == 0){ 
        tipo = TipoLectura;
    }
    free(tipoStr);

    // Obtenemos la direccion de lectura
    char *direccion = listRemove(lista, 0);

    // Obtenemos la cantidad de bytes q se leeran
    char* numerito = listRemove(lista, 0);
    uint32_t cantBytes = (uint32_t)atoi(numerito);
    free(numerito);
    // Obtenemos los datos leidos
    char* datos = listRemove(lista, 0);
    
    //Liberamos la memoria ocupada por la lista
    listDelete(lista);

    // Guardamos los datos en el struct entrada
    entrada->instructionPointer = primerCampo;
    entrada->tipo = tipo;
    entrada->direccion = direccion; 
    entrada->cantBytes = cantBytes;
    entrada->datos = datos;
    return entrada;
}

char *hexaABin(char* hexadecimal){
    size_t cantDigitos = strlen(hexadecimal) - 2;
    char *numeroHex = malloc(cantDigitos + 1); 
    strncpy(numeroHex, hexadecimal+2,cantDigitos);
    numeroHex[cantDigitos] = '\0'; 

    int tamCadena = cantDigitos *4;
    char* numDecimal = malloc(tamCadena +1);

    for (size_t i = 0; i < cantDigitos; i++){
        switch (numeroHex[i])
        {
        case '0': agregarDigitos("0000", numDecimal, i*4); break;
        case '1': agregarDigitos("0001", numDecimal, i*4); break;
        case '2': agregarDigitos("0010", numDecimal, i*4); break;
        case '3': agregarDigitos("0011", numDecimal, i*4); break;
        case '4': agregarDigitos("0100", numDecimal, i*4); break;
        case '5': agregarDigitos("0101", numDecimal, i*4); break;
        case '6': agregarDigitos("0110", numDecimal, i*4); break;
        case '7': agregarDigitos("0111", numDecimal, i*4); break;
        case '8': agregarDigitos("1000", numDecimal, i*4); break;
        case '9': agregarDigitos("1001", numDecimal, i*4); break;
        case 'a': agregarDigitos("1010", numDecimal, i*4); break;
        case 'b': agregarDigitos("1011", numDecimal, i*4); break;
        case 'c': agregarDigitos("1100", numDecimal, i*4); break;
        case 'd': agregarDigitos("1101", numDecimal, i*4); break;
        case 'e': agregarDigitos("1110", numDecimal, i*4); break;
        case 'f': agregarDigitos("1111", numDecimal, i*4); break;
        default:break;
        }
    }
    numDecimal[tamCadena] = '\0';
    free(numeroHex);
    return numDecimal;
}

void agregarDigitos(char* digitos, char* destino, size_t i ){
    for(size_t j = 0; j < 4; j++){
        destino[i+j] = digitos[j];
    }
}
    
info_t obtenerLinea(entrada_t* entrada, uint32_t cantSets, uint32_t cantLineas, uint32_t tamBloque, line_t** sets, list_t **listasLRU, size_t indiceActual){
    info_t info;
    uint32_t bitsSet = (uint32_t)log2(cantSets);
    uint32_t bitsBloque = (uint32_t)log2(tamBloque);
    uint32_t bitsTag = TAM_BUS - bitsSet - bitsBloque; 

    //Pasamos el numero de hexa a decimal
    char* numBinarioStr = hexaABin(entrada->direccion);
    uint32_t direccion = strtoul(numBinarioStr, NULL, 2);
    free(numBinarioStr);
    
    //Mascaras para separar datos de la direccion
    uint32_t mascaraTag = 0xFFFFFFFF<<(TAM_BUS - bitsTag);
    uint32_t mascaraBloque = ~(0xFFFFFFFF<<(bitsBloque));
    uint32_t mascaraSet = ~(mascaraTag & mascaraBloque);
    
    //Mascara para filtrar los 
    uint32_t mascaraTagFinal = ~(0xFFFFFFFF << bitsTag);
    uint32_t mascaraSetFinal = ~(0xFFFFFFFF << bitsSet);

    uint32_t bloque = direccion & mascaraBloque;
    uint32_t tag = (direccion & mascaraTag) >> (bitsSet + bitsBloque);
    tag = tag & mascaraTagFinal;
    
    uint32_t set = (direccion & mascaraSet) >> (bitsBloque); 
    set = set & mascaraSetFinal;

    line_t *setActual = sets[set];
    list_t *listaActual = listasLRU[set];
    int tamanioLista = listGetSize(listaActual);
    
    info.cacheIndex = set;
    info.cacheTag = tag;
    info.dirtyBit = 0;
    info.validBit = 1;
    info.tipo = entrada->tipo;
    info.bytesLeidos = 0;
    info.bytesEscritos = 0;
    info.clocksRead = 0;
    info.clocksWrite = 0;

    if(entrada->tipo == TipoEscritura){
        info.clocksWrite = 1;
    } else{
        info.clocksRead = 1;
    }
    
    for (int i = 0; i < cantLineas ; i++){
        if (setActual[i].valid==1 && setActual[i].tag == tag){
            int largoAntes = listGetSize(listaActual);
            info.lastUsed = setActual[i].indice;
            setActual[i].indice = indiceActual;
            info.resultado = ResultadoHit;

            info.caso = "1"; //We can be heroes just for one day
            info.cacheLine = i;
            info.lineTag = tag;

            info.dirtyBit = setActual[i].dirty;

            if(entrada->tipo == TipoEscritura){
                setActual[i].dirty=1;
            }

            //Actualizamos lista LRU
            int *iPuntero = malloc(sizeof(int));
            *iPuntero = i;
            int indiceLista = listGetIndex(listaActual,iPuntero);
            int* removido = listRemove(listaActual,indiceLista);
            free(removido);
            listAddLast(listaActual, iPuntero);
            free(iPuntero);
            return info;
        }
    }
    
    //Si esta lleno -> desalojamos
    if (tamanioLista == cantLineas){
        int largoAntes = listGetSize(listaActual);
        int *indiceDesalojo = listRemove(listaActual, 0);
        info.lastUsed = setActual[*indiceDesalojo].indice;
        info.cacheLine = *indiceDesalojo;
        info.lineTag = setActual[*indiceDesalojo].tag;
        info.bytesLeidos = tamBloque;
        if(entrada->tipo == TipoEscritura){
            info.clocksWrite += 100;
        } else{
            info.clocksRead += 100;
        }

        if (setActual[*indiceDesalojo].dirty == 1){
            info.dirtyBit = 1;
            info.caso = "2b"; 
            info.resultado = ResultadoDirtyMiss;
            info.bytesEscritos = tamBloque;
            if(entrada->tipo == TipoEscritura){
                info.clocksWrite += 100;
            } else{
                info.clocksRead += 100;
            }
        } else {
            info.caso = "2a";
            info.resultado = ResultadoMiss;
        }
        setActual[*indiceDesalojo].indice = indiceActual;
        setActual[*indiceDesalojo].dirty = entrada->tipo;
        setActual[*indiceDesalojo].valid = 1;
        setActual[*indiceDesalojo].tag = tag;

        listAddLast(listaActual, indiceDesalojo);
        free(indiceDesalojo);
        int largoDespues = listGetSize(listaActual);
    } else{
        info.resultado = ResultadoMiss;
        info.lastUsed = 0;
        info.validBit = 0;
        info.caso = "2a";
        info.cacheLine = tamanioLista;
        info.lineTag = -1;
        info.bytesLeidos = tamBloque;

        if(entrada->tipo == TipoEscritura){
            info.clocksWrite += 100;
        } else{
            info.clocksRead += 100;
        }
        
        int *tamanio = malloc(sizeof(int));
        *tamanio = tamanioLista;
        
        listAddLast(listaActual, tamanio);

        free(tamanio);
        setActual[tamanioLista].dirty = entrada->tipo;
        setActual[tamanioLista].valid = 1;
        setActual[tamanioLista].tag = tag;
        setActual[tamanioLista].indice = indiceActual;
    }

    return info;
}

void borrarEntrada(entrada_t* entrada){
    free(entrada->instructionPointer);
    free(entrada->direccion);
    free(entrada->datos);
    free(entrada);
}