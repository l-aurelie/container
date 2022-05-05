#pragma once
#include <iterator>
#include <cstddef>

namespace ft 
{
	/* Defines the category of an iterator. Each tag is an empty type. Iterator
	category tags carry information that can be used to select the most efficient
	algorithms for the specific requirement set that is implied by the category. */
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag: public input_iterator_tag {};
    struct bidirectional_iterator_tag: public forward_iterator_tag {};
    struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	/* std::iterator_traits is the type trait class that provides uniform interface.
	Used here mostly for reverse_iterator based on template parameter <Iterator> */
    template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct	iterator
    {
    	typedef T         value_type;
    	typedef Distance  difference_type;
    	typedef Pointer   pointer;
    	typedef Reference reference;
    	typedef Category  iterator_category;
	};

	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;
			typedef typename Iterator::iterator_category iterator_category;
	};
	template <class T>
	class iterator_traits<T*>
	{
		public:
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			typedef std::random_access_iterator_tag iterator_category;
	};
	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef const T* pointer;
			typedef const T& reference;
			typedef std::random_access_iterator_tag iterator_category;

	};
}