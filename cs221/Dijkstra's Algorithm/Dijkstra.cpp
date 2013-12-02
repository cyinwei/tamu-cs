#include "Dijkstra.h"
#include "Digraph.h"
#include <stdexcept>
#include <limits>
#include <stack>

using namespace std;

//VertexContainer implementation
//------------------------------------------------------------------------------------------------------

bool operator<(VertexContainer v1, VertexContainer v2)
{
	return v1.weight < v2.weight;
}

bool operator>(VertexContainer v1, VertexContainer v2)
{
	return v1.weight > v2.weight;
}

ostream& operator<<(ostream& out, VertexContainer v)
{
	return out<<"Vertex ["<<v.vertex<<"] = "<<v.weight<<", with parent ["<<v.parent<<"]"<<endl;
}

//Dijkstra implementation
//-------------------------------------------------------------------------------------------------------
Dijkstra::Dijkstra(Digraph& g, int s)
	:graph(g), source(s), isGraphLoaded(true), isCalculated(false), INF(std::numeric_limits<int>::max())
{
	if(s<1 || s> graph.size()) throw runtime_error("In Dijkstra constructor, source vertex is out of bounds");
	else{
		//setting up other containers
		vertices.resize(graph.size());
		output.resize(graph.size());

		initialQueue(); //sets up heap
		calculate();
	}
}

ostream& Dijkstra::displayDistance(ostream& out, int vertex, bool verbose)
{
	if(isCalculated){
		if(vertex > 0 && vertex < size()){
			out<<"Shortest path from ["<<source<<"] to ["<<vertex<<"] = "<<output[vertex].weight<<
				" with parent ["<<output[vertex].parent<<"]"<<endl;
			if(verbose){ //draws a arrow map of the shortest distance
				int s = vertex;
				stack<VertexContainer> stack; 
				while (s != source){
					stack.push(output[s]);
					s = output[s].parent;
				}
				//we know souce weight is 0, no need to push

				//does the output
				bool isFinish = false;
				int distance;
				VertexContainer fresh, old; //default is 0 for weight

				//Initial stuff
				out<<"Path is: ["<<source<<"]";
				while(!isFinish){
					if(!stack.empty()){
						fresh = stack.top();
						stack.pop();
						distance = fresh.weight - old.weight;
						out<<" --||"<<distance<<"||--> ["<<fresh.vertex<<"]";
						old = fresh; //loop
					}
					else{
						out<<endl;
						isFinish = true;
					} 
				}
			}
			return out;
		}
		else throw runtime_error("In Dijkstra::displayDistance(..), vertex is out of bounds");	
	}
	else throw std::runtime_error("In Dijkstra::displayDistance(..), algorithm isn't calculated yet");
}

void Dijkstra::calculate()
{
	if (!isGraphLoaded) throw runtime_error("In Dijkstra::calculate(), No graph..");
	else if (!isHeapLoaded) throw runtime_error("In Dijkstra::calculate(), Heap not initialized");

	else{
		Locator loc = vertices[source];
		int index = loc.getIndex();
		VertexContainer vc(source, source, 0);

		heap.changeElem(loc, vc);

		while(!heap.isEmpty()){
			VertexContainer minElem = heap.popMin();
			output[minElem.vertex] = minElem;
			relax(minElem.vertex);
		}
		isCalculated = true;
	}
}

void Dijkstra::initialQueue()
{
	if (!isGraphLoaded) throw runtime_error("In Dijkstra::initialQueue() No graph..");
	else {
		for(int i=1; i<graph.size(); i++){
			heap.insert(VertexContainer(i, -1, INF), &vertices[i]);		
		}
		isHeapLoaded = true;
	}
}

void Dijkstra::relax(int s)
//***Assumes heap is already initialized to inf, and output is already initialized.
{
	if(s<1 || s> graph.size()) throw runtime_error("In Dijkstra::relax(..), source vertex is out of bounds");
	else if(!isHeapLoaded) throw runtime_error("In Dijkstra::relax(..), heap is not loaded");

	else {
		list<WeightedVertex> adj = graph.getAdj(s);
		for(auto i=adj.begin(); i!=adj.end(); i++){
			int v = i->vertex;
			Locator currentLocator = vertices[v];
			int index = currentLocator.getIndex();

			if(index != -1){ //Assumes -1 means located element is already removed
				int weight = i->weight;
				int currentWeight = heap.getHeap()[index].getElem().weight;
				int parentWeight = output[s].weight;
			
				if(currentWeight > (parentWeight + weight)){
					VertexContainer vc(v, s, parentWeight+weight);
					heap.changeElem(currentLocator, vc);
				}
			}
		}
	}			
}

std::ostream& operator<<(std::ostream& out, Dijkstra& d)
{
	for(int i=1; i<d.size(); i++){
		d.displayDistance(out, i, false);
	}
}