all: prog

run: prog
	./prog

valgrind: prog
	gcc -o prog -g -Wall -ggdb3 grafo_lista.o listaencad.o main.o -g
	valgrind --leak-check=full --show-leak-kinds=all ./prog
	
prog: listaencad.o grafo_lista.o main.o
	gcc -o prog listaencad.o grafo_lista.o main.o -g

main.o: main.c
	gcc -c main.c

grafo_lista.o: grafo_lista.c 
	gcc -c grafo_lista.c

listaencad.o: listaencad.c
	gcc -c listaencad.c

zip:
	zip trab.zip *.c *.h Makefile

clean: 
	rm -rf *o prog