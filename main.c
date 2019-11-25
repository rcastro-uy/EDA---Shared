#include "sistema.h"
#include <string.h>
#include <stdio.h> 
#include <iostream>
#include <cstring>
#include <stdbool.h>

using namespace std;


int main(){
	Sistema s = CREAR_SISTEMA();
	bool salir = false;
	char * comando = new(char[MAX_COMANDO]);
	char * parametro = new(char[MAX_PARAMETRO]);
	char * parametro1 = new(char[MAX_PARAMETRO]);
	int parametro_num;
	printf("\n\n*\t*\t*\tBienvenido al Matrix File System\t*\t*\t*\nCreadores:\nJuan Ugas\nJuan Rodriguez\nRodrigo Castro\n\nEnjoy!\n\n\n");
	TipoRet retorno;
	
	do{
		cout << "NEO SAYS: $ ";
		cin >> comando;
		if (strcasecmp(comando,"DIR") == 0){
			// Ver lectura parametro tarea 2
			retorno = DIR (s, parametro);
		}else if (strcasecmp(comando,"CREATE") == 0){
			cin >> parametro;
			retorno = CREATE (s, parametro);
		}else if (strcasecmp(comando,"DELETE") == 0){
			cin >> parametro;
			retorno = DELETE (s, parametro);
		}else if (strcasecmp(comando,"UNDELETE") == 0){
			retorno = UNDELETE (s);
		}else if (strcasecmp(comando,"IC") == 0){
			cin >> parametro;
			cin >> parametro1;
			retorno = IC (s, parametro, parametro1);
		}else if (strcasecmp(comando,"IF") == 0){
			cin >> parametro;
			cin >> parametro1;
			if(TIENE_COMILLAS_LARGO_CORRECTO(parametro1))
				retorno = IF (s, parametro, parametro1);
			else
				retorno = ERROR;
		}else if (strcasecmp(comando,"BC") == 0){
			cin >> parametro;
			cin >> parametro_num;
			retorno = BC (s, parametro, parametro_num);
		}else if (strcasecmp(comando,"BF") == 0){
			cin >> parametro;
			cin >> parametro_num;
			retorno = BF (s, parametro, parametro_num);
		}else if (strcasecmp(comando,"CAT") == 0){
			cin >> parametro;
			cin >> parametro1;
			retorno = CAT (s, parametro, parametro1);
		}else if (strcasecmp(comando,"TYPE") == 0){
			cin >> parametro;
			retorno = TYPE (s, parametro);
		}else if (strcasecmp(comando,"MKDIR") == 0){
			cin >> parametro;
			cin >> parametro_num;
			retorno = MKDIR (s, parametro,parametro_num);
		}else if (strcasecmp(comando,"exit") == 0){
			for(int i=0; i < 10000; i++){
				cout << "\t- Desconectando de la Matrix . . .\n\n";
			}
			for(int i=0; i < 100000; i++){
				printf("0101010010101010010101010000011101110111110101010101010");
			}
			salir = true;
			retorno = OK;
		}else if (strcasecmp(comando,"CD") == 0){
			cin >> parametro;
			retorno = CD (s, parametro);
		}else{
			cout << " - Comando Incorrecto.\n\n";
			retorno = ERROR;
		}
		// consumo el resto de la linea
		fgets(parametro, MAX_PARAMETRO, stdin);

		if (retorno == OK)
			cout << " - OK\n\n";
		else if (retorno == ERROR)
			cout << " - ERROR\n\n";
		else
			cout << " - NO IMPLEMENTADA DEL MAIN\n\n";
	}while (!salir);
	
	s = DESTRUIR_SISTEMA ();
	delete [] comando;
	delete [] parametro;
	delete [] parametro1;
}
