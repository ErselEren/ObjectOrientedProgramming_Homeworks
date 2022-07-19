#ifndef GTUVECTOR_H
#define GTUVECTOR_H

#include <iostream>
#include <memory>
#include "GTUIterator.h"
#include "GTUIteratorConst.h"
#include "Iterable.h"

namespace vector_space
{

    template<class T>
    class GTUVector : public Iterable<T>
    {
        public:
            GTUVector();
            GTUVector(const GTUVector<T>& other);
            GTUVector(T&& other);
            GTUVector<T>& operator=(const GTUVector<T> &other);
            GTUVector<T>& operator=(GTUVector<T>&& other);
            void add(const T& _added_value);
            T& operator[](int index);
            bool empty() override;
            size_t size(); 
            void clear() override;
            void erase(GTUIterator<T> position) override;
            void erase(GTUIterator<T> first,GTUIterator<T> last);
            GTUIterator<T> begin() override;
            GTUIterator<T> end() override;
            GTUIteratorConst<T> cbegin() const;
            GTUIteratorConst<T> cend() const;
            ~GTUVector(){}
        private:
            size_t vecSize;
            size_t vecCapacity;
            shared_ptr<T> vecPtr;
    };

}
#endif