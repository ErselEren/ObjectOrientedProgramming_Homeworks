#ifndef ITERABLE_H
#define ITERABLE_H

#include <iostream>
#include <memory>
#include "GTUIterator.h"

using namespace std;

template<class T>
class Iterable //base class that inherit vector, set, array classes
{
    public: //pure virtual functions
        virtual bool empty() = 0;
        virtual size_t size() = 0;
        virtual void clear() = 0;
        virtual GTUIterator<T> begin() = 0;
        virtual GTUIterator<T> end() = 0;
        virtual void erase(GTUIterator<T> position) = 0;
        virtual GTUIteratorConst<T> cbegin() const = 0;
        virtual GTUIteratorConst<T> cend() const = 0;     
};


#endif