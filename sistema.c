#include "sistema.h"
#include "directorios.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>

struct nodo_sistema{
	directorios dirs;
	directorios actual;
};


Sistema CREAR_SISTEMA (){
// Crea un Sistema de Archivos Nuevo.
// Al crearlo no tiene ningun archivo o directorio (solo el raiz).
	Sistema aux = new(nodo_sistema);
	aux->dirs = CREAR_DIRECTORIOS();
	aux->actual = aux->dirs;
	return aux;
}


TipoRet DIR (Sistema &s, string parametro){
// Muestra el contenido del directorio actual.
// Siempre retorna OK.
	IMPRIMIR_DIRECTORIO(s->actual);
	return OK;
}

TipoRet CREATE (Sistema &s, string nombreArchivo){
// Crea  un  nuevo  archivo  vacío en  el directorio 
// especificado  por  su ruta (relativa o absoluta).
// Retorna OK si el archivo pudo ser creado exitosamente.
// Retorna ERROR si ya existe un archivo con ese nombre
// completo en el directorio actual.
	return CREATE_ARCHIVO_DIR (s->actual, nombreArchivo);// falta ver rutas absolutas 2da tarea
}

TipoRet DELETE (Sistema & s, string nombreArchivo){
// Elimina un archivo del Sistema de Archivos. El archivo
// a ser borrado puede ser especificado mediante una ruta relativa
// o absoluta.
// Retorna OK si se pudo eliminar el archivo exitosamente.
// Retorna ERROR si no existe un archivo con ese nombre en
// el directorio  actual.
	return NO_IMPLEMENTADA;
}

TipoRet UNDELETE (Sistema &s){
// Recupera  el  último  archivo  eliminado en  el  sistema
// mediante  el  comando DELETE (si  hay  al  menos  uno,  sino
// no  tiene  efecto).
// Retorna OK si se pudo recuperar el archivo exitosamente.
// Retorna ERROR si no existe el archivo a recuperar.
	return NO_IMPLEMENTADA;
}

TipoRet IC (Sistema &s, string nombreArchivo, string texto){
// Inserta  una  línea  al  comienzo  del  texto  del archivo
// nombreArchivo  (la  información  a  insertar debe ir entre comillas (“),
// el texto a su vez no podrá contener ese caracter).
// Recordar que si un directorio está acotado, su tamaño máximo no
// puede ser excedido
// Retorna OK si se pudo insertar el texto al final del archivo.
// Retorna ERROR si no existe un archivo con ese nombre en el directorio
// actual o Si la línea a insertar no está entre comillas o si  no  se
// pudo insertar  el  texto  por  superar  el  largo  máximo establecido.
	return NO_IMPLEMENTADA;
}

TipoRet IF (Sistema &s, string nombreArchivoExt, string texto){
// Inserta una línea al final del texto del archivo nombreArchivo.
// (vale la misma acotación que para el comando IC).
// Retorna OK si se pudo insertar el texto al final del archivo.
// Retorna ERROR si no existe un archivo con ese nombre en el directorio
// actual o si la línea a insertar no está entre comillas o si no se  pudo
// insertar  el  texto  por  superar  el  largo  máximo establecido.
	// printf ("Llegamos a Sistema\n");
	char * nombreArchivo, * extensionArchivo;
	nombreArchivo = strtok (nombreArchivoExt,".");
	if (nombreArchivo != NULL){
		extensionArchivo = strtok (NULL, ".");
		if (extensionArchivo == NULL){
			extensionArchivo = new(char[strlen("")]);
			strcpy(extensionArchivo, "");
		}
	}
	return INSERTAR_LINEA_DIR ( s->actual, nombreArchivo, extensionArchivo, texto);

}

TipoRet BC (Sistema &s, string nombreArchivo, int k){
// Borra, a lo sumo, las k primeras líneas de texto del archivo
// nombreArchivo. Si el texto tiene k o menos líneas, éste queda vacío.
// Retorna OK si  se  pudieron  eliminar  las  a  lo  sumo  k  primeras
// líneas  del archivo  parámetro,  aún  cuando  k  fuera  mayor  o  igual
// a  la cantidad  de  líneas  del  archivo  en  cuestión  (en  cuyo  caso
// el contenido quedaría vacío).
// Retorna ERROR si no existe un archivo con ese nombre en el directorio
// actual.
	return NO_IMPLEMENTADA;
}

TipoRet BF (Sistema &s, string nombreArchivo, int k){
// Borra, a lo sumo, las k últimas líneas de texto del archivo nombreArchivo.
// Si el texto tiene k o menos líneas, éste queda vacío.
// Retorna OK si  se  pudieron  eliminar  las  a  lo  sumo  k  últimas
// líneas  del archivo  parámetro,  aún  cuando  k  fuera  mayor  o  igual
// a  la cantidad  de  líneas  del  archivo  en  cuestión  (en  cuyo  caso
// el contenido quedaría vacío).
// Retorna ERROR si no existe un archivo con ese nombre en el directorio
// actual.
	return NO_IMPLEMENTADA;
}

TipoRet CAT (Sistema &s, string nombreArchivo1, string nombreArchivo2){
// Concatena  el archivo nombreArchivo2  a  continuación  del archivo
// nombreArchivo1, dejando el contenido del archivo resultante en
// nombreArchivo1. El archivo nombreArchivo2 no se modifica.
// Recordar que si un directorio está acotado, su tamaño máximo no
// puede ser excedido.
// Retorna OK si se pudieron concatenar los archivos.
// Retorna ERROR si  no  existe  un  archivo  con  nombreArchivo1  en  el
// directorio actual o si  no  existe  un  archivo nombreArchivo2  en  el
// directorio actual.
	return NO_IMPLEMENTADA;
}

TipoRet TYPE (Sistema &s, string nombreArchivoExt){
// Muestra  por  pantalla  el  contenido  de nombreArchivo.  Cada  línea
// del archivo se desplegará en una línea nueva en la pantalla.
// Retorna OK si  se  pudo  mostrar  el  contenido  del  archivo  (aún
// cuando  éste fuere nulo).
// Retorna ERROR si no existe un archivo con ese nombre en el directorio
// actual.
	char * nombreArchivo, * extensionArchivo;
	nombreArchivo = strtok (nombreArchivoExt,".");
	if (nombreArchivo != NULL){
		extensionArchivo = strtok (NULL, ".");
		if (extensionArchivo == NULL){
			extensionArchivo = new(char[strlen("")]);
			strcpy(extensionArchivo, "");
		}
	}
	return IMPRIMIR_ARCHIVO_DIR (s->actual, nombreArchivo, extensionArchivo);
}
bool ES_RUTA_RELATIVA (char * nombreDirectorio){
	if(nombreDirectorio[0]=='/')
		return false;
	else
		return true;
}

TipoRet MKDIR (Sistema &s, char * ruta, int cota){
	if(strcmp(ruta, "/")!=0){
		//Analisis de ruta asoluta o relativa
		if(ES_RUTA_RELATIVA(ruta)){//analizar primer caracter, si NO es "/")
			return MKDIR_DIRECTORIOS_REL (s->actual, ruta, cota); //actual que es el padre
		}
			//voy hasta la raíz; para eso, uso s->dirs, que apunta a "/"*/
		else
			return MKDIR_DIRECTORIOS_ABSOLUTA(s->dirs, ruta, cota);
	}
	else{
		printf("No se puede crear un directorio llamado RAIZ \"/\" ");
		return ERROR;
	}
	
}
bool ES_SUBIR (char * ruta){
	if((ruta[0]=='.')&&(ruta[1]=='.'))
		return true;
	else
		return false;
}
TipoRet CD (Sistema &s, char * ruta){
	if(ES_SUBIR (ruta)){
		return SUBIR_UN_NIVEL(s->actual, ruta);
	}
	if(ES_RUTA_RELATIVA(ruta)){
		directorios aux=s->actual;
		return CD_DIRECTORIOS_REL (s->actual, ruta, aux);
	}
	else{
		return CD_DIRECTORIOS_ABS (s->dirs, ruta, s->actual);
	}
}

Sistema DESTRUIR_SISTEMA (){
// Destruye el sistema de archivos y libera la memoria asociada.
	
}

int END_QUOTES(char * str){
	//retorna 0 si al final tiene comillas
	return ( str && *str && str[strlen(str) -1] == '"') ? 0 : 1;
}

bool TIENE_COMILLAS (char * a){
	int aux;
	if(a[0] == '"'){
		aux=END_QUOTES(a);
		if(aux==0)
			return true;
		else
		{
			printf("Error en el formato ingresado. El texto no termina con comillas\n");
			return false;
		}		
	}
	else{
		printf("Error en el formato ingresado. El texto no comienza con comillas\n");
		return false;
	}
}

bool TIENE_COMILLAS_LARGO_CORRECTO(char * parametro1){
	if(TIENE_COMILLAS(parametro1)){
		if(strlen(parametro1)-2<TEXTO_MAX){
			return true;
		}
		else{
			printf ("El texto es más largo de lo permitido.\n");
			return false;
		}	
	}
	else{
		printf ("El texto ingresado no tiene comillas.\n");
		return false;
	}
}
