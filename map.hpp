#pragma once

#include "tree.hpp"
#include "algorithm.hpp"
#include "map_const_iterator.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include <memory>

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<Key, T > > >
	class map
	{
	public:
        /*===/ MEMBER TYPES /===*/
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef pair<key_type, mapped_type>				value_type;
		typedef Compare									key_compare;
		typedef Allocator								allocator_type;
		typedef typename allocator_type::reference		reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer		pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		typedef mapIterator<value_type>					iterator;
		typedef mapConstIterator<value_type>			const_iterator;
		typedef ft::reverseIterator<iterator>			reverse_iterator;
		typedef ft::reverseIterator<const_iterator>		const_reverse_iterator;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;

		class value_compare
		{
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			value_compare() : _comp(Compare()) {}
			value_compare(Compare c) : _comp(c) {}
			~value_compare(void) {}
			value_compare& operator=(const value_compare& rhs)
			{
				if (this != &rhs)
					this->_comp = rhs._comp;
				return (*this);
			}
			/* Specialisation de comparaison pour la map : on compare seulement les keys des deux elements */ 
			result_type operator()(const value_type& lhs, const value_type& rhs) const
			{ return (this->_comp(lhs.first, rhs.first)); } 
		protected:
			Compare _comp;
		};

	private:
	 	/* Rebind pour pouvoir allouer des types qui different de la value type du container, ex : node */
		typedef typename allocator_type::template rebind<value_type>::other pair_allocator_type;
		typedef Tree<value_type, value_compare, pair_allocator_type> tree;
		typedef Node<value_type> node;
		typedef typename tree::node_pointer node_pointer;

	public:
        /*===/ CONSTUCTOR DESTRUCTOR ASSIGNATION /===*/
		map() :
		_key_comp(key_compare()), _val_comp(value_compare()), _allocator(allocator_type()), _tree(tree()) {}

		explicit map(const Compare& comp, const Allocator& alloc = Allocator()) :
		_key_comp(comp), _val_comp(value_compare()), _allocator(alloc), _tree(tree()) {}

		template<class InputIt>
		map(InputIt	first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) :
		_key_comp(comp), _val_comp(value_compare()), _allocator(alloc), _tree(tree())
		{ this->insert(first, last); }

		map(const map& src) { *this = src; }

		~map() {}

		map& operator=(const map& rhs)
		{
			if (this != &rhs)
			{
				this->_allocator = rhs._allocator;
				this->_key_comp	= rhs._key_comp;
				this->_val_comp	= rhs._val_comp;
				if (this->_tree.get_size())
					this->clear();
				this->_tree.insert(rhs.begin(), rhs.end());
			}
			return (*this);
		}


        /*===/ ELEMENT ACCESS /===*/

		mapped_type& at(const key_type& key)
		{
			value_type p = ft::make_pair(key, mapped_type());
			node_pointer ptr = this->_tree.search(p);
			if (ptr == NULL)
				throw std::out_of_range("map: out of range");
			return (ptr->value.second);
		}

		const mapped_type& at(const key_type& key) const 
		{
			node_pointer ptr = this->_tree.search(key);
			if (ptr == NULL)
				throw std::out_of_range("map: out of range");
			return (ptr->value.second);
		}

		mapped_type& operator[](const key_type& key)
		{
			value_type p = ft::make_pair(key, mapped_type());
			node_pointer ptr = this->_tree.search(p);
			/* Si la valeur existe pas on l'ajoute */
			if (ptr == NULL)
			{
				this->_tree.insert(value_type(key, mapped_type()));
				ptr = this->_tree.search(p);
			}
			return (ptr->value.second);
		}


        /*===/ ITERATORS /===*/
		
		/* Renvoie l'iterateur a l'aide des fonction minimum et maximum de l'arbre(root ou end) */
		iterator begin() { return (iterator(this->_tree.minimum(this->_tree.get_root()))); }

		const_iterator begin() const { return (const_iterator(this->_tree.minimum(this->_tree.get_root()))); }

		iterator end() { return (iterator(this->_tree.get_end())); }

		const_iterator end() const { return (const_iterator(this->_tree.get_end())); }

		reverse_iterator rbegin() { return (reverse_iterator(this->end())); }

		const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }

		reverse_iterator rend() { return (reverse_iterator(this->begin())); }

		const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); }


        /*===/ CAPACITY /===*/

		bool empty() const { return (this->_tree.get_size() == 0); }

		size_type size() const { return (this->_tree.get_size()); }

		size_type max_size() const { return (this->_tree.get_allocator().max_size()); }


        /*===/ MODIFIERS /===*/

		void clear() { this->_tree.clear(this->_tree.get_root()); }

		pair<iterator, bool> insert(const_reference value)
		{
			size_type size_before = this->_tree.get_size();
			/* bool : true si la pair a ete inseree */
			return (ft::make_pair<iterator, bool>( this->insert(this->begin(), value), size_before != this->_tree.get_size()));
		}

		iterator insert(iterator hint, const_reference value)
		{
			(void)hint;
			this->_tree.insert(value);
			return (iterator(this->_tree.search(value)));
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last)
		{
			for (; first != last; first++)
				this->_tree.insert(*first);
		}

		void erase(iterator pos) { this->_tree.erase(pos.base()->value); }

		void erase(iterator first, iterator last)
		{
			iterator tmp;
			while (first != last)
			{
				tmp = first;
				first++;
				this->_tree.erase(tmp.base()->value);
			}
		}

		size_type erase(const key_type& key) 
		{
			size_type old_size = this->_tree.get_size();
			value_type p = ft::make_pair(key, mapped_type());
			this->_tree.erase(p);
			/* Nb of elements erased */
			return (old_size - this->_tree.get_size());
		}

		void swap(map& x) { this->_tree.swap(x._tree); }


        /*===/ OPERATIONS /===*/

		size_type count(const Key& key) const { return (this->find(key) != this->end()); }

		iterator find(const Key& key)
		{
			node_pointer found = _tree.search(ft::make_pair(key, mapped_type()));
			if(!found)
				return(this->end());
			return(iterator(found));
		}

		const_iterator find(const Key& key) const
		{
			node_pointer found = _tree.search(ft::make_pair(key, mapped_type()));
			if(!found)
				return(this->end());
			return(const_iterator(found));
		}

		ft::pair<iterator, iterator> equal_range(const Key& key)
		{ return (ft::make_pair(lower_bound(key), upper_bound(key))); }

		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
		{ return (ft::make_pair(lower_bound(key), upper_bound(key))); }

		iterator lower_bound(const Key& key)
		{
			for (iterator it = this->begin(); it != this->end(); ++it)
				if (!this->_val_comp(it.base()->value, ft::make_pair(key, mapped_type())))
					return (it);
			return (this->end());
		}

		const_iterator lower_bound(const Key& key) const
		{
			for (const_iterator it = this->begin(); it != this->end(); ++it)
				if (!this->_val_comp(it.base()->value, ft::make_pair(key, mapped_type())))
					return (it);
			return (this->end());
		}

		iterator upper_bound(const Key& key)
		{
			for (iterator it = this->begin(); it != this->end(); ++it)
				if (this->_val_comp(ft::make_pair(key, mapped_type()), it.base()->value))
					return (it);
			return (this->end());
		}

		const_iterator upper_bound(const Key& key) const
		{
			for (const_iterator it = this->begin(); it != this->end(); ++it)
				if (this->_val_comp(ft::make_pair(key, mapped_type()), it.base()->value))
					return (it);
			return (this->end());
		}


        /*===/ OBSERVERS /===*/

		key_compare	  key_comp() const { return (this->_key_comp); }

		value_compare value_comp() const { return (value_compare(this->_key_comp)); }


        /*===/ ALLOCATORS /===*/
		
		allocator_type get_allocator() const { return (this->_allocator); }


	private:
		key_compare	   _key_comp; 
		value_compare  _val_comp;
		allocator_type _allocator;
		tree		   _tree;
	};

    /*===/ NON MEMBER /===*/

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(map<Key, T, Compare, Alloc> const& lhs, map<Key, T, Compare, Alloc> const& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(map<Key, T, Compare, Alloc> const& lhs, map<Key, T, Compare, Alloc> const& rhs)
	{ return (!(lhs == rhs)); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(map<Key, T, Compare, Alloc> const& lhs, map<Key, T, Compare, Alloc> const& rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(map<Key, T, Compare, Alloc> const& lhs, map<Key, T, Compare, Alloc> const& rhs)
	{ return (!(rhs < lhs)); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(map<Key, T, Compare, Alloc> const& lhs, map<Key, T, Compare, Alloc> const& rhs)
	{ return (rhs < lhs); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(map<Key, T, Compare, Alloc> const& lhs, map<Key, T, Compare, Alloc> const& rhs)
	{ return (!(lhs < rhs)); }

	template<class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs)
	{ lhs.swap(rhs); }
}