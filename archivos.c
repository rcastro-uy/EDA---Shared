#include "archivos.h"
#include "archivo.h"
#include "definiciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdbool.h>

using namespace std;

struct nodo_archivos{
	archivo actual;
	archivos sig;
};

archivos CREAR_ARCHIVOS(){
// Crea el conjunto de archivos vacio.
	return NULL;
}

int CALCULAR_QUOTA (archivos as){
	if(as!=NULL){
		return QUOTA_ARCHIVO (as->actual)+CALCULAR_QUOTA(as->sig);
	}
	else
		return 0;
}

void IMPRIMIR_ARCHIVOS(archivos as){
// Imprime nombre, extension y tamaño de los archivos pertenecientes al conjunto.
	if (as!= NULL){
		IMPRIMIR_ARCHIVO(as->actual);
		IMPRIMIR_ARCHIVOS(as->sig);
	}
}


bool PERTENECE_ARCHIVO_ARCHIVOS (archivos as, char * nombre, char * extension){
// Retorna true si el archivo a pertenece a as
	if (as == NULL)
		return false;
	else{
		if (SOY_ARCHIVO(as->actual, nombre, extension))
			return true;
		else{
			// printf("Va a revisar el siguiente archivo.\n");
			return PERTENECE_ARCHIVO_ARCHIVOS (as->sig, nombre, extension);
		}
	}
}

archivos INSERTAR_ARCHIVO_ORDENADO_ARCHIVOS(archivos & as, archivo a){
// Inserta a en orden (alfabetico) en as.

	archivos aux = new(nodo_archivos);
	aux->actual = a;

	bool inserte = false;


	archivos actual = as;
	archivos anterior = NULL;

	char nombre_ext[MAX_ARCH + MAX_EXTENSION];
	strcpy (nombre_ext, NOMBRE_ARCHIVO(a));
	strcat (nombre_ext, EXTENSION_ARCHIVO(a));


	char nombre_ext_actual[MAX_ARCH + MAX_EXTENSION];

		
	while ((actual!= NULL) && !inserte){
		strcpy (nombre_ext_actual, NOMBRE_ARCHIVO(actual->actual));
		strcat (nombre_ext_actual, EXTENSION_ARCHIVO(actual->actual));
		if (strcmp (nombre_ext_actual, nombre_ext) > 0){
			if (anterior == NULL){
				aux->sig = as;
				as = aux;
			}else{
				anterior->sig = aux;				
				aux->sig = actual;				
			}
			inserte = true;
		}else{
			anterior = actual;
			actual = actual->sig;
		}
	}
	if ((actual == NULL) && !inserte){
		if (anterior == NULL)
			as = aux;
		else
			anterior->sig = aux;
		aux->sig = NULL;
	}
	return as;
}

TipoRet CREATE_ARCHIVO_ARCHIVOS(archivos & as, char * nombreArchivo){
// Crea un archivo en el conjunto de archivos.
	char * nombre, * extension;
	nombre = strtok (nombreArchivo,".");
	if (nombre != NULL){
		extension = strtok (NULL, ".");
		if (extension == NULL){
			extension = new(char[strlen("")]);
			strcpy(extension, "");
		}
	}

	if (!PERTENECE_ARCHIVO_ARCHIVOS (as, nombre, extension)){
		if((strlen(nombre) <= MAX_ARCH) && (strlen (extension) <= MAX_EXTENSION)){
			archivo a = CREAR_ARCHIVO(nombre, extension);
			as = INSERTAR_ARCHIVO_ORDENADO_ARCHIVOS(as, a);
			return OK;
		}
		else{
			cout << "El nombre del archivo o su extension no cumplen el largo perimitido.\n";
			return ERROR;
		}
	}else{
		cout<<"El archivo a crear ya existe en este directorio.\n";
		return ERROR;
	}
}

TipoRet INSERTAR_LINEA_ARCHIVOS (archivos &as, char * nombreArchivo, char * extensionArchivo, char * texto, int cota, int &dir_size){
	if(SOY_ARCHIVO(as->actual, nombreArchivo, extensionArchivo)){
		INSERTAR_LINEA_ARCHIVO(as->actual, texto, cota, dir_size);
		return OK;
	}
	else{
		if (as->sig==NULL){ 
				printf ("No existe el archivo.\n");
				return ERROR;
		}
		else
		 return INSERTAR_LINEA_ARCHIVOS (as->sig, nombreArchivo, extensionArchivo, texto, cota, dir_size);
	}
}

TipoRet IMPRIMIR_ARCHIVO_ARCHIVOS (archivos as, char * nombreArchivo, char * extensionArchivo){
	if(!SOY_ARCHIVO(as->actual,nombreArchivo, extensionArchivo)){
		//Entra cuando el nombreArchivo es diferente al archivo actual
			if(as->sig==NULL){
				cout << "No existe el archivo.\n";
				return ERROR;
			}
			else
				return IMPRIMIR_ARCHIVO_ARCHIVOS (as->sig, nombreArchivo, extensionArchivo);
	}
	else{
		IMPRIMIR_ARCHIVO_ARCHIVO (as->actual);
	}
}