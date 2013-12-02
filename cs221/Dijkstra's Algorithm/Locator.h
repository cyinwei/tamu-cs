#ifndef LOCATOR
#define LOCATOR
/*
  Locator class used for a faster implementation of priority queue
  Taken from assignment page.
    :http://courses.cs.tamu.edu/teresa/csce221/pdf/221-13c-A5.pdf
  For: Dr. Leyk's CSCE 221 class

  Author: Yinwei Zhang
  Date: 12.11.2013
  Time Taken: 9:13-9:35pm
*/

#include <iostream>

class Locator;

template<class T>
class Item{
 private:
  T elem;
  Locator* locPtr;
 public:
 Item(const T& e=T(), Locator* l=nullptr):
  elem(e), locPtr(l) {}

  T getElem() const {return elem;}
  Locator* getLoc() const {return locPtr;}

  void setElem(const T& e) {elem = e;}
  void setLoc(Locator* l) {locPtr = l;} 
};

template<class T>
std::ostream& operator<<(std::ostream& out, Item<T> item);

template<class T>
bool operator<(Item<T> e1, Item<T> e2);

template<class T>
bool operator>(Item<T> e1, Item<T> e2);

//-------------------------------------------------------------------
class Locator{
 private:
  int index;
 public:
 Locator(int i=-1):
  index(i) {}

  int getIndex(){ return index; }
  void setIndex(int e){ index = e; }

};


//Implementations

template<class T>
std::ostream& operator<<(std::ostream& out, Item<T> item)
{
  out<<item.getElem();
}

template<class T>
bool operator<(Item<T> e1, Item<T> e2)
{
  return e1.getElem() < e2.getElem();
}

template<class T>
bool operator>(Item<T> e1, Item<T> e2)
{
  return e1.getElem() > e2.getElem();
}

#endif  
