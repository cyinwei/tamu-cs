#ifndef DIJKSTRA
#define DIJKSTRA

/*
	Dijkstra's algorithm implementation using a binary heap (with locators) and a graph ADT.
	For Dr. Leyks Autumn 2013 CSCE 221 class.

	Author: Yinwei (Charlie) Zhang
	Date: 1.12.2013
	Time Taken: 11:04AM-

	Explanation:
	The key here is to index the vertices with the same number; I initialize the locator array with the
	vertex number (a hash if you will), and do the same with the output vector.
*/

#include "Heap.h"
#include "Digraph.h"
#include "Locator.h"
#include <iostream>
#include <vector>

class VertexContainer{
public:
	int vertex;
	int parent;
	int weight;

VertexContainer(int v=0, int p=0, int w=0)
	:vertex(v), parent(p), weight(w) {}	
};

bool operator<(VertexContainer v1, VertexContainer v2);
bool operator>(VertexContainer v1, VertexContainer v2);
std::ostream& operator<<(std::ostream& out, VertexContainer v);

//--------------------------------------------------------------
class Dijkstra{
private:
	int source;
	Heap<VertexContainer> heap;
	Digraph graph;

	std::vector<Locator> vertices;
	std::vector<VertexContainer> output;

	//flags
	bool isGraphLoaded;
	bool isHeapLoaded;
	bool isCalculated;

	int INF; //used for initial queue

public:
	Dijkstra(Digraph& g, int source);
	

	//Displays the shortest path of 1 vertex compared to source, and also the vertic(es) required.
	std::ostream& displayDistance(std::ostream& out, int vertex, bool verbose); 

	//comparison gets
	int getRemoveCount(){return heap.getRemoveCount();}
	int getDecreaseCount(){return heap.getDecreaseCount();}
	int getTotalCount(){return getDecreaseCount()+getRemoveCount();}

	int size(){return graph.size();}

private:
	void calculate(); //does all the heavy lifting

	//helpers for calculate
	void initialQueue(); //sets queue up
	void relax(int s);
};

std::ostream& operator<<(std::ostream& out, Dijkstra& d); //outputs ALL the shortest distances

#endif
