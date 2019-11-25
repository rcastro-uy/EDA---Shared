#ifndef SISTEMA_H
#define SISTEMA_H

#include "definiciones.h"

typedef struct nodo_sistema * Sistema;

Sistema CREAR_SISTEMA ();
// Crea un Sistema de Archivos Nuevo.
// Al crearlo no tiene ningun archivo o directorio (solo el raiz).

TipoRet DIR (Sistema &s, string parametro);
// Muestra el contenido del directorio actual.
// Siempre retorna OK.

TipoRet CREATE (Sistema &s, string nombreArchivo);
// Crea  un  nuevo  archivo  vacío en  el directorio 
// especificado  por  su ruta (relativa o absoluta).
// Retorna OK si el archivo pudo ser creado exitosamente.
// Retorna ERROR si ya existe un archivo con ese nombre
// completo en el directorio actual.

TipoRet DELETE (Sistema & s, string nombreArchivo);
// Elimina un archivo del Sistema de Archivos. El archivo
// a ser borrado puede ser especificado mediante una ruta relativa
// o absoluta.
// Retorna OK si se pudo eliminar el archivo exitosamente.
// Retorna ERROR si no existe un archivo con ese nombre en
// el directorio  actual.

TipoRet UNDELETE (Sistema &s);
// Recupera  el  último  archivo  eliminado en  el  sistema
// mediante  el  comando DELETE (si  hay  al  menos  uno,  sino
// no  tiene  efecto).
// Retorna OK si se pudo recuperar el archivo exitosamente.
// Retorna ERROR si no existe el archivo a recuperar.

TipoRet IC (Sistema &s, string nombreArchivo, string texto);
// Inserta  una  línea  al  comienzo  del  texto  del archivo
// nombreArchivo  (la  información  a  insertar debe ir entre comillas (“),
// el texto a su vez no podrá contener ese caracter).
// Recordar que si un directorio está acotado, su tamaño máximo no
// puede ser excedido
// Retorna OK si se pudo insertar el texto al final del archivo.
// Retorna ERROR si no existe un archivo con ese nombre en el directorio
// actual o Si la línea a insertar no está entre comillas o si  no  se
// pudo insertar  el  texto  por  superar  el  largo  máximo establecido.

TipoRet IF (Sistema &s, string nombreArchivo, string texto);
// Inserta una línea al final del texto del archivo nombreArchivo.
// (vale la misma acotación que para el comando IC).
// Retorna OK si se pudo insertar el texto al final del archivo.
// Retorna ERROR si no existe un archivo con ese nombre en el directorio
// actual o si la línea a insertar no está entre comillas o si no se  pudo
// insertar  el  texto  por  superar  el  largo  máximo establecido.

TipoRet BC (Sistema &s, string nombreArchivo, int k);
// Borra, a lo sumo, las k primeras líneas de texto del archivo
// nombreArchivo. Si el texto tiene k o menos líneas, éste queda vacío.
// Retorna OK si  se  pudieron  eliminar  las  a  lo  sumo  k  primeras
// líneas  del archivo  parámetro,  aún  cuando  k  fuera  mayor  o  igual
// a  la cantidad  de  líneas  del  archivo  en  cuestión  (en  cuyo  caso
// el contenido quedaría vacío).
// Retorna ERROR si no existe un archivo con ese nombre en el directorio
// actual. 

TipoRet BF (Sistema &s, string nombreArchivo, int k);
// Borra, a lo sumo, las k últimas líneas de texto del archivo nombreArchivo.
// Si el texto tiene k o menos líneas, éste queda vacío.
// Retorna OK si  se  pudieron  eliminar  las  a  lo  sumo  k  últimas
// líneas  del archivo  parámetro,  aún  cuando  k  fuera  mayor  o  igual
// a  la cantidad  de  líneas  del  archivo  en  cuestión  (en  cuyo  caso
// el contenido quedaría vacío).
// Retorna ERROR si no existe un archivo con ese nombre en el directorio
// actual. 

TipoRet CAT (Sistema &s, string nombreArchivo1, string nombreArchivo2);
// Concatena  el archivo nombreArchivo2  a  continuación  del archivo
// nombreArchivo1, dejando el contenido del archivo resultante en
// nombreArchivo1. El archivo nombreArchivo2 no se modifica.
// Recordar que si un directorio está acotado, su tamaño máximo no
// puede ser excedido.
// Retorna OK si se pudieron concatenar los archivos.
// Retorna ERROR si  no  existe  un  archivo  con  nombreArchivo1  en  el
// directorio actual o si  no  existe  un  archivo nombreArchivo2  en  el
// directorio actual.

TipoRet TYPE (Sistema &s, string nombreArchivo);
// Muestra  por  pantalla  el  contenido  de nombreArchivo.  Cada  línea
// del archivo se desplegará en una línea nueva en la pantalla.
// Retorna OK si  se  pudo  mostrar  el  contenido  del  archivo  (aún
// cuando  éste fuere nulo).
// Retorna ERROR si no existe un archivo con ese nombre en el directorio
// actual.

TipoRet MKDIR (Sistema &s, string nombreDirectorio, int cota);

TipoRet CD (Sistema &s, char * ruta);

Sistema DESTRUIR_SISTEMA ();
// Destruye el sistema de archivos y libera la memoria asociada.

bool TIENE_COMILLAS(char * nombreArchivo);

bool TIENE_COMILLAS_LARGO_CORRECTO(char * a);

int END_QUOTES(char * str);

bool ES_SUBIR (char * ruta);

bool ES_RUTA_RELATIVA(char * nombreDirectorio);

#endif
