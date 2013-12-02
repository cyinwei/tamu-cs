
#ifndef HEAP
#define HEAP

/*
  Heap implementation with locators
  For Dr. Leyk's CSCE 221 Autumn 2013 course.

  Author: Yinwei Zhang
  Date: 14.11.2013, updated on 1.12.2013
  Time Taken: 3:55-... updated 12AM-2AM
*/

#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stdexcept>  

#include "Locator.h"

template<class T>
class Heap{
 private:
  std::vector<Item<T> > _heap;
  int RemoveComp;
  int DecreaseComp;
  
 public:
  //constructor
  Heap(int size=0) { _heap.reserve(size); RemoveComp=0; DecreaseComp=0;}
  
  //operations
  void insert(const Item<T>& elem);
  void insert(const T& elem=T(), Locator* l=nullptr);

  Locator minLoc(); //returns min locator, does not modify heap
  void remove(Locator& loc); //updates node, removes element at locator

  void changeElem(Locator loc, const T& k); //change the elements amount to k, updates

  T popMin();

  int size() const{ return _heap.size();}
  int getRemoveCount() const{return RemoveComp;}
  int getDecreaseCount() const{return DecreaseComp;}
  bool isEmpty(){return _heap.size()==0;}

  //access to _heap for locator to access its data
  std::vector<Item<T> > getHeap() const{return _heap;}

 private:
  //Note: due to the (dumb) requirement, we have to know the number of comparisons for remove and decrease..
  //So I pass an int: -1 = do nothing
  //                   0 = decrease key (false for isRemove)
  //                   1 = remove (true)
  void _update(); //makes sure every location is their array spot. used for shifts
  void _shiftDown(int node, int isRemove);
  void _shiftUp(int node, int isRemove);
};

template<class T>
std::ostream& operator<<(std::ostream& out, Heap<T>& pq);

//Implementation of Heap, array based implementation
//------------------------------------------------------------------------------

template<class T>
void Heap<T>::insert(const Item<T>& elem)
{
  _heap.push_back(elem);
  _shiftUp(_heap.size()-1, -1);
  _update();
}

template<class T>
void Heap<T>::insert(const T& elem, Locator* l)
{
  Item<T> t(elem,l);
  insert(t);
}

template<class T>
Locator Heap<T>::minLoc()
{
  if(!isEmpty()){
    Item<T> result = _heap.front();
    return *(result.getLoc());
  } 
}

template<class T>
void Heap<T>::remove(Locator& loc)
{
  if(!isEmpty() && loc.getIndex() < _heap.size()){
    std::swap(_heap[loc.getIndex()], _heap.back()); //gets rid of front element
    _heap.pop_back(); //remove duplicate

    //compares with parent and decides on shift (should always shift down heres)
    //parent can be -1 if index =0 , have to check
    int parent = std::floor(double(loc.getIndex()-1)/2.0);

    if(_heap[loc.getIndex()] < _heap[parent] && parent >= 0){
      _shiftUp(loc.getIndex(), 1); 
    }
    else
      _shiftDown(loc.getIndex(), 1);
  }
  _update();
  loc.setIndex(-1); //used to tell that this locator is invalid now
}

template<class T>
T Heap<T>::popMin()
{
  Locator loc = minLoc();
  Item<T> output = _heap[loc.getIndex()];
  remove(*(output.getLoc()));
  return output.getElem();
}

template<class T>
void Heap<T>::changeElem(Locator loc, const T& key)
{
  if(loc.getIndex() >= 0 || loc.getIndex() > _heap.size()){
    _heap[loc.getIndex()].setElem(key);
    //compares with parent and decides on shift (should always shift down heres)
    //parent can be -1 if index =0 , have to check
    int parent = std::floor(double(loc.getIndex()-1)/2.0);

    if(_heap[loc.getIndex()] < _heap[parent] && parent >= 0)
      _shiftUp(loc.getIndex(), 0); 
    
    else
      _shiftDown(loc.getIndex(), 0);
  
    _update();
  }
  else{
   std::cout<<"at this point, locator index is "<<loc.getIndex()<<std::endl
            <<"with size "<<size()<<std::endl;  
   throw std::runtime_error("In Heap<T>::setElem(..) Locator index is out of bounds");  
  }
}

template<class T>
void Heap<T>::_update()
{
  for (int i=0; i<_heap.size(); i++){
    if(_heap[i].getLoc() != nullptr)
      _heap[i].getLoc()->setIndex(i);
  }
}

template<class T>
void Heap<T>::_shiftDown(int node, int isRemove)
{
  int left_child = node*2+1;
  int right_child = node*2+2;

  //comparisons
  int comparisons=0;

  int replace = node;
  if(right_child < _heap.size()){
    comparisons++;

    bool left = _heap[left_child] < _heap[right_child];
    if(left && _heap[left_child] < _heap[node]){ //left is the smallest 
      replace = left_child;
      comparisons++;
    }
    else if(!left && _heap[right_child] < _heap[node]){ //right is the smallest
      replace = right_child;
      comparisons++;
    }  
  }
  else if(left_child < _heap.size()){
    comparisons++;
    if(_heap[left_child] < _heap[node]){ //left is smaller
      replace = left_child;
      comparisons++;
    }
  }
  if(replace == node){
    if(isRemove==0) DecreaseComp+=comparisons;
    else if(isRemove==1) RemoveComp+=comparisons;

    return;//node is external; has no children
  }

  else{
    if(isRemove==0) DecreaseComp+=comparisons;
    else if(isRemove==1) RemoveComp+=comparisons;

    std::swap(_heap[node], _heap[replace]);
    _shiftDown(replace, isRemove);
  }
}

template<class T>
void Heap<T>::_shiftUp(int node, int isRemove)
{
  int comparisons=0;

  if(node==0){
    return; //can't shift root up
  }
  
  else{
    int parent = std::floor(double(node-1)/2.0);
    if(_heap[parent].getElem() < _heap[node].getElem()){

      comparisons++;
      if(isRemove==0) DecreaseComp+=comparisons;
      else if(isRemove==1) RemoveComp+=comparisons;
      return; //parent is less than child, do nothing 
    } 
    
    else {
      comparisons++;
      if(isRemove==0) DecreaseComp+=comparisons;
      else if(isRemove==1) RemoveComp+=comparisons;

      std::swap(_heap[node], _heap[parent]);
      _shiftUp(parent, isRemove);
    }
  }
}


template<class T>
std::ostream& operator<<(std::ostream& out, Heap<T>& pq)
{
  //for(int i=0; i<pq.getHeap().size(); i++)
  //out<<pq.getHeap()[i].getElem()<<" "<<pq.getHeap()[i].getElem()<<std::endl;
  
  //EMPTYS PQ!!!!
  Locator loc;
  while (!pq.isEmpty()) {
    loc=pq.minLoc();
    //T elem = pq.getHeap()[loc.getIndex()].getElem(); //ostream doesn't like if I straight input it...
    //okay when I type the definition straight into out I get a segfault... wtf? ??? ???????
    int index = loc.getIndex();
    out<<pq.getHeap()[index]<<std::endl;
    pq.remove(loc);
  }
 
  return out;
}

#endif