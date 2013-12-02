#include "Digraph.h"
#include <stdexcept>

using namespace std;

//Implementation of WeightedVertex
bool operator<(const WeightedVertex& wv1, const WeightedVertex& wv2)
{
	return wv1.weight < wv2.weight;
}

bool operator>(const WeightedVertex& wv1, const WeightedVertex& wv2)
{
	return wv1.weight > wv1.weight;
}

ostream& operator<<(ostream& out, WeightedVertex& wv)
{
	return out<<'['<<wv.vertex<<'|'<<wv.weight<<']';
}

//Implementation of Digraph
Digraph::Digraph(istream& in)
{
	if(in.fail())
		throw std::runtime_error("In constructor Digraph, input stream is not good");
	else{
		int a, b, v;
		int end = -1;

		//temp values
		a=0;
		b=0;
		v=0;

		if(!in.eof()){
			//finding the initial value for size
			in>>a;
			if(a == end || a < 0){
				throw std::runtime_error("In constructor Digraph, first symbol is negative");
			}
			else{
				V = a;
				E = 0;
				_adj.resize(V+1);
			}
			//loop for finding vertex value
			in>>v;
			while(a!=end || v!=end){
				if(v < -1 || v == 0) throw std::runtime_error("In constructor Digraph, vertex symbol is negative");
				//loop for the adj. vertexes and weights
				else{
					//reset a
					a=0;
					while(a!=end){
						in>>a>>b;
						//cout<<"adj vertex, weight = "<<a<<","<<b<<endl
							//<<"with source = "<<v<<endl;
						if(a!=end)	
							addEdge(a, b, v);
					}
					//reached end of one vertex
					if(a=end){
						v = b;
					}
				}
			}
		}	
	}
}

void Digraph::addEdge(WeightedVertex wv, int v)
{
	if(v>size() || v<1){
		throw runtime_error("In Digraph::addEdge(..), vertex index is out of bounds");
	}
	else{
		//cout<<"vertex is "<<v<<", size() is "<<size()<<endl;
		_adj[v].push_back(wv);
		E++;
	}
}

void Digraph::addEdge(int v, int w, int source)
{
	WeightedVertex wv(v,w);
	addEdge(wv, source);
}

std::list<WeightedVertex> Digraph::getAdj(int v)
{
	if (v > size() || v < 1) //note we don't use 0 here
		throw runtime_error("In Digraph::getAdj(..), vertex index is out of bounds");

	else 
		return _adj[v];
}

ostream& operator<<(ostream& out, Digraph& g)
{
	for(int i=1; i< g.size(); i++){
		out<<"vertex "<<i<<": ";
		list<WeightedVertex> temp = g.getAdj(i);
		for(auto j = temp.begin(); j != temp.end(); j++){
			out<<(*j)<<" ";
		}
		out<<endl<<endl;
	}
	return out;
}