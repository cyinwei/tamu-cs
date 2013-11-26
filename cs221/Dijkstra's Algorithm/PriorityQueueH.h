/*
  Heap implementation with locators (kinda dumb for this...)
  For Dr. Leyk's CSCE 221 Autumn 2013 course.

  Author: Yinwei Zhang
  Date: 14.11.2013
  Time Taken: 3:55-
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "Locator.h"

//class PriorityQueueH, heap based implementation
//------------------------------------------------------------------------------
template<class T>
class PriorityQueueH{
 private:
  std::vector<Item<T> > _heap;
  
 public:
  //constructor
  PriorityQueueH(int size=0) { _heap.reserve(size);}
  
  //operations
  void insert(const Item<T>& elem);
  void insert(int key=-1, const T& elem=T(), Locator* l=nullptr);

  Locator min(); //returns min locator, does not modify heap
  void remove(Locator loc); //updates node, removes element at locator

  void decreaseKey(Locator loc, T k); //decreases index by k

  //T popMin();

  int size() const{ return _heap.size();}
  bool isEmpty(){return _heap.size()==0;}

  //access to _heap for locator to access its data
  std::vector<Item<T> > getHeap() const{return _heap;}

 private:
  void cleanLocs(); //makes sure every location is their array spot. used for shifts
  void _shiftDown(int node);
  void _shiftUp(int node);
};

PriorityQueueH<int> createPriorityQueueH(std::string filename, Locator locArray); 
template<class T>
std::ostream& operator<<(std::ostream& out, PriorityQueueH<T>& pq);

//Implementation of PriorityQueueH, array based implementation
//------------------------------------------------------------------------------

template<class T>
void PriorityQueueH<T>::insert(const Item<T>& elem)
{
  _heap.push_back(elem);
  _shiftUp(_heap.size()-1);
  cleanLocs();
}

template<class T>
void PriorityQueueH<T>::insert(int key, const T& elem, Locator* l)
{
  Item<T> t(key,elem,l);
  insert(t);
}

template<class T>
Locator PriorityQueueH<T>::min()
{
  Item<T> result = _heap.front();
  return *(result.getLoc());
}

template<class T>
void PriorityQueueH<T>::remove(Locator loc)
{
  if(!isEmpty() && loc.getIndex() < _heap.size()){
    std::swap(_heap[loc.getIndex()], _heap.back()); //gets rid of front element
    _heap.pop_back(); //remove duplicate
    _heap.front().getLoc()->changeIndex(0);
    _shiftDown(loc.getIndex()); //might want to start at the top? I think this still works tho
  }
  cleanLocs();
}

template<class T>
void PriorityQueueH<T>::cleanLocs()
{
  for (int i=0; i<_heap.size(); i++){
    if(_heap[i].getLoc() != nullptr)
      _heap[i].getLoc()->changeIndex(i);
  }
}

template<class T>
void PriorityQueueH<T>::_shiftDown(int node)
{
  int left_child = node*2+1;
  int right_child = node*2+2;

  int replace = node;
  if(right_child < _heap.size()){
    bool left = _heap[left_child].getKey() < _heap[right_child].getKey();
    if(left && _heap[left_child].getKey() < _heap[node].getKey()) //left is the smallest 
      replace = left_child;
    else if(!left && _heap[right_child].getKey() < _heap[node].getKey()) //right is the smallest
      replace = right_child;
  }
  else if(left_child < _heap.size()){
    if(_heap[left_child].getKey() < _heap[node].getKey()) //left is smaller
      replace = left_child;
  }
  if(replace == node) return;//node is external; has no children

  else{
    std::swap(_heap[node], _heap[replace]);
    _shiftDown(replace);
  }
}

template<class T>
void PriorityQueueH<T>::_shiftUp(int node)
{
  if(node==0){
    _heap[0].getLoc()->changeIndex(0); //updates index
    return; //can't shift root up
  }
  
  else{
    int parent = std::floor(double(node-1)/2.0);
    if(_heap[parent].getKey() < _heap[node].getKey()) return; //parent is less than child, do nothing 
    
    else {
      std::swap(_heap[node], _heap[parent]);
      _shiftUp(parent);
    }
  }
}

template<class T>
void PriorityQueueH<T>::decreaseKey(Locator loc, T key)
{
  _heap[loc.getIndex()].changeKey(_heap[loc.getIndex()].getKey()-key);
  _shiftUp(loc.getIndex());
}


PriorityQueueH<int> createPriorityQueueH(std::string filename, std::vector<Locator> locArray)
{
  PriorityQueueH<int> pq;

  std::ifstream in(filename.c_str());
  if(!in.is_open()) throw std::runtime_error("Cannot find file.");
 
  int counter = 0;
  int x, y, a, b;
  while(in.good() && !in.eof()){
    //hold test against last element
    x = a;
    y = b;

    in>>x>>y;
    if(!(x==a && y==b)){
      if(counter >= locArray.size()) locArray.push_back(Locator());
      else{
	pq.insert(x, y, &locArray[counter]);
      }
	counter++;
    }
  }
  in.close();
  return pq;
}

template<class T>
std::ostream& operator<<(std::ostream& out, PriorityQueueH<T>& pq)
{
  //for(int i=0; i<pq.getHeap().size(); i++)
  //out<<pq.getHeap()[i].getKey()<<" "<<pq.getHeap()[i].getElem()<<std::endl;
  
  //EMPTYS PQ!!!!
  Locator loc;
  while (!pq.isEmpty()) {
    loc=pq.min();
    //T elem = pq.getHeap()[loc.getIndex()].getElem(); //ostream doesn't like if I straight input it...
    //okay when I type the definition straight into out I get a segfault... wtf? ??? ???????
    int index = loc.getIndex();
    out<<pq.getHeap()[index]<<std::endl;
    pq.remove(loc);
  }
 
  return out;
}
