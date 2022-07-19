#ifndef GTUGTUArray_H
#define GTUGTUArray_H

#include <iostream>
#include <memory>
#include "GTUIterator.h" //non-const iterator header
#include "GTUIteratorConst.h" //const iterator header
#include "Iterable.h"

namespace array_space
{
    //Custom Array Class
    template <class T, int SIZE> //T is type of array and SIZE is fixed size of array
    class GTUArray : public Iterable<T> //derived from Iterable class
    {
        public:
            GTUArray(); //constructor
            ~GTUArray(); //destructor
            T& operator[](int index);
            T& at(int index);
            const T& front();
            const T& back();
            bool empty();
            size_t size();
            void clear();
            GTUIterator<T> begin();
            GTUIterator<T> end();
            GTUIteratorConst<T> cbegin() const; //const begin iterator
            GTUIteratorConst<T> cend() const;
            void erase(GTUIterator<T> position){} //body is empty, because there is no erase in arrays
        private:  
            shared_ptr<T> ArrPtr;
            int ArrSize;
    };

}

#endif