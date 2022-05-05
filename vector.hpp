#ifndef VECTOR_HPP
# define VECTOR_HPP
#include "vector_iterator.hpp"
#include "vector_const_iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "algorithm.hpp" 
#include <memory>

namespace ft
{
    template <typename T, typename Alloc = std::allocator<T> >
    class vector
    {
    public:
        /*===/ MEMBER_TYPES /===*/

        /* A class can define type aliases treated as members of the class itself.
        They can be accessed from outside with class_name::member_type, and
        allow to relate class to others or define types (or templated class
        parameters) needed within the class */
        typedef T								            value_type;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef vectorIterator<T>                           iterator;
        typedef vectorConstIterator<T>                      const_iterator;
        typedef reverseIterator<iterator>                   reverse_iterator;
        typedef reverseIterator<const_iterator>             const_reverse_iterator;
        typedef std::ptrdiff_t                              difference_type;
        typedef std::size_t                                 size_type;                     

        /*===/ CONSTRUCTOR DESTRUCTOR ASSIGNATION /===*/ 

        explicit vector(const Alloc& alloc = Alloc()) : _data(NULL), _size(0), _capacity(0), _allocator(alloc) {}	

	    explicit vector(size_type n, const_reference val = value_type(), const Alloc& alloc = Alloc())
        : _data(NULL), _size(0), _capacity(0), _allocator(alloc) { this->assign(n, val); }

		template <class InputIterator>
		vector(InputIterator first, typename ft::enable_if<!(ft::is_integral<InputIterator>::value), InputIterator>::type last, const Alloc& alloc = Alloc())
        : _data(NULL), _size(0), _capacity(0), _allocator(alloc) { this->assign(first, last); }
		
		vector(const vector& x)
        : _data(NULL), _size(0), _capacity(0), _allocator(x._allocator) { *this = x; }
        
        ~vector()
        {
            this->clear();
            this->_allocator.deallocate(this->_data, this->_capacity);
        }
        
        vector& operator= (const vector& x)
        {
            if(this != &x)
			    this->assign(x.begin(), x.end());
			return (*this);
        }

        /*===/ ITERATORS /===*/ 

        iterator begin() { return (iterator(this->_data)); }

        iterator end() { return (iterator(this->_data + this->_size)); }
        
        const_iterator begin() const { return (const_iterator(this->_data)); }

        const_iterator end() const { return (const_iterator(this->_data + this->_size)); }

        reverse_iterator rbegin(void) { return (reverse_iterator(this->_data + this->_size)); }
		
		reverse_iterator rend(void) { return (reverse_iterator(this->_data)); }
        
        const_reverse_iterator rbegin(void) const { return (const_reverse_iterator(this->_data + this->_size)); }

		const_reverse_iterator rend(void) const { return (const_reverse_iterator(this->_data)); }


        /*===/ CAPACITY /===*/ 

        size_type size() const { return (this->_size); }

        size_type max_size() const { return (this->_allocator.max_size()); }

        void resize(size_type n, value_type val = value_type())
        {
            if (n < this->_size)
                while (this->_size > n)
                    pop_back();
            else
            {
                if (this->_capacity < n && n < this->_capacity * 2)
                    reserve(_capacity * 2);
                else if (this->_capacity < n)
                    reserve(n);
                while (this->_size < n)
                    push_back(val);
            }
        }

        size_type capacity() const { return this->_capacity; }

        bool empty() const { return (!this->_size); }

        void reserve(size_type n)
        {
            if (n >= this->_capacity)
            {
                pointer new_storage = this->_allocator.allocate(n);
                for (size_type i = 0; i < _size; i++)
                {
                    this->_allocator.construct(new_storage + i, this->_data[i]);
                    this->_allocator.destroy(this->_data + i);
                }
                _allocator.deallocate(this->_data, this->_capacity);
                this->_capacity = n;
                this->_data = new_storage;
            }
        }

        /*===/ ELEMENTS ACCESS /===*/

        const_reference operator[](size_type index) const { return (this->_data[index]); }

        reference operator[](size_type index) { return (this->_data[index]); }

        reference at(size_type n)
        {
            if (n >= this->_size || n < 0)
                throw std::out_of_range("vector: out of range");
            return this->_data[n];
        }

        const_reference at(size_type n) const
        {
            if (n >= this->_size || n < 0)
                throw std::out_of_range("vector: out of range");
            return this->_data[n];
        }

        reference front() { return this->_data[0]; }

        const_reference front() const { return this->_data[0]; }

        reference back() { return this->_data[this->_size - 1]; }

        const_reference back() const { return _data[this->_size - 1]; }

        /*===/ MODIFIERS /===*/

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
        {
            size_type n = std::distance(first, last);
            clear();
            if (n > this->_capacity)
                reserve(n);
            for (size_type i = 0; i < n; i++)
                push_back(*first++);
        }

        void assign(size_type n, const T& val) 
        {
            clear();
            if (n > this->_capacity)
                reserve(n);
            for (size_type i = 0; i < n; i++)
                this->push_back(val);
        }

        void push_back(const_reference value)
        {
            if (this->_size >= this->_capacity)
            {
                if (this->_capacity == 0)
                    reserve(10);
                else
                    reserve(this->_capacity * 2);
            }
            _allocator.construct(this->_data + this->_size, value);
            this->_size++;
        }

        void pop_back()
        {
            if (this->_size > 0)
            {
                this->_size--;
                this->_allocator.destroy(this->_data + this->_size);
            }
        }

        iterator insert(iterator position, const_reference val)
        {
            size_type n = &(*position) - &(*begin());
            insert(position, 1, val);
            return (begin() + n);
        }

        void insert(iterator position, size_type n, const_reference val)
        {
            if (n != 0)
            {
                size_type n_to_end = &(*end()) - &(*position);
                if (this->_size + n > this->_capacity && this->_size + n <= this->_capacity * 2)
                    reserve(this->_capacity * 2);
                else if (this->_size + n > this->_capacity)
                    reserve(this->_size + n);
                size_type i = 0;
                for (; i < n_to_end; i++)
                {
                    this->_allocator.construct(this->_data + this->_size + n - i - 1, *(this->_data + this->_size - i - 1));
                    this->_allocator.destroy(this->_data + this->_size - i - 1);
                }
                for (size_type j = 0; j < n; j++)
                    this->_allocator.construct(this->_data + this->_size - i + j, val);
                this->_size += n;
            }
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
        {
            size_type n = std::distance(first, last);
            size_type n_to_end = &(*end()) - &(*position);
            if (n != 0)
            {
                if (this->_size + n > this->_capacity && this->_size + n <= this->_capacity * 2)
                    reserve(this->_capacity * 2);
                else if (this->_size + n > this->_capacity)
                    reserve(this->_size + n);
                size_type i = 0;
                for (; i < n_to_end; i++)
                {
                    this->_allocator.construct(this->_data + this->_size + n - i - 1, *(this->_data + this->_size - i - 1));
                    this->_allocator.destroy(this->_data + this->_size - i - 1);
                }
                for (size_type j = 0; j < n; j++)
                {
                    this->_allocator.construct(this->_data + this->_size - i + j, *first);
                    first++;
                }
                this->_size += n;
            }
        }

        iterator erase(iterator position)
        {
            this->_allocator.destroy(&(*position));
            for (iterator it = position; it != end() - 1; it++)
            {
                this->_allocator.construct(&*(it), *(it + 1));
                this->_allocator.destroy(&(*(it + 1)));
            }
            this->_size--;
            return (position);
        }
        iterator erase(iterator first, iterator last)
        {
            for (iterator it = first; it != last; last--)
                erase(it);
            return (first);
        }

        void swap(vector &x)
        {
            std::swap(this->_data, x._data);
            std::swap(this->_size, x._size);
            std::swap(this->_capacity, x._capacity);
            std::swap(this->_allocator, x._allocator);
        }

        void clear()
        {
            for (size_type i = 0; i < this->_size; i++)
                this->_allocator.destroy(this->_data + i);
            this->_size = 0;
        }

        /*===/ ALLOCATORS /===*/

        Alloc get_allocator() const { return (this->_allocator); }

    private:
        pointer _data;
        size_type _size;
        size_type _capacity;
        Alloc _allocator;
    };

        /*===/ NON MEMBER /===*/ 
    template< class T, class Alloc >
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template< class T, class Alloc >
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    { return (!(lhs == rhs)); }

    template< class T, class Alloc >
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    { return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

    template< class T, class Alloc >
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    { return (lhs == rhs || lhs < rhs); }

    template< class T, class Alloc >
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    { return (!(lhs <= rhs)); }

    template< class T, class Alloc >
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    { return (lhs == rhs || lhs > rhs); }

    template <class T, class Alloc>
    void swap (vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
    { lhs.swap(rhs); }

}

#endif