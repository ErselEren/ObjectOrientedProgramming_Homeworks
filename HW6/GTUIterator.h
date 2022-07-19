#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include <iostream>
#include <memory>

//typedef std::forward_iterator_tag iterator_category;

template<class IT>
class GTUIterator
{
public:

    using iterator_category = std::random_access_iterator_tag;
    using value_type = IT;
    using difference_type = std::ptrdiff_t;
    using pointer = IT*;
    using reference = IT&;

public:

    GTUIterator(IT* ptr = nullptr){it_ptr = ptr;}
    GTUIterator(const GTUIterator<IT>& rawIterator) = default;
    ~GTUIterator(){}

    GTUIterator<IT>& operator=(const GTUIterator<IT>& rawIterator) = default;
    GTUIterator<IT>& operator=(IT* ptr){it_ptr = ptr;return (*this);}

    operator bool()const
    {
        if(it_ptr) return true;
        else return false;
    }

    bool             operator==(const GTUIterator<IT>& rawIterator)const{return (it_ptr == rawIterator.getConstPtr());}
    bool             operator!=(const GTUIterator<IT>& rawIterator)const{return (it_ptr != rawIterator.getConstPtr());}

    GTUIterator<IT>& operator+=(const difference_type& movement){it_ptr += movement;return (*this);}
    GTUIterator<IT>& operator-=(const difference_type& movement){it_ptr -= movement;return (*this);}
    GTUIterator<IT>& operator++(){++it_ptr;return (*this);}
    GTUIterator<IT>& operator--(){--it_ptr;return (*this);}
    GTUIterator<IT>  operator++(int){auto temp(*this);++it_ptr;return temp;}
    GTUIterator<IT>  operator--(int){auto temp(*this);--it_ptr;return temp;}
    GTUIterator<IT>  operator+(const difference_type& movement){auto oldPtr = it_ptr;it_ptr+=movement;auto temp(*this);it_ptr = oldPtr;return temp;}
    GTUIterator<IT>  operator-(const difference_type& movement){auto oldPtr = it_ptr;it_ptr-=movement;auto temp(*this);it_ptr = oldPtr;return temp;}

    difference_type  operator-(const GTUIterator<IT>& rawIterator){return std::distance(rawIterator.getPtr(),this->getPtr());}

    IT&              operator*(){return *it_ptr;}
    const IT&        operator*()const{return *it_ptr;}
    IT*              operator->(){return it_ptr;}

    IT*              getPtr()const{return it_ptr;}
    const IT*        getConstPtr()const{return it_ptr;}

protected:

    IT*   it_ptr;
};


#endif
