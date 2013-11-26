#ifndef LOCATOR_H
#define LOCATOR_H

/*
  A wrapper for the adaptable priority queue using vector indexes.  It includes a pointer to the locator and associated functions.
  Author: Yinwei (Charlie) Zhang
  Date: 25.11.2013
  Time taken: 4:56 PM-5:18PM
*/

class Locator{
 private:
  int index;
 public:
 Locator(int i=0):
  index(i) {}
 
  //access functions
  int getIndex() const{return index;}
  void setIndex(int i) {index = i;}

}; 

template <class T> 
class LocatorWrapper{
 private:
  T elem;
  Locator* locPtr;

 public:
 LocatorWrapper(const T& e=T(), Locator* l=nullptr):
  elem(e), locPtr(l) {}

  //access functions
  T getElem() const{return elem;}
  Locator* getLoc() const{return locPtr;}

  void setElem(const T& e=T()) {elem = T;}
  void setLoc(Locator* l=nullptr) {locPtr = l;}
};

template <class T>
void swap(LocatorWrapper<T> a, LocatorWrapper<T> b);

//Definitions
//-----------------------------------------------------------------
template <class T>
swap(LocatorWrapper<T> a, LocatorWrapper<T> b)
{
  int aIndex, bIndex;

  if(a.getLoc()!=nullptr) aIndex = a.getLoc()->getIndex();
  else aIndex= -1; //used to say there is no index 

  if(b.getLoc()!=nullptr) bIndex = b.getLoc()->getIndex();
  else bIndex= -1; //used to say there is no index 
  
  //std::swap clone of T
  T temp = a.getElem();
  a.setElem(b.getElem());
  b.setElem(temp);

  //swaps indexes
  if(aIndex != -1)
    a.getLoc()->setIndex(bIndex);

  if(bIndex != -1)
    b.getLoc()->setIndex(aIndex);

  return;
}

#endif
