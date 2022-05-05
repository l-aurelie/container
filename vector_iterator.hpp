#pragma once

#include "iterator_traits.hpp"
#include "vector_const_iterator.hpp"

namespace ft
{
    template<typename T>
    class vectorConstIterator;

    template <typename T>
    class vectorIterator 
    {
    public:

        typedef T               value_type;
        typedef value_type*     pointer;
        typedef value_type&     reference;
    	typedef std::ptrdiff_t  difference_type;
    	typedef std::random_access_iterator_tag iterator_category;

    public:
        
	    vectorIterator() : _ptr(NULL) {}
        vectorIterator(pointer ptr) : _ptr(ptr) {}
        vectorIterator(const vectorIterator& src) : _ptr(src._ptr) {}
	    ~vectorIterator() {}
        //operator vectorIterator<value_type const>() const {return vectorIterator<value_type const>(_ptr);}

        vectorIterator& operator=(const vectorIterator& rhs)
        {
            if(this != &rhs)
                this->_ptr = rhs._ptr;
            return (*this);
        }

        pointer	base() const { return _ptr; };


        reference operator[](int index) { return *(this->_ptr + index); }
        pointer operator->() { return (this->_ptr); }
        reference operator*() { return (*this->_ptr); }


        vectorIterator& operator++()
        {
            this->_ptr++;
            return (*this);
        }
        vectorIterator& operator--()
        {
            this->_ptr--;
            return (*this);
        }
        
        vectorIterator operator++(int)
        {
            vectorIterator iterator = *this;
            ++(*this);
            return (iterator);
        }
        vectorIterator operator--(int)
        {
            vectorIterator iterator = *this;
            --(*this);
            return (iterator);
        }


        bool operator==(const vectorConstIterator<T>& other) const 
        { return (this->_ptr == other.base()); }

        bool operator!=(const vectorConstIterator<T>& other) const 
        { return !(*this == other.base()); }

        bool operator<(const vectorConstIterator<T>& other) const 
        {return (this->_ptr < other.base()); }

	    bool operator<=(const vectorConstIterator<T>& other) const 
        {return (this->_ptr <= other.base()); }

    	bool operator>(const vectorConstIterator<T>& other) const 
        {return (this->_ptr > other.base()); }

    	bool operator>=(const vectorConstIterator<T>& other) const 
        {return (this->_ptr >= other.base()); }


        vectorIterator operator+(difference_type n) const 
        { return (this->_ptr + n); }

        vectorIterator operator-(difference_type n) const 
        { return (this->_ptr - n); }

        difference_type operator+(const vectorIterator& rhs) const 
        { return (this->_ptr + rhs._ptr); }

		//difference_type operator-(vectorIterator const& rhs) const { return (this->_ptr - rhs._ptr); }

        vectorIterator& operator+=(difference_type n)
        {
            this->_ptr += n;
            return (*this);
        }
	    
        vectorIterator& operator-=(difference_type n)
        {
            this->_ptr -= n;
            return (*this);
        }

        friend vectorIterator operator+(difference_type n, const vectorIterator& rhs) { return (vectorIterator(rhs._ptr + n)); }

		friend difference_type operator-(const vectorIterator& lhs, const vectorIterator& rhs) { return (lhs._ptr - rhs._ptr); }
    
    private:
        pointer _ptr;
    };


}