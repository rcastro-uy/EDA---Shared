#ifndef DIRECTORIOS_H
#define DIRECTORIOS_H

#include "definiciones.h"

typedef struct nodo_directorios * directorios;

directorios CREAR_DIRECTORIOS();
// Crea la estructura vacia (solo con el raiz)

void IMPRIMIR_DIRECTORIO(directorios d);
// Imprime el contenido del directorio pasado como parametro en la salida estandar.

TipoRet CREATE_ARCHIVO_DIR (directorios d, char * nombreArchivo);
// Crea un archivo en el directorio actual.

TipoRet INSERTAR_LINEA_DIR (directorios d, char * nombreArchivo, char * extensionArchivo, char * texto);

TipoRet IMPRIMIR_ARCHIVO_DIR (directorios &d, char * nombreArchivo, char * extensionArchivo);

directorios CREAR_DIR_NULL ();

TipoRet MKDIR_DIRECTORIOS_REL (directorios &p , char * nombreDirectorio, int cota);

TipoRet MKDIR_DIRECTORIOS_ABSOLUTA(directorios &raiz, char * parametro, int cota);

bool PERTENECE_DIRECTORIO_DIRECTORIOS (directorios d, char * nombre);

bool SOY_DIRECTORIO(directorios d, char * nombre);

TipoRet CD_DIRECTORIOS_REL (directorios &actual, char * ruta, directorios &aux);

TipoRet CD_DIRECTORIOS_ABS (directorios &dirs, char * ruta, directorios &actual);

void BUSCAR_ANTERIOR_HERMANO(directorios & hijo_actual, directorios aux);

void ASOCIAR_HERMANO(directorios & ultimo_hijo, directorios aux);

TipoRet SUBIR_UN_NIVEL (directorios &actual, char * ruta);

int SepararString (char * parametro, char * &padre, char * &new_dir);

void TOKEN (char * ruta, char * &tokenized);

#endif
