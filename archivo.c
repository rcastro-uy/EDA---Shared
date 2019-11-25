#include "archivo.h"
#include "contenido.h"
#include "definiciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

//PRUEBA


using namespace std;

struct nodo_archivo{
	char * nombre;
	char * extension;
	contenido cont;
	int tamano;
};

int QUOTA_ARCHIVO (archivo a){
	return a->tamano;
}
archivo CREAR_ARCHIVO(char * nombre, char * extension){
// Crea el archivo nombre.extension.
	archivo aux = new(nodo_archivo);
	aux->nombre = new(char[MAX_ARCH]);
	strcpy(aux->nombre, nombre);	
	aux->extension = new(char[MAX_EXTENSION]);
	strcpy(aux->extension, extension);
	aux->cont = CREAR_CONTENIDO();
	aux->tamano = 0;
	return aux;
}

void IMPRIMIR_ARCHIVO(archivo a){
// Imprime el nombre extension y tamaño del archivo en la salida estandar.
	cout << a->nombre << "." << a->extension << "\tArchivo\t" << a->tamano << "\n";
}

bool SOY_ARCHIVO(archivo a, char * nombre, char * extension){
// Retorna true si a tiene el nombre y la extension pasados como parametro, false en caso contrario.
	if ((strcmp(a->nombre, nombre) == 0) && (strcmp(a->extension, extension) == 0))
		return true;
	else
		return false;
}


char * NOMBRE_ARCHIVO(archivo a){
// Retorna el nombre del archivo.
	return a->nombre;
}

char * EXTENSION_ARCHIVO(archivo a){
// Retorna el nombre del archivo.
	return a->extension;
}

TipoRet INSERTAR_LINEA_ARCHIVO (archivo &a, char * texto, int cota, int &dir_size){
	if(cota==0){
		INSERTAR_LINEA_CONTENIDO_IF (a->cont, texto);
		a->tamano ++;
		return OK;
	}
	else{
		if((a->tamano<cota)&&(dir_size<cota)){
			INSERTAR_LINEA_CONTENIDO_IF (a->cont, texto);
			a->tamano ++;
			dir_size ++;
			return OK;
		}
		else{
			printf("El tamaño del archivo supera la cota definida para el directorio.\n");
			return ERROR;
		}
	}
}

TipoRet IMPRIMIR_ARCHIVO_ARCHIVO (archivo a){
	return IMPRIMIR_ARCHIVO_CONTENIDO(a->cont);
}
