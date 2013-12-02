#ifndef GRAPH
#define GRAPH

/*
  Directed Weighted Graph implementation with adjacency lists.
  For Dr. Leyk's Autumn 2013 CSCE 221 class.

  Author: Yinwei (Charlie) Zhang
  Used Sedgewick's Algorithm's 4th ed. as a reference.

  Date: 1.12.2013
  Time taken: 2:06AM-10:50AM (4 hours of sleep, 1~ hour of rest)
*/

#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>

class WeightedVertex{
public:
  int vertex;
  int weight;

  WeightedVertex(int v=0, int w=0)
  :vertex(v), weight(w) {}
};

bool operator<(const WeightedVertex& wv1, const WeightedVertex& wv2);
bool operator>(const WeightedVertex& wv1, const WeightedVertex& wv2);
std::ostream& operator<<(std::ostream& out, WeightedVertex& wv);

class Digraph{
 private:
  int V; //number of vertices
  int E; //number of edges
  std::vector<std::list<WeightedVertex> > _adj;

 public:
  explicit Digraph(int v)
    :V(v), E(0) {_adj.reserve(v);}

  Digraph(std::istream& in); //constructor that takes in an input file

  int getV() const{return V;}
  int getE() const{return E;}
  int size() const{return _adj.size();} //should be same as V

  void addEdge(WeightedVertex wv, int v);
  void addEdge(int v, int w, int source);

  std::list<WeightedVertex> getAdj(int v);

};

std::ostream& operator<<(std::ostream& out, Digraph& g);

#endif
