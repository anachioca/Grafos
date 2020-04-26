all: prog

run: prog
	./prog
	
prog: listaencad.o grafo_lista.o main.o
	gcc -o prog listaencad.o grafo_lista.o main.o -g

main.o: main.c
	gcc -c main.c

grafo_lista.o: grafo_lista.c 
	gcc -c grafo_lista.c

listaencad.o: listaencad.c
	gcc -c listaencad.c

clean: 
	rm -rf *o prog