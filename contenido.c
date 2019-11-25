#include "contenido.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <unistd.h>
#include "definiciones.h"

using namespace std;

struct nodo_contenido{
	char * linea;
	contenido sig;
};

bool isEmptyLinea (char * a){
	return (a == NULL);
}

contenido CREAR_CONTENIDO(){
// Crea el contenido vacio.
	return NULL;
}

contenido IMPLEMENTAR_CONTENIDO(){
	contenido aux = new(nodo_contenido);
	aux->linea = new(char[TEXTO_MAX]);
	aux->sig = CREAR_CONTENIDO();
	return aux;
}

void INSERTAR_LINEA_CONTENIDO_IF(contenido &c, char * texto){
	if(c==NULL){
		c=IMPLEMENTAR_CONTENIDO();
		strcpy(c->linea, texto);
	}
	else{
		INSERTAR_LINEA_CONTENIDO_IF(c->sig, texto);
	}

}


TipoRet IMPRIMIR_ARCHIVO_CONTENIDO(contenido c){
	if(c==NULL)
		return ERROR;
	else{
		printf("%s\n",c->linea);
		if(c->sig!=NULL)
			IMPRIMIR_ARCHIVO_CONTENIDO(c->sig);
		else
			return OK;
	}
}

bool EXISTE_CONTENIDO(contenido c){
	return(c!=NULL);
}