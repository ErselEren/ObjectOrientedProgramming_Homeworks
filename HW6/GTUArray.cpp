#include <iostream>
#include <memory>
#include <algorithm>
#include "GTUArray.h"

namespace array_space
{
    //returns element at first index
    template <class T,int SIZE>
    const T& GTUArray<T,SIZE>::front(){
        return *(begin());
    }

    //returns element at last index
    template <class T,int SIZE>
    const T& GTUArray<T,SIZE>::back(){
        return *(end()-1);
    }

    //returns element at given index
    template <class T,int SIZE>
    T& GTUArray<T,SIZE>::at(int index){
        // if given index is greater than the
        // size of arr print Error
        if (index >= ArrSize) {
            cout << "Error: index out of bound";
            exit(0);
        }

        // else return value at that index
        return ArrPtr.get()[index];
    }

    //constructor
    template <class T,int SIZE>
    GTUArray<T,SIZE>::GTUArray()
    {
        shared_ptr<T> newPtr (new T[SIZE]);
        ArrPtr = nullptr;
        ArrPtr = newPtr;
        ArrSize = SIZE;
    }

    //destructor
    template <class T,int SIZE>
    GTUArray<T,SIZE>::~GTUArray(){}

    //returns iterator of first element
    template <class T,int SIZE>
    GTUIterator<T> GTUArray<T,SIZE>::begin(){
        return GTUIterator<T>(ArrPtr.get());
    }

    //returns iterator of last element
    template <class T,int SIZE>
    GTUIterator<T> GTUArray<T,SIZE>::end(){
        return GTUIterator<T>(ArrPtr.get() + ArrSize);
    }

    //returns iterator of first element
    template <class T,int SIZE>
    GTUIteratorConst<T> GTUArray<T,SIZE>::cbegin()const{
        return GTUIteratorConst<T>(ArrPtr.get());
    }

    //returns iterator of last element
    template <class T,int SIZE>
    GTUIteratorConst<T> GTUArray<T,SIZE>::cend()const{
        return GTUIteratorConst<T>(ArrPtr.get() + ArrSize);
    }

    //returns element at given index
    template <class T,int SIZE>
    T& GTUArray<T,SIZE>::operator[](int index){
        // if given index is greater than the
        // size of arr print Error
        if (index >= ArrSize) {
            cout << "Error: index out of bound";
            exit(0);
        }

        // else return value at that index
        return ArrPtr.get()[index];
    }

    //returns true if array is empty
    template <class T,int SIZE>
    bool GTUArray<T,SIZE>::empty(){
        if(ArrSize==0) return true;
        return false;
    }

    //makes array size 0 and null its pointer
    template <class T,int SIZE>
    void GTUArray<T,SIZE>::clear(){
        ArrPtr = nullptr;
        ArrSize = 0;
    }

    //returns size of array
    template<class T,int SIZE>
    size_t GTUArray<T,SIZE>::size(){
        return ArrSize;
    }


}