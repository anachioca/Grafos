all: prog

run: prog
	./prog
	
prog: grafo_matriz.o main.o
	gcc -o prog grafo_matriz.o main.o -g

main.o: main.c
	gcc -c main.c

grafo_matriz.o: grafo_matriz.c
	gcc -c grafo_matriz.c

clean: 
	rm -rf *o prog