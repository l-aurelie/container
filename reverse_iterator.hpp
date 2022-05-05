#pragma once

#include "iterator_traits.hpp"
#include "vector_iterator.hpp"

namespace ft
{
    template <class Iterator>
    class reverseIterator 
    {
    public:

        typedef Iterator    iterator_type;
        typedef typename iterator_traits<Iterator>::value_type      value_type;
        typedef typename iterator_traits<Iterator>::value_type*     pointer;
        typedef typename iterator_traits<Iterator>::value_type&     reference;
    	typedef typename iterator_traits<Iterator>::difference_type difference_type;
    	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;

    public:
        
	    reverseIterator() : _ptr(NULL) {}
        explicit reverseIterator(iterator_type x) : _ptr(x) {}
        template<class U>
        reverseIterator(const reverseIterator<U>& src) : _ptr(src.base()) {}
	    ~reverseIterator() {}
//        operator reverseIterator<vectorIterator<value_type const> >() const {return reverseIterator<vectorIterator<value_type const> >(_ptr); }
//        operator reverseIterator<vectorIterator<value_type> >() {return reverseIterator<vectorIterator<value_type> >(_ptr); }

        template<class U>
        reverseIterator& operator=(reverseIterator<U> const& rhs)
        {
            this->_ptr = rhs.base();
            return (*this);
        }

        iterator_type base() const { return (this->_ptr); }

        reverseIterator& operator++()
        {
            --this->_ptr;
            return (*this);
        }

        reverseIterator operator++(int)
        {
            reverseIterator iterator = *this;
            --this->_ptr;
            return (iterator);
        }

        reverseIterator& operator--()
        {
            ++this->_ptr;
            return (*this);
        }

        reverseIterator operator--(int)
        {
            reverseIterator iterator = *this;
            ++this->_ptr;
            return (iterator);
        }

        reference operator[] (int index) const
        {
            Iterator tmp = this->_ptr;
            return (*(--tmp - index));
        }

        pointer operator->() const 
        {
            Iterator tmp = this->_ptr;
            return (&(*--tmp));
        }

        reference operator* () const
        {
            Iterator tmp = this->_ptr;
            return (*--tmp);
        }


        reverseIterator operator+(difference_type n) const { return reverseIterator(this->_ptr - n); }

        reverseIterator operator-(difference_type n) const { return reverseIterator(this->_ptr + n); }


        reverseIterator& operator+=(difference_type n)
        {
            this->_ptr -= n;
            return (*this);
        }
	    
        reverseIterator& operator-=(std::ptrdiff_t n)
        {
            this->_ptr += n;
            return (*this);
        }

    protected:
        iterator_type _ptr;
    };

    template<class Iterator1, class Iterator2>
    bool operator==(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs) 
    { return (lhs.base() == rhs.base()); }

    template<class Iterator1, class Iterator2>
    bool operator!=(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs) 
    { return (lhs.base() != rhs.base()); }

    template<class Iterator1, class Iterator2>
    bool operator<(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs) 
    { return (lhs.base() > rhs.base()); }

    template<class Iterator1, class Iterator2>
    bool operator<=(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs) 
    { return (lhs.base() >= rhs.base()); }
    
    template<class Iterator1, class Iterator2>
    bool operator>(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs) 
    { return (lhs.base() < rhs.base()); }

    template<class Iterator1, class Iterator2>
    bool operator>=(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs) 
    { return (lhs.base() <= rhs.base()); }

    template<class Iterator>
    reverseIterator<Iterator> operator+(typename reverseIterator<Iterator>::difference_type n, const reverseIterator<Iterator>& it)
    { return(reverseIterator<Iterator>(it.base() - n)); }
    
    template<class Iterator>
    typename reverseIterator<Iterator>::difference_type operator-(const reverseIterator<Iterator>& lhs, const reverseIterator<Iterator>&  rhs) 
    { return(rhs.base() - lhs.base()); }

    template<class Iterator1, class Iterator2>
    typename reverseIterator<Iterator1>::difference_type operator-(const reverseIterator<Iterator1>& lhs, const reverseIterator<Iterator2>& rhs) 
    { return (rhs.base() - lhs.base()); }
}