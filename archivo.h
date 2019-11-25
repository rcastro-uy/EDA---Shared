#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "definiciones.h"

typedef struct nodo_archivo * archivo;


archivo CREAR_ARCHIVO(char * nombre, char * extension);
// Crea el archivo nombre.extension.

void IMPRIMIR_ARCHIVO(archivo a);
// Imprime el nombre extension y tamaño del archivo en la salida estandar.

int QUOTA_ARCHIVO (archivo a);

bool SOY_ARCHIVO(archivo a, char * nombre, char * extension);
// Retorna true si a tiene el nombre y la extension pasados como parametro, false en caso contrario.

char * NOMBRE_ARCHIVO(archivo a);
// Retorna el nombre del archivo.

char * EXTENSION_ARCHIVO(archivo a);
// Retorna el nombre del archivo.

TipoRet INSERTAR_LINEA_ARCHIVO (archivo &a, char * texto, int cota, int &dir_size);

TipoRet IMPRIMIR_ARCHIVO_ARCHIVO (archivo a);

#endif