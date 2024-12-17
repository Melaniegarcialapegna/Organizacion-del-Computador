#ifndef CONSTANTE
#define CONSTANTE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "listaEnlazada.h"

typedef enum e_tipo{
    TipoLectura = 0,
    TipoEscritura = 1
} tipo_t;

typedef enum e_resultado{
    ResultadoHit = 0,
    ResultadoMiss = 1,
    ResultadoDirtyMiss = 2
} resultado_t;

typedef struct info_t{
    char* caso;
    uint32_t cacheIndex;
    uint32_t cacheLine;
    uint32_t cacheTag;
    int32_t lineTag;
    uint8_t validBit;
    uint8_t dirtyBit;
    int32_t lastUsed;
    tipo_t tipo;
    resultado_t resultado;
    uint32_t bytesLeidos;
    uint32_t bytesEscritos;
    uint32_t clocksRead;
    uint32_t clocksWrite;
} info_t;

typedef struct s_entrada{
    char* instructionPointer;
    tipo_t tipo;
    char* direccion;
    uint32_t cantBytes;
    char* datos;
} entrada_t;

typedef struct s_line{
    uint32_t valid;
    uint32_t dirty;
    uint32_t tag;
    size_t indice;
} line_t;

entrada_t *parsear(char* linea);
info_t obtenerLinea(entrada_t* entrada, uint32_t cantSets, uint32_t cantLineas, uint32_t cantBloques, line_t** sets, list_t **listasLRU, size_t i);
char *hexaABin(char* hexadecimal);
void agregarDigitos(char* digitos, char* destino, size_t i );
void borrarEntrada(entrada_t* entrada);

#endif