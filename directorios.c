#include "directorios.h"
#include "archivos.h"
#include "sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <iostream>

using namespace std;
bool unavez=true;


struct nodo_directorios{
	archivos archs;
	char * nombre;
	int cota;
	int tam;
	directorios padre;
	directorios sh;
	directorios ph;
};

directorios CREAR_DIRECTORIOS(){
// Crea la estructura vacia (solo con el raiz)
	directorios aux = new(nodo_directorios);
	aux->nombre = new(char[MAX_DIR]);
	strcpy(aux->nombre, "/");
	aux->archs = CREAR_ARCHIVOS();
	aux->cota = 0;
	aux->tam=0;
	aux->padre=NULL;
	aux->sh=NULL;
	aux->ph=CREAR_DIR_NULL();
	return aux;
	
}

directorios CREAR_DIR_NULL(){
	return NULL;
}

bool SOY_DIRECTORIO(directorios d, char * nombre){
// Retorna true si el nombre pasado ya pertenece al directorio d (es decir, ya existe)
	if (strcmp(d->nombre, nombre) == 0)
		return true;
	else
		return false;
}

bool PERTENECE_DIRECTORIO_DIRECTORIOS (directorios d, char * nombre){
// Retorna true si el directorio a pertenece al padre
	if (d == NULL)
		return false;
	else{
		if (SOY_DIRECTORIO(d, nombre))
			return true;
		else
			return PERTENECE_DIRECTORIO_DIRECTORIOS (d->sh, nombre);
	}
}

int SepararString (char * parametro, char * &padre, char * &new_dir){
//Esta funcion guarda en "padre" la ruta hasta el directorio donde se creará lo solicitado en mkdir, el nombre del nuevo directorio queda en "new_dir" 
	int i=0,contador=0;
    while(parametro[i] != '\0'){
      if(parametro[i] == '/'){
        contador++;
        i++;
      }else
        i++;
    }
    char * ruta_mod;
    ruta_mod = new (char[MAX_PARAMETRO]);
    ruta_mod = strtok (parametro, "/");
    strcpy (new_dir,ruta_mod);
    for (int i=0; i<contador-1; i++){
		strcat(padre, "/");
		strcat(padre,new_dir);
		new_dir=strtok(NULL,"/");
    }
	if(contador==1){
		strcat(padre, "/");
	}
	return contador;
}

void BUSCAR_ANTERIOR_HERMANO(directorios &hijo_actual, directorios aux){
		if(hijo_actual->sh==NULL)
			ASOCIAR_HERMANO(hijo_actual, aux); //"ultimo hijo" en ASOCIAR_HERMANO
		else
			return BUSCAR_ANTERIOR_HERMANO (hijo_actual->sh, aux);
}

void ASOCIAR_HERMANO(directorios & ultimo_hijo, directorios aux){
	ultimo_hijo->sh=aux;
}

TipoRet MKDIR_DIRECTORIOS_ABSOLUTA(directorios &raiz, char * parametro, int cota){ 
	TipoRet retorno;
	directorios actual = new (nodo_directorios);
	actual = raiz;
	directorios padre_rel = new (nodo_directorios);
	char *new_dir = new (char[MAX_PARAMETRO]);
    char * padre = new (char[MAX_PARAMETRO]);
	int contador=0;
	char * tokenized = new (char[MAX_DIR]);
	contador= SepararString (parametro, padre, new_dir);
	while(contador>1){
			TOKEN (padre, tokenized);
			retorno=CD_DIRECTORIOS_REL(actual, tokenized, padre_rel);
			contador--;
			padre=strtok(NULL, "/");
	}
	if(retorno == ERROR){
		return retorno;
	}
	else
		return MKDIR_DIRECTORIOS_REL(actual, new_dir, cota);
}

TipoRet MKDIR_DIRECTORIOS_REL (directorios & p, char * nombreDirectorio, int cota){
	directorios respaldo = p;
	directorios actual = p;
	directorios padre_rel = p;
	//actual es el dir en el que estamos parados
	if(actual->ph==NULL){
		directorios aux = new(nodo_directorios);
		aux->nombre = new(char[MAX_DIR]);
		strcpy(aux->nombre, nombreDirectorio);
		aux->archs = CREAR_ARCHIVOS();
		aux->cota = cota;
		aux->tam = 0;
		aux->padre=p;
		aux->sh=CREAR_DIR_NULL();
		aux->ph=CREAR_DIR_NULL();
		p->ph=aux;
		return OK;
	}
	else{
		//Tiene hijos; hay que buscar en el ultimo hermano para conectar el aux que se va a crear
		padre_rel=actual;
		actual=actual->ph;
		if(PERTENECE_DIRECTORIO_DIRECTORIOS(actual, nombreDirectorio)){
			printf ("Error, ya existe el directorio.\n");
			p=respaldo;
			return ERROR;
		}

		while(actual->sh!=NULL){
			actual=actual->sh;
			if(PERTENECE_DIRECTORIO_DIRECTORIOS(actual, nombreDirectorio)){
				printf ("Error, ya existe el directorio %s.\n", nombreDirectorio);
				p=respaldo;
				return ERROR;
			}
		}
		directorios aux = new(nodo_directorios);
		aux->nombre = new(char[MAX_DIR]);
		strcpy(aux->nombre, nombreDirectorio);
		aux->archs = CREAR_ARCHIVOS();
		aux->cota = cota;
		aux->tam = 0;
		aux->padre=padre_rel;
		aux->sh=CREAR_DIR_NULL();
		aux->ph=CREAR_DIR_NULL();
		actual->sh=aux;
		return OK;
	}

}

TipoRet CD_DIRECTORIOS_REL (directorios &actual, char * ruta, directorios &aux){
	//Analizar si existe la carpeta y cambiar el s->actual a esa carpeta; utilizando el SOY_ARCHIVO, buscando entre hermanos
	//Si no existe, retornar error
	// else 
	if(unavez){
		if(actual->ph!=NULL){
			aux=actual->ph;
			unavez=false;
		}
		else{
			printf("El directorio actual no tiene subdirectorios.\n");
			unavez=true;
			return ERROR;
		}	
	}
	if (SOY_DIRECTORIO(aux, ruta)){
			actual=aux;
			unavez=true;
			return OK;
	}
	else{
			if(aux->sh==NULL){
				printf ("No existe el directorio de destino en este directorio\n");
				unavez=true;
				return ERROR;
			}
			else
					return CD_DIRECTORIOS_REL(actual, ruta, aux->sh);	
	}
}
void TOKEN (char * padre, char * &tokenized){
	tokenized = strtok (padre, "/");
}

TipoRet CD_DIRECTORIOS_ABS (directorios &dirs, char * ruta, directorios &actual){
	TipoRet retorno;
	directorios respaldo_actual = new (nodo_directorios);
	directorios padre_rel = new (nodo_directorios);
	respaldo_actual = actual; //cuando confirme la ruta, el acutal queda en la ultima posicion; de lo contrario, lo vuelvo al respaldo_actual
	int contador=0;
	bool loencontre=false;
	char * tokenized = new (char[MAX_PARAMETRO]);
	char * aux = new (char[MAX_PARAMETRO]);
	char * padre = new (char[MAX_PARAMETRO]);
	contador= SepararString (ruta,padre,aux);
	strcat(padre, "/");
	strcat(padre,aux);
	while(contador>0){
		TOKEN (padre, tokenized);
		retorno=CD_DIRECTORIOS_REL(actual, tokenized, padre_rel);
		contador--;
		padre=strtok(NULL, "/");		
	}
	if(retorno == ERROR){
		actual=respaldo_actual;
		return retorno;
	}
	else
		return retorno;
}

TipoRet SUBIR_UN_NIVEL (directorios &actual, char * ruta){
	if((strcmp(actual->nombre,"/")==0)){
		printf("Directorio actual es la raíz, no se puede subir.\n");
		return ERROR;
	}
	else{
		actual=actual->padre;
		return OK;
	}
}
void IMPRIMIR_DIRECTORIO(directorios d){
// Imprime el contenido del directorio pasado como parametro en la salida estandar.
	directorios backup=d;
	int q;
	if(d->ph!=NULL){
		d=d->ph;
		q=CALCULAR_QUOTA(d->archs);
		if(d->cota==0)
			printf("%s\tDirectorio\t%d File_Lines\n",d->nombre,q);
		else
			printf("%s\tDirectorio\t%d%%\n",d->nombre,q=q*100/d->cota);
		while(d->sh!=NULL){
			d=d->sh;
			q=CALCULAR_QUOTA(d->archs);
			if(d->cota==0)
				printf("%s\tDirectorio\t%d File_Lines\n",d->nombre,q);
			else
				printf("%s\tDirectorio\t%d%%\n",d->nombre,q=q*100/d->cota);
		}
	}
	d=backup;
	IMPRIMIR_ARCHIVOS(d->archs);
}


TipoRet CREATE_ARCHIVO_DIR (directorios d, char * nombreArchivo){
// Crea un archivo en el directorio actual.
	return CREATE_ARCHIVO_ARCHIVOS(d->archs, nombreArchivo);
}

TipoRet INSERTAR_LINEA_DIR (directorios d, char * nombreArchivo, char * extensionArchivo, char * texto){
	int q=0;
	q=CALCULAR_QUOTA(d->archs);
	return INSERTAR_LINEA_ARCHIVOS (d->archs, nombreArchivo, extensionArchivo, texto, d->cota, d->tam);
}

TipoRet IMPRIMIR_ARCHIVO_DIR (directorios &d, char * nombreArchivo, char * extensionArchivo){
	return IMPRIMIR_ARCHIVO_ARCHIVOS (d->archs, nombreArchivo, extensionArchivo);
}
