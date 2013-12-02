CC = g++-4.7 -std=c++11

all: clean Dijkstra-Algorithm remove

Dijkstra-Algorithm: main.o Dijkstra.o Digraph.o 
	$(CC) -o Dijkstra-Algorithm main.o Dijkstra.o Digraph.o

main.o: main.cpp Dijkstra.h 
	$(CC) -c main.cpp

Dijkstra.o: Dijkstra.cpp Dijkstra.h Heap.h Digraph.h 
	$(CC) -c Dijkstra.cpp


Digraph.o: Digraph.cpp Digraph.h 
	$(CC) -c Digraph.cpp

clean:
	rm -f *.o Dijkstra-Algorithm

remove:
	rm -f *.o