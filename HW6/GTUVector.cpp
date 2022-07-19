#include <iostream>
#include <memory>
#include <algorithm>
#include "GTUVector.h"

namespace vector_space
{


template <class T> // constructor
GTUVector<T>::GTUVector() : vecSize(0){ }

template <class T> //constructor
GTUVector<T>::GTUVector(T&& other){ }

//------------------------------------------------------const düzenlemesi yapılacak
template <class T> //constructor 
GTUVector<T>::GTUVector(const GTUVector<T>& other){ 
    GTUVector<T> newVec;
    GTUIteratorConst<T> it;
    for(it = other.cbegin();it!=other.cend();it++)
        newVec.add((*it));

    vecPtr = nullptr;
    vecPtr = newVec.vecPtr;
    vecSize = other.vecSize;
}

template <class T> //assignment operator
GTUVector<T>& GTUVector<T>::operator=(GTUVector<T>&& other){ return *this; }

//-----------------------------------------------------------------parametre const yapılacak. iterator const iterator döndürecek
template <class T> //assignment operator
GTUVector<T>& GTUVector<T>::operator=(const GTUVector<T> &other){ 
    GTUVector<T> newVec;
    GTUIteratorConst<T> it;
    for(it = other.cbegin();it!=other.cend();it++)
        newVec.add((*it));

    vecPtr = nullptr;
    vecPtr = newVec.vecPtr;
    vecSize = other.vecSize;
    return *this;
}

template <class T> //returns size of vector
size_t GTUVector<T>::size(){ return vecSize;}

template <class T> //returns begin iterator
GTUIterator<T> GTUVector<T>::begin(){
    return GTUIterator<T>(vecPtr.get());
}

template <class T> //returns end iterator
GTUIterator<T> GTUVector<T>::end(){
    return GTUIterator<T>(vecPtr.get() + vecSize);
}

template <class T> //returns const begin iterator
GTUIteratorConst<T> GTUVector<T>::cbegin() const{
    return GTUIteratorConst<T>(vecPtr.get());
}

template <class T> //returns const end iterator
GTUIteratorConst<T> GTUVector<T>::cend() const{
    return GTUIteratorConst<T>(vecPtr.get() + vecSize);
}

template <class T> //returns true if vector is empty
bool GTUVector<T>::empty(){
    if(vecSize==0) return true; //return 1 if it is empty
    return false; //return 0 if it is not empty
}

template <class T> //overloaded [] operator and returns element reference
T& GTUVector<T>::operator[](int index)
{
    // if given index is greater than the
	// size of vector print Error
	if (index >= vecSize) {
		cout << "Error: vecPtray index out of bound";
		exit(0);
	}

	// else return value at that index
	return vecPtr.get()[index];
}

template<class T> //adds new element to vector
void GTUVector<T>::add(const T& _added_value){
   // cout << "\n|vecSize : "<<vecSize<<endl;
    
    shared_ptr<T> old ( new T[vecSize+1] );

    for(int i=0;i<vecSize;i++) old.get()[i] = vecPtr.get()[i];
    
    old.get()[vecSize] = _added_value;
    vecPtr = nullptr;
    vecPtr = old;
    vecSize++;
    
}

template<class T> //clears vector
void GTUVector<T>::clear(){
    shared_ptr<T> old = nullptr;
    vecPtr = old;
    vecSize = 0;
}


template<class T> //
void GTUVector<T>::erase(GTUIterator<T> position){

    GTUVector<T> newVec;
    GTUIterator<T> it;
    for(it = begin();it!=end();it++)
        if(it != position) newVec.add((*it));

    
    vecSize = newVec.size();
    vecPtr = newVec.vecPtr;   
}

template<class T> //
void GTUVector<T>::erase(GTUIterator<T> first,GTUIterator<T> last){

    GTUVector<T> newVec;
    GTUIterator<T> it;
    for(it = begin();it!=first;it++)
        newVec.add((*it));
    
    for(it = last;it!=end();it++)
        newVec.add((*it));    

    
    vecSize = newVec.size();
    vecPtr = newVec.vecPtr;   
}

//iterator erase (const_iterator first, const_iterator last); bunu overloadla


}