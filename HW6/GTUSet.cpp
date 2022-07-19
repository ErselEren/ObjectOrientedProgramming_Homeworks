#include <iostream>
#include <memory>
#include <algorithm>
#include "GTUSet.h"

namespace set_space
{
    template <class T> //constructor
    GTUSet<T>::GTUSet():setSize(0){}

    template <class T>//constructor
    GTUSet<T>::GTUSet(T&& other){}

    template <class T> //checks is set empty or not
    bool GTUSet<T>::empty(){
        if(setSize==0) return true; //return 1 if it is empty
        return false; //return 0 if it is not empty
    }

    template <class T> //adds new element
    void GTUSet<T>::add(const T& _added_value){
        
        for(int i=0;i<setSize;i++)
            if(setPtr.get()[i]== _added_value) return;
        
        
        shared_ptr<T> old ( new T[setSize+1] );

        for(int i=0;i<setSize;i++) old.get()[i] = setPtr.get()[i];
        
        old.get()[setSize] = _added_value;
        setPtr = nullptr;
        setPtr = old;
        setSize++;
        
    }

    template <class T> //returns size of set
    size_t GTUSet<T>::size(){
        return setSize;
    }

    template <class T> //clears set
    void GTUSet<T>::clear(){
        shared_ptr<T> old ( new T[0] );
        setPtr = old;
        setSize = 0;
    }

    template <class T> //returns begin iterator
    GTUIterator<T> GTUSet<T>::begin(){
        return GTUIterator<T>(setPtr.get());
    }

    template <class T> //returns end iterator
    GTUIterator<T> GTUSet<T>::end(){
        return GTUIterator<T>(setPtr.get()+setSize);
    }

    template <class T>//returns iterator of first element
    GTUIteratorConst<T> GTUSet<T>::cbegin()const{
        return GTUIteratorConst<T>(setPtr.get());
    }

    template <class T> //returns iterator of last element
    GTUIteratorConst<T> GTUSet<T>::cend()const{
        return GTUIteratorConst<T>(setPtr.get() + setSize);
    }

    template <class T> //returns intersection set of two set
    GTUSet<T> GTUSet<T>::intersection(GTUSet<T> &other){

        GTUSet<T> temp;
        GTUIterator<T> it1,it2;
        int flag;
        for(it1 = begin(); it1!= end();it1++,flag=0){
            for(it2 = other.begin(); it2!=other.end();it2++){
                if( (*it1) == (*it2) ){
                    flag = 1; 
                    break;
                }
            }
            if(flag == 1){
                temp.add(*it1);
                temp.setSize++;
            }
        }
        
        return temp;
    }

    template<class T> //erases element at given position
    void GTUSet<T>::erase(GTUIterator<T> position){
        GTUSet<T> temp;
        GTUIterator<T> it; 

        for(it=begin();it!=end();it++)
            if(position != it) temp.add((*it));
        
        (*this) = temp;
    }

    template<class T> //erase given element
    void GTUSet<T>::erase(const T& _erased_value){
        GTUSet<T> temp;
        GTUIterator<T> it;
        
        for(it = begin(); it!=end();it++)
            if(_erased_value != (*it)) 
                temp.add((*it));
            
        (*this) = temp;
    }

    template<class T> //erase elements between two elements
    void GTUSet<T>::erase (GTUIterator<T> first, GTUIterator<T> last){
        GTUSet<T> temp;
        GTUIterator<T> it;

        for(it=begin();it!=first;it++)
            temp.add((*it));

        for(it=last;it!=end();it++)
            temp.add((*it));

        (*this) = temp;
    }

    template<class T> //searchs given element and returns iterator
    GTUIterator<T> GTUSet<T>::search(const T& _searched_value){
        GTUIterator<T> it;
        for(it = begin(); it!=end(); it++)
            if(_searched_value == (*it))
                return it;

        return begin();        
    }

    template<class T>//returns union set of two sets
    GTUSet<T> GTUSet<T>::union_of(GTUSet<T>& other){
        GTUSet<T> temp;
        GTUIterator<T> it,it2;
        int flag;
        for(it = begin(); it!=end(); it++) temp.add((*it));

        for(it2 = other.begin(); it2!=other.end(); it2++){
            flag = 0;
            for(it = begin(); it != end(); it++){
                if((*it2)==(*it)){
                    flag = 1;
                    break;
                }
            }
            if(flag==0) temp.add((*it2));
        }
        return temp;
    }

    template<class T> //assignment operator
    GTUSet<T>& GTUSet<T>::operator=(GTUSet<T>& other){
        GTUSet<T> newSet;
        GTUIterator<T> it;
        for(it = other.begin();it!=other.end();it++)
            newSet.add((*it));

        setPtr = nullptr;
        setPtr = newSet.setPtr;
        setSize = other.setSize;
        return *this;

    }

    template<class T> //assignment operator
    GTUSet<T>& GTUSet<T>::operator=(const GTUSet<T>&& other){
        setPtr = nullptr;
        setPtr = other.setPtr;
        setSize = other.setSize;
        return *this;
    }

}