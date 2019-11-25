#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "definiciones.h"


typedef struct nodo_archivos * archivos;

archivos CREAR_ARCHIVOS();
// Crea el conjunto de archivos vacio.

void IMPRIMIR_ARCHIVOS(archivos as);
// Imprime nombre, extension y tamaño de los archivos pertenecientes al conjunto.

TipoRet CREATE_ARCHIVO_ARCHIVOS(archivos & as, char * nombreArchivo);
// Crea un archivo en el conjunto de archivos.

TipoRet INSERTAR_LINEA_ARCHIVOS (archivos &as, char * nombreArchivo, char * texto, char * extensionArchivo, int cota, int &dir_size);

TipoRet IMPRIMIR_ARCHIVO_ARCHIVOS (archivos as, char * nombreArchivo, char * extensionArchivo);

int CALCULAR_QUOTA (archivos as);




#endif
