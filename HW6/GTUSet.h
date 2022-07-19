#ifndef GTUSET_H
#define GTUSET_H

#include <iostream>
#include <memory>
#include "GTUIterator.h"
#include "GTUIteratorConst.h"
#include "Iterable.h"

namespace set_space
{
    template<class T>
    class GTUSet : public Iterable<T> // set class that derived from base class Iterable
    {
        public:
            //constructors
                GTUSet();
                GTUSet(T&& other);
                GTUSet(const GTUSet<T>& other) = default;
            
            void add(const T& _added_value);
            bool empty() override;
            void clear() override;
            void erase(GTUIterator<T> position);
            void erase(const T& _erased_value);
            void erase (GTUIterator<T> first, GTUIterator<T> last);
            size_t size(); 
            
            //iterators
                GTUIterator<T> begin() override;
                GTUIterator<T> end() override;
                GTUIteratorConst<T> cbegin() const;
                GTUIteratorConst<T> cend() const;
                GTUIterator<T> search(const T& _searched_value);
            GTUSet<T> intersection(GTUSet<T> &other);
            GTUSet<T> union_of(GTUSet<T>& other);
            GTUSet<T>& operator=(const GTUSet<T>&& other);
            GTUSet<T>& operator=(GTUSet<T>& other);
            ~GTUSet(){}
        private:
            size_t setSize;
            size_t setCapacity;
            shared_ptr<T> setPtr;
    };

}
#endif