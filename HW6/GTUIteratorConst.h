#ifndef GTUIteratorConst_H
#define GTUIteratorConst_H

#include <iostream>
#include <memory>

//typedef std::forward_iterator_tag iterator_category;

template<class IT>
class GTUIteratorConst
{
    public:

        using iterator_category = std::random_access_iterator_tag;
        using value_type = IT;
        using difference_type = std::ptrdiff_t;
        using pointer = IT*;
        using reference = IT&;


        GTUIteratorConst(IT* ptr = nullptr){iterator_ptr = ptr;}
        GTUIteratorConst(const GTUIteratorConst<IT>& rawIterator) = default;
        ~GTUIteratorConst(){}

        GTUIteratorConst<IT>& operator=(const GTUIteratorConst<IT>& rawIterator) = default;
        const GTUIteratorConst<IT>& operator=(IT* ptr){iterator_ptr = ptr;return (*this);}

        operator bool()const
        {
            if(iterator_ptr) return true;
            else return false;
        }

        bool    operator==(const GTUIteratorConst<IT>& rawIterator)const{return (iterator_ptr == rawIterator.getConstPtr());}
        bool    operator!=(const GTUIteratorConst<IT>& rawIterator)const{return (iterator_ptr != rawIterator.getConstPtr());}

        const GTUIteratorConst<IT>& operator+=(const difference_type& movement){iterator_ptr += movement;return (*this);}
        const GTUIteratorConst<IT>& operator-=(const difference_type& movement){iterator_ptr -= movement;return (*this);}
        const GTUIteratorConst<IT>& operator++(){++iterator_ptr;return (*this);}
        const GTUIteratorConst<IT>& operator--(){--iterator_ptr;return (*this);}
        const GTUIteratorConst<IT>  operator++(int){auto temp(*this);++iterator_ptr;return temp;}
        const GTUIteratorConst<IT>  operator--(int){auto temp(*this);--iterator_ptr;return temp;}
        const GTUIteratorConst<IT>  operator+(const difference_type& movement){auto oldPtr = iterator_ptr;iterator_ptr+=movement;auto temp(*this);iterator_ptr = oldPtr;return temp;}
        const GTUIteratorConst<IT>  operator-(const difference_type& movement){auto oldPtr = iterator_ptr;iterator_ptr-=movement;auto temp(*this);iterator_ptr = oldPtr;return temp;}

        const difference_type  operator-(const GTUIteratorConst<IT>& rawIterator){return std::distance(rawIterator.getPtr(),this->getPtr());}

        const IT&      operator*(){return *iterator_ptr;}
        const IT&      operator*()const{return *iterator_ptr;}
        const IT*      operator->(){return iterator_ptr;}

        const IT*      getPtr()const{return iterator_ptr;}
        const IT*      getConstPtr()const{return iterator_ptr;}

    protected:

        IT*   iterator_ptr;
};


#endif
