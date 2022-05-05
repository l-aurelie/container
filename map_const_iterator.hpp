#pragma once

#include "map_iterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	template<typename T>
	class mapConstIterator
	{
	public:
		typedef T const			value_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
		typedef std::ptrdiff_t	difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

	private:
		typedef typename Node<T>::node_pointer node_pointer;

	public:
		mapConstIterator() : _ptr(NULL) {}
		mapConstIterator(node_pointer ptr) : _ptr(ptr) {}
		mapConstIterator(const mapIterator<T>& rhs) : _ptr(rhs.base()) {}
		mapConstIterator(const mapConstIterator& rhs) { *this = rhs; }
		~mapConstIterator() {}

		mapConstIterator& operator=(const mapConstIterator& rhs)
		{
			if (this != &rhs)
				this->_ptr = rhs._ptr;
			return (*this);
		}

		node_pointer base() const { return (this->_ptr); }

		reference operator*() const { return (this->_ptr->value); }
		pointer	operator->() const { return (&this->_ptr->value); }


		mapConstIterator& operator++()
		{
			if (!this->_ptr)
				return (*this);
			/* Si noeud a droit, prend la plus petite valeur a droite (cad la plus a gauche) : la prochaine */
			if (this->_ptr->right)
			{
				this->_ptr = this->_ptr->right;
				while (this->_ptr->left)
					this->_ptr = this->_ptr->left;
			}
			/* Sinon on doit remonter jusqu'au prochain noeud : si a gauche une seule fois car le parents est plus grand, si a droite
			le parent est plus petit on remonte jusqua ne plus etre a droite */
			else if (this->_ptr->parent)
			{
				while (this->_ptr->parent && this->_ptr->parent->right == this->_ptr)
					this->_ptr = this->_ptr->parent;
				if (this->_ptr->parent && this->_ptr->parent->left == this->_ptr)
					this->_ptr = this->_ptr->parent;
				else
					this->_ptr = NULL;
			}
			else
				this->_ptr = NULL;
			return (*this);
		}
		mapConstIterator& operator--()
		{
			if (!this->_ptr)
				return (*this);
			/* Si un noeud a gauche il est plus petit, on va chercher de ce cote le noeud le plus grand : le plus a droite */
			if (this->_ptr->left)
			{
				this->_ptr = this->_ptr->left;
				while (this->_ptr && this->_ptr->right)
					this->_ptr = this->_ptr->right;
			}
			/* Sinon on remonte jusqua ce que ce soit le pere d'un noeud de droite : il est plus petit  */
			else
			{
				node_pointer tmp = this->_ptr;
				this->_ptr = this->_ptr->parent;
				while (this->_ptr && this->_ptr->right != tmp)
				{
					tmp = this->_ptr;
					this->_ptr = this->_ptr->parent;
				}
			}
			return (*this);
		}

		mapConstIterator operator++(int)
		{
			mapConstIterator iterator = *this;
			++(*this);
			return (iterator);
		}
		mapConstIterator operator--(int)
		{
			mapConstIterator tmp = *this;
			--(*this);
			return (tmp);
		}

		bool operator==(const mapConstIterator<T>& rhs) const { return (this->_ptr == rhs._ptr); }
		bool operator!=(const mapConstIterator<T>& rhs) const { return (this->_ptr != rhs._ptr); }

		private:
			node_pointer _ptr;
	};

}