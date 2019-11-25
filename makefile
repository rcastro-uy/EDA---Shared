todo: main.o sistema.o directorios.o archivos.o archivo.o contenido.o
	g++ -o main main.o sistema.o directorios.o archivos.o archivo.o contenido.o
main.o: main.c
	g++ -c main.c
sistema.o: sistema.h sistema.c
	g++ -c sistema.c
directorios.o: directorios.h directorios.c
	g++ -c directorios.c
archivos.o: archivos.h archivos.c
	g++ -c archivos.c
archivo.o: archivo.h archivo.c
	g++ -c archivo.c
contenido.o: contenido.h contenido.c
	g++ -c contenido.c
limpiar:
	rm -f main
	rm -f *.o

