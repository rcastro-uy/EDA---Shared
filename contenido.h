#ifndef CONTENIDO_H
#define CONTENIDO_H

#include "definiciones.h"
typedef struct nodo_contenido * contenido;


contenido CREAR_CONTENIDO();
// Crea el contenido vacio.

void INSERTAR_LINEA_CONTENIDO_IF (contenido &c, char * texto);

TipoRet IMPRIMIR_ARCHIVO_CONTENIDO(contenido c);

bool isEmptyLinea (char * a);

bool EXISTE_CONTENIDO(contenido c);

contenido IMPLEMENTAR_CONTENIDO();
//Crea las estruturas internas del contenido
#endif
