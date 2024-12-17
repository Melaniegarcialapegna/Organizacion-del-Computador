CC=gcc
ASM=nasm
CFLAGS=-Wall -Wextra -pedantic -std=c11 -O0 -ggdb -no-pie -g
ASMFLAGS=-f elf64
LIBS=-lm

# Archivos fuente y objeto
CACHESIM_SRCS=cachesim.c 
LIST_SRCS= listaEnlazada.c
ASM_SRCS=archivo.asm
OBJS=cachesim.o listaEnlazada.o archivo.o 

all: cachesim

cachesim: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

cachesim.o: $(CACHESIM_SRCS)
	$(CC) -g -c $< -o $@

listaEnlazada.o: $(LIST_SRCS)
	$(CC) -g -c $< -o $@
	
archivo.o: $(ASM_SRCS)
	$(ASM) $(ASMFLAGS) $< -o $@
	
clean:
	rm -f *.o
	rm -f cachesim
