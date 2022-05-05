#pragma once

#include "vector_iterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{
    template <typename T>
    class vectorIterator;

    template <typename T>
    class vectorConstIterator
    {
    public:

        typedef T const         value_type;
        typedef value_type*     pointer;
        typedef value_type&     reference;
    	typedef std::ptrdiff_t  difference_type;
    	typedef std::random_access_iterator_tag iterator_category;

    public:
        
	    vectorConstIterator() : _ptr(NULL) {}
        vectorConstIterator(pointer ptr) : _ptr(ptr) {}
        vectorConstIterator(const vectorConstIterator& src) : _ptr(src._ptr) {}
        vectorConstIterator(const ft::vectorIterator< T >& src): _ptr(src.base()){} 
	    ~vectorConstIterator() {}
       // operator vectorConstIterator<value_type const>() const {return vectorConstIterator<value_type const>(_ptr);}

        vectorConstIterator& operator=(const vectorConstIterator& rhs)
        {
            if(this != &rhs)
                this->_ptr = rhs._ptr;
            return (*this);
        }
        
        pointer	base() const { return _ptr; };

        reference operator[](int index) { return *(this->_ptr + index); }
        pointer operator->() { return (this->_ptr); }
        reference operator*() { return (*this->_ptr); }


        vectorConstIterator& operator++()
        {
            this->_ptr++;
            return (*this);
        }
        vectorConstIterator& operator--()
        {
            this->_ptr--;
            return (*this);
        }

        vectorConstIterator operator++(int)
        {
            vectorConstIterator iterator = *this;
            ++(*this);
            return (iterator);
        }
        vectorConstIterator operator--(int)
        {
            vectorConstIterator iterator = *this;
            --(*this);
            return (iterator);
        }


        bool operator==(const vectorConstIterator& other) const
        { return (this->_ptr == other._ptr); }

        bool operator!=(const vectorConstIterator& other) const 
        { return !(*this == other); }

        bool operator<(const vectorConstIterator& other) const 
        {return (this->_ptr < other._ptr); }

	    bool operator<=(const vectorConstIterator& other) const 
        {return (this->_ptr <= other._ptr); }

    	bool operator>(const vectorConstIterator& other) const 
        {return (this->_ptr > other._ptr); }

    	bool operator>=(const vectorConstIterator& other) const 
        {return (this->_ptr >= other._ptr); }


        vectorConstIterator operator+(difference_type n) const 
        { return (this->_ptr + n); }

        vectorConstIterator operator-(difference_type n) const 
        { return (this->_ptr - n); }

        difference_type operator+(vectorConstIterator const &rhs) const 
        { return (this->_ptr + rhs._ptr); }

		//difference_type operator-(vectorConstIterator const& rhs) const { return (this->_ptr - rhs._ptr); }

        vectorConstIterator& operator+=(difference_type n)
        {
            this->_ptr += n;
            return (*this);
        }
	    
        vectorConstIterator& operator-=(difference_type n)
        {
            this->_ptr -= n;
            return (*this);
        }

        friend vectorConstIterator operator+(difference_type n, const vectorConstIterator& rhs) { return (vectorConstIterator(rhs._ptr + n)); }

		friend difference_type operator-(const vectorConstIterator& lhs, const vectorConstIterator& rhs) { return (lhs._ptr - rhs._ptr); }
    
    private:
        pointer _ptr;
    };
}