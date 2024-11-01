#MAKEFILE -> ejecutar una serie de comandos que tienen dependencias entre si (muy util para compilaciones!!)

#DECLARACION DE VARIABLES:
#Generar un target -> generar el archivo output-entrega-text, es el archivo donde se redirigira la salidan los resultados del circuito
OUTPUT := output-entrega.txt

#Comando que vamos a ejecutar
RUN_TEST := logisim-evolution --toplevel-circuit "verificador" -tty table

#Almacena los resultados que esperamos 
SALIDA_ESPERADA := salida_catedra.txt

#Contiene el nombre del archivo del circuito que luego ejecutaremos
CIRCUITO := TallerLogica-Combinatorios-individual.circ

#DECLARACION de los PHONY
.PHONY :clean all verificar


#COMANDO ALL: Sirve para no tener que especificar el target -> podemos ejecutar solo con el "make", genera archivo de salida de forma predeterminada
all: $(OUTPUT) verificar 

#ESTRUCTURA PARA GENERAR EL ARCHIVO DE SALIDA:
#Target(variable) : prerequisitos(que archivo necesito para generar este output-entrega)

#	comandos-> que voy a ejecutar en mi prerequisitos para obtener el target
#    $<  :  es una referencia al prerequisito
#    $@  :  es una referencia al target
$(OUTPUT) : $(CIRCUITO)
	@$(RUN_TEST) $< > $@
	@echo "Se genero el archivo de salida $(OUTPUT)"
	@echo "  "

#COMANDO VERIFICAR: Chequea que las salidas coincidan
verificar: $(OUTPUT)
	@echo "Comparando resultados..."
	@if diff -q $(OUTPUT) $(SALIDA_ESPERADA);then\
	    echo "Todo OK";\
	else\
	    echo "ERROR: Las salidas no coinciden";\
	    exit 1;\
	fi

#COMANDO CLEAN: Limpia y deja los archivo fuente(limpia archivos generados)
clean:
	@rm -rf $(OUTPUT)
	@echo "Se elimino el archivo de salida $(OUTPUT)"
