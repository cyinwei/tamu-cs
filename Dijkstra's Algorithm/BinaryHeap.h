/*
  Implementation of Binary Heap using templates.  Based on slides from class
    :http://courses.cs.tamu.edu/teresa/csce221/pdf-lectures-print/priority-queue-4.pdf
  Also used Igushev's implementation
    :http://igushev.com/implementations/binary-heap-cpp/
  For Dr. Leyk's CSCE 221 Autumn 2013, Assignment 5.

  Author: Yinwei Zhang
  Date: 12.11.2013
  Time taken: 6:46-9:11PM
*/

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <vector>
#include <cmath>
#include <algorithm>

template<class T>
class BinaryHeap{
 private:
  std::vector<T> _heap;
  
 public:
  //constructor
  BinaryHeap(int size=0) { _heap.reserve(size);}
  
  //operations
  void insert(const T& elem);
  T popMin();

  int size() const{ return _heap.size();}

  void buildHeap();

 private:
  void _shiftDown(int node);
  void _shiftUp(int node);
};

template<class T>
void BinaryHeap<T>::insert(const T& elem)
{
  _heap.push_back(elem);
  _shiftUp(_heap.size()-1);
}

template<class T>
T BinaryHeap<T>::popMin()
{
  T result = _heap.front();
  _heap.front() = _heap.back(); //gets rid of front element
  _heap.pop_back(); //remove duplicate
  _shiftDown(0);
  return result;
}

template<class T>
void BinaryHeap<T>::buildHeap()
{
  for(int i = _heap.size()/2; i>=0; --i)
    _shiftDown(i);
}

template<class T>
void BinaryHeap<T>::_shiftDown(int node)
{
  int left_child = node*2+1;
  int right_child = node*2+2;

  int replace = node;
  if(right_child < _heap.size()){
    bool left = _heap[left_child] < _heap[right_child];
    if(left && _heap[left_child] < _heap[node]) //left is the smallest 
      replace = left_child;
    else if(!left && _heap[right_child] < _heap[node]) //right is the smallest
      replace= right_child;
  }
  else if(left_child < _heap.size()){
    if(_heap[left_child] < _heap[node]) //left is smaller
      replace = left_child;
  }
  if(replace == node) return;//node is external; has no children

  else{
    std::swap(_heap[node], _heap[replace]);
    _shiftDown(replace);
  }
}

template<class T>
void BinaryHeap<T>::_shiftUp(int node)
{
  if(node==0) return; //can't shift root up
  
  else{
    int parent = std::floor(double(node-1)/2.0);
    if(_heap[parent] < _heap[node]) return; //parent is less than child, do nothing 
    
    else {
      std::swap(_heap[node], _heap[parent]);
      _shiftUp(parent);
    }
  }
}

#endif
