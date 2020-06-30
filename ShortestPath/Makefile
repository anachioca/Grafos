all: prog

run: prog 
	./prog 

debug: listaencad.o grafo_matriz.o main.o
	gcc -o prog listaencad.o grafo_matriz.o main.o -g
	gdb prog
	
valgrind: prog
	gcc -o prog -g -Wall -ggdb3 *.o -g
	valgrind --leak-check=full --show-leak-kinds=all ./prog < 8.in
	
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
