all: prog

run: prog
	./prog 
	
prog: listaencad.o grafo_matriz.o main.o
	gcc -o prog listaencad.o grafo_matriz.o main.o -g

main.o: main.c
	gcc -c main.c

grafo_matriz.o: grafo_matriz.c 
	gcc -c grafo_matriz.c

listaencad.o: listaencad.c
	gcc -c listaencad.c

clean: 
	rm -rf *o prog