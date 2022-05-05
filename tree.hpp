#pragma once

#include "pair.hpp"
#include <cstdlib>
#include <memory>
#include <utility>

namespace ft
{
	/* Feuille  */
	#define LEAF NULL

	typedef enum
	{
		RED = 0,
		BLACK
	} RBColor;

	/* Un noeud de l'arbre */
	template<class T>
	class Node
	{
	public:
		typedef T					  value_type;
		typedef value_type&			  reference;
		typedef value_type const&	  const_reference;
		typedef value_type*			  pointer;
		typedef value_type const*	  const_pointer;
		typedef Node<value_type>*	  node_pointer;

		Node(void): left(NULL), right(NULL), parent(NULL), color(BLACK), value() {}
		Node(T const& value): left(NULL), right(NULL), parent(NULL), color(BLACK), value(value) {}
		Node(Node const& rhs) { *this = rhs; }
		~Node(void) {}
		Node& operator=(Node const& rhs)
		{
			if (this == &rhs)
				return (*this);
			this->left = rhs.left;
			this->right = rhs.right;
			this->parent = rhs.parent;
			this->color	= rhs.color;
			this->value = rhs.value;
			return (*this);
		}

		node_pointer left;
		node_pointer right;
		node_pointer parent;
		RBColor color;
		value_type value; //Ex : la paire pour map
	};

	/*L'arbre */
	template<class T, class Compare, class Allocator = std::allocator<Node<T> > >
	class Tree
	{
	public:
		typedef T										value_type; //Ex : la paire pour map
		typedef value_type&								reference;
		typedef value_type const&						const_reference;
		typedef Compare									value_compare;
		/* Rebind pour allouer un node */
		typedef typename Allocator::template rebind<Node<value_type> >::other allocator_type;
		typedef std::size_t							  	size_type;
		typedef typename allocator_type::pointer	   	pointer;
		typedef typename allocator_type::const_pointer 	const_pointer;
		typedef Node<value_type>						node;
		typedef node*								   	node_pointer;

	private:
		allocator_type allocator;
		size_type size; //taille arbre
		value_compare comp; //objet de comparaison des values (paires)
		node_pointer root; //racine de l'arbre
		node_pointer end; //noeud sentinelle place apres le dernier neoud de l'arbre

	public:
		Tree(void): allocator(Allocator()), size(0), comp(Compare()), root(LEAF), end(this->create_node()) {}
		Tree(Tree const& rhs) { *this = rhs; }
		~Tree(void)
		{
			this->clear(this->root);
			this->delete_node(this->end);
		}

	private:
		Tree& operator=(Tree const& rhs)
		{
			(void)rhs;
			return (*this);
		}

	public: 
		void insert(const_reference value)
		{
			node_pointer n = search(value);
			if (n != NULL)
				return;
			if (this->size)
				this->end->parent->right = LEAF; // supprime end
			else
				this->root = LEAF;
			++this->size;
			/* Cree un noeud rouge */
			node_pointer inserted_node = create_node(node(value));
			inserted_node->color = RED;
			/* Arbre vide on insert le noeud a la racine */
			if (this->root == NULL)
				this->root = inserted_node;
			else
			{
				node_pointer n = this->root;
				while (true)
				{
					/* Tant que plus petit on se deplace a gauche jusqua trouver une place*/
					if (this->comp(value, n->value) == true)
					{
						if (n->left == NULL && n->left != this->end)
						{
							n->left = inserted_node;
							break;
						}
						else
							n = n->left;
					}
					/* Tant que plus grand on se deplace a droit jusqua trouver une place*/ 
					else
					{
						if (n->right == NULL && n->right != this->end)
						{
							n->right = inserted_node;
							break;
						}
						else
							n = n->right;
					}
				}
				/* On le relie au reste de l'arbre.*/
				inserted_node->parent = n;
			}
			/* On verifie que les regle de larbre sont ok */
			insert_case1(inserted_node);
			/* Replace end a la fin de l'arbre */
			update_end();
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last)
		{
			for (; first != last; ++first)
				insert(*first);
		}

		/* On remplace le noeud a suprimer par les valeur du noeud qui precede dans l'odre : le max ou 
		l'element le plus a droit de la branche de gauche */
		void erase(const_reference val)
		{
			/* On cherche le noeud passe si on ne trouve pas on ne fait rien */
			node_pointer n = search(val);
			if (n == NULL)
				return;
			if (this->size)
				this->end->parent->right = LEAF; // Supprime end
			else
				this->root = LEAF;
			--this->size;
			/* Si le noeud a remplacer a deux enfant on le remplace par celui qui precede dans lordre */
			if (n->left != NULL && n->right != NULL)
			{
				node_pointer pred = maximum(n->left);
				n->value = pred->value;
				n = pred;
			}
			node_pointer child = n->right == NULL ? n->left : n->right;
			if (get_color(n) == BLACK)
			{
				n->color = get_color(child);
				erase_case1(n);
			}
			replace_node(n, child);
			if (n->parent == NULL && child != NULL)
				child->color = BLACK;
			delete_node(n);
			/* Replace end a la fin de l'arbre */
			update_end();
		}

		
		void clear(node_pointer root)
		{
			if (root == LEAF || root == this->end)
			{
				this->size = 0;
				this->update_end();
				return;
			}
			clear(root->left);// rappelle recursivement 
			clear(root->right);
			delete_node(root);
		}

		/* Renvoie le pointeur vers l'element passe en param ou null */
		node_pointer search(const_reference val)
		{
			node_pointer n = this->root;
			while (n != NULL)
			{
				/* Element trouve */
				if (this->comp(val, n->value) == false && this->comp(n->value, val) == false && n != this->end)
					return (n);
				/* plus petit va a gauche */
				else if (this->comp(val, n->value) == true)
					n = n->left;
				/* Plus grand va a droite */
				else
					n = n->right;
			}
			return (n);
		}
		node_pointer search(const_reference val) const
		{
			node_pointer n = this->root;
			while (n != NULL)
			{
				if (this->comp(val, n->value) == false && this->comp(n->value, val) == false)
					return (n);
				else if (this->comp(val, n->value) == true)
					n = n->left;
				else
					n = n->right;
			}
			return (n);
		}

		/* Retourne la fin de l'arbre l'element le + a droite */
		node_pointer maximum(node_pointer n)
		{
			while (n->right != NULL && n->right != this->end)
				n = n->right;
			return (n);
		}
		node_pointer maximum(node_pointer n) const
		{
			while (n->right != NULL && n->right != this->end)
				n = n->right;
			return (n);
		}

		/* Retourne le debut de l'arbre : l'element le + a gauche*/ 
		node_pointer minimum(node_pointer n)
		{
			if (this->size == 0)
				return (this->end);
			while (n->left != NULL)
				n = n->left;
			return (n);
		}
		node_pointer minimum(node_pointer n) const
		{
			if (this->size == 0)
				return (this->end);
			while (n->left != NULL)
				n = n->left;
			return (n);
		}

		void swap(Tree& tree)
		{
			allocator_type tmp_allocator = tree.allocator;
			size_type tmp_size	= tree.size;
			value_compare	tmp_comp = tree.comp;
			node_pointer tmp_root = tree.root;
			node_pointer tmp_end = tree.end;

			tree.allocator = this->allocator;
			tree.size = this->size;
			tree.comp = this->comp;
			tree.root = this->root;
			tree.end = this->end;

			this->allocator = tmp_allocator;
			this->size = tmp_size;
			this->comp = tmp_comp;
			this->root = tmp_root;
			this->end = tmp_end;
		}

		allocator_type get_allocator(void) const { return (this->allocator); }
		size_type get_size(void) const { return (this->size); }
		node_pointer get_root(void) const { return (this->root); }
		node_pointer get_end(void) const { return (this->end); }

	private:
		/* CREATE / DELETE */

		/* Cree un noeud sans value */
		node_pointer create_node(void)
		{
			node_pointer n = this->allocator.allocate(1);
			this->allocator.construct(n, node());
			return (n);
		}
		/* Cree un noeud avec comme cle la val passee en arg */
		node_pointer create_node(node p)
		{
			node_pointer n = this->allocator.allocate(1);
			this->allocator.construct(n, p);
			return (n);
		}

		/* Destroy dealloc */
		void delete_node(node_pointer n)
		{
			this->allocator.destroy(n);
			this->allocator.deallocate(n, 1);
		}

		/* GENEALOGY */

		/* Retourne la genealogie demandee ou null si pas de noeud correspondant */
		node_pointer parent(node_pointer n) { return (n->parent); }

		node_pointer grandparent(node_pointer n)
		{
			node_pointer p = parent(n);
			if (p == NULL)
				return (NULL);
			return parent(p);
		}

		node_pointer sibling(node_pointer n)
		{
			node_pointer p = parent(n);
			if (p == NULL)
				return (NULL);
			if (n == p->left)
				return (p->right);
			else
				return (p->left);
		}

		node_pointer uncle(node_pointer n)
		{
			node_pointer p = parent(n);
			node_pointer g = grandparent(n);
			if (g == NULL)
				return (NULL);
			return (sibling(p));
		}

		/* ROTATION */

		/* Effectue une rotation a gauche a partir du noeud passe en parametre */
		void rotate_left(node_pointer n) 
		{
			node_pointer r = n->right;
			replace_node(n, r);
			n->right = r->left;
			if (r->left != NULL)
				r->left->parent = n;
			r->left	= n;
			n->parent = r;
		}

		/* Effectue une rotation a droite a partir du noeud passe en parametre */
		void rotate_right(node_pointer n) 
		{
			node_pointer l = n->left;
			replace_node(n, l);
			n->left = l->right;
			if (l->right != NULL)
				l->right->parent = n;
			l->right  = n;
			n->parent = l;
		}

		/* UTILS */

		RBColor get_color(node_pointer n)
		{
			return (n == NULL ? BLACK : n->color);
		}

		/* remplace old par new,  si old est la racine remplace la racine par new */
		void replace_node(node_pointer oldn, node_pointer newn)
		{
			if (oldn->parent == NULL)
				this->root = newn;
			else
			{
				if (oldn == oldn->parent->left)
					oldn->parent->left = newn;
				else
					oldn->parent->right = newn;
			}
			if (newn != NULL)
				newn->parent = oldn->parent;
		}

		/* Renvoie la nouvelle fin de l'arbre : noeud de droite du precedent end, si vide : cree un maillon
		 fait pointer root et end dessus */
		void update_end(void)
		{
			if (this->size == 0)
			{
				if (this->end == NULL)
					this->end = this->create_node();
				this->root = this->end;
				return;
			}
			node_pointer max = this->maximum(this->root);
			max->right = this->end;
			this->end->parent = max; 
		}

		/* INSERT */

		/* inserted node est a la racine : colore en noir */
		void insert_case1(node_pointer n)
		{
			if (n->parent == NULL)
				n->color = BLACK;
			else
				insert_case2(n);
		}

		/* inserted a un parent noir : tree valide on quitte les verif */
		void insert_case2(node_pointer n)
		{
			if (get_color(n->parent) == BLACK)
				return;
			else
				insert_case3(n);
		}

		/* l'oncle de inserted est rouge, on recolore en noir l'oncle et 
		le parent, en rouge le grand parents, puis on rappelle recursivement
		case1 sur le grand parent (car chgt couleur)*/
		void insert_case3(node_pointer n)
		{
			if (get_color(uncle(n)) == RED)
			{
				n->parent->color = BLACK;
				uncle(n)->color = BLACK;
				grandparent(n)->color = RED;
				insert_case1(grandparent(n));
			}
			else
				insert_case4(n);
		}

		/* Necessite rotation gauche ou droite a partir du parent selon le placement */
		void insert_case4(node_pointer n)
		{
			if (n == n->parent->right && n->parent == grandparent(n)->left)
			{
				rotate_left(n->parent);
				n = n->left;
			}
			else if (n == n->parent->left && n->parent == grandparent(n)->right)
			{
				rotate_right(n->parent);
				n = n->right;
			}
			insert_case5(n);
		}

		/* Necessite recoloration, rotation gauche ou droite a partir du grand parent selon le placement */
		void insert_case5(node_pointer n)
		{
			n->parent->color = BLACK;
			grandparent(n)->color = RED;
			if (n == n->parent->left && n->parent == grandparent(n)->left)
				rotate_right(grandparent(n));
			else
				rotate_left(grandparent(n));
		}

		/* ERASE */
		/* Realise des echanges de couleurs et des rotation selon les configarations (parfois recursivement)
		 pour retablir les couleurs : pas deux rouges a la suite, meme nombre de noir sur chaque chemin  */

		/* Si deleted est la root */
		void erase_case1(node_pointer n)
		{
			if (n->parent == NULL)
				return;
			else
				erase_case2(n);
		}
		
		/* si n a un frere rouge, le noeud suprime etait noir il faut retablir */
		void erase_case2(node_pointer n)
		{
			if (get_color(sibling(n)) == RED)
			{
				n->parent->color  = RED;
				sibling(n)->color = BLACK;
				if (n == n->parent->left)
					rotate_left(n->parent);
				else
					rotate_right(n->parent);
			}
			erase_case3(n);
		}

		void erase_case3(node_pointer n)
		{
			if (get_color(n->parent) == BLACK && get_color(sibling(n)) == BLACK && get_color(sibling(n)->left) == BLACK && get_color(sibling(n)->right) == BLACK)
			{
				sibling(n)->color = RED;
				erase_case1(n->parent);
			}
			else
				erase_case4(n);
		}

		void erase_case4(node_pointer n)
		{
			if (get_color(n->parent) == RED && get_color(sibling(n)) == BLACK && get_color(sibling(n)->left) == BLACK && get_color(sibling(n)->right) == BLACK)
			{
				sibling(n)->color = RED;
				n->parent->color  = BLACK;
			}
			else
				erase_case5(n);
		}
		
		void erase_case5(node_pointer n)
		{
			if (n == n->parent->left && get_color(sibling(n)) == BLACK && get_color(sibling(n)->left) == RED && get_color(sibling(n)->right) == BLACK)
			{
				sibling(n)->color = RED;
				sibling(n)->left->color = BLACK;
				rotate_right(sibling(n));
			}
			else if (n == n->parent->right && get_color(sibling(n)) == BLACK && get_color(sibling(n)->right) == RED && get_color(sibling(n)->left) == BLACK)
			{
				sibling(n)->color = RED;
				sibling(n)->right->color = BLACK;
				rotate_left(sibling(n));
			}
			erase_case6(n);
		}
		
		void erase_case6(node_pointer n)
		{
			sibling(n)->color = get_color(n->parent);
			n->parent->color  = BLACK;
			if (n == n->parent->left)
			{
				sibling(n)->right->color = BLACK;
				rotate_left(n->parent);
			}
			else
			{
				sibling(n)->left->color = BLACK;
				rotate_right(n->parent);
			}
		}
	};
}