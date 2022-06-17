#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <memory>
#include "pair.hpp"
#include "type_traits.hpp"
#include "iterator.hpp"
#include <iostream>

namespace ft
{
	template <class T>
	class BinaryNode
	{
	public:
		T		data;
		BinaryNode*	left;
		BinaryNode*	right;
		BinaryNode*	parent;
		BinaryNode*	best;
		BinaryNode(T data) : data(data), left(NULL), right(NULL), parent(NULL)
		{
		}
		BinaryNode(T data, BinaryNode* parent) : data(data), left(NULL), right(NULL), parent(parent)
		{
		}
	};
	template <class T, class Compare, class Node=ft::BinaryNode<T> >
	class BinaryTreeIterator
	{
	public:
		typedef T	 value_type;
		typedef T& reference;
		typedef T* pointer;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t			 difference_type;
		typedef Compare				key_compare;
		BinaryTreeIterator(Node* curr, Node* first, Node* last, Node*& end) : curr(curr), first(first), last(last), end(end), comp(key_compare())
		{
			if (this->comp(2, 1))
			{
				Node* tmp = this->first;
				this->first = this->last;
				this->last = tmp;
				this->curr = this->first;
			}
		}
		BinaryTreeIterator() : curr(NULL), first(NULL), last(NULL), end(NULL), comp(key_compare())
		{
		}
		reference operator*() const
		{
			return (this->curr->data);
		}
		pointer operator->() const
		{
			return (&this->curr->data);
		}
		BinaryTreeIterator& operator++()
		{
			Node* tmp = this->curr;
			if (this->curr == this->end)
			{
				this->curr = this->first;
			}
			else if ((tmp->right == NULL && this->comp(1, 2)) || (tmp->left == NULL && this->comp(2, 1)))
			{
				tmp = tmp->parent;
				while (tmp != NULL && this->comp(tmp->data.first, this->curr->data.first))
					tmp = tmp->parent;
				if (tmp == NULL)
					this->curr = this->end;
				else
					this->curr = tmp;
			}
			else if (this->comp(1, 2))
			{
				tmp = tmp->right;
				while (tmp != NULL && tmp->left != NULL)
				{
					tmp = tmp->left;
				}
				this->curr = tmp;
			}
			else
			{
				tmp = tmp->left;
				while (tmp != NULL && tmp->right != NULL)
				{
					tmp = tmp->right;
				}
				this->curr = tmp;
			}
			return (*this);
		}
		BinaryTreeIterator operator++(int)
		{
			BinaryTreeIterator tmp = *this;
			++*this;
			return (tmp);
		}
		BinaryTreeIterator& operator--()
		{
			Node* tmp = this->curr;
			if (this->curr == this->end)
			{
				this->curr = this->last;
			}
			else if ((tmp->left == NULL && this->comp(1, 2)) || (tmp->right == NULL && this->comp(2, 1)))
			{
				tmp = tmp->parent;
				while (tmp != NULL && this->comp(this->curr->data.first, tmp->data.first))
					tmp = tmp->parent;
				if (tmp == NULL)
					this->curr = this->end;
				else
					this->curr = tmp;
			}
			else if (this->comp(1, 2))
			{
				tmp = tmp->left;
				while (tmp != NULL && tmp->right != NULL)
				{
					tmp = tmp->right;
				}
				this->curr = tmp;
			}
			else
			{
				tmp = tmp->right;
				while (tmp != NULL && tmp->left != NULL)
				{
					tmp = tmp->left;
				}
				this->curr = tmp;
			}
			return (*this);
		}
		BinaryTreeIterator operator--(int)
		{
			BinaryTreeIterator tmp = *this;
			--*this;
			return (tmp);
		}
		friend bool
		operator==(const BinaryTreeIterator& x, const BinaryTreeIterator& y)
		{ return x.curr == y.curr; }

		friend bool
		operator!=(const BinaryTreeIterator& x, const BinaryTreeIterator& y)
		{ return x.curr != y.curr; }
		Node* curr;
		Node* first;
		Node* last;
		Node* end; 
		key_compare comp;
	};
	template <class T, class Compare, class Node=ft::BinaryNode<T> >
	class ConstBinaryTreeIterator
	{
	public:
		typedef T	 value_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef ft::BinaryTreeIterator<T, Compare> iterator;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t			 difference_type;
		typedef Compare					key_compare;
		ConstBinaryTreeIterator(Node* curr, Node* first, Node* last, Node* end) : curr(curr), first(first), last(last), end(end), comp(key_compare())
		{
			if (this->comp(2, 1))
			{
				this->first = last;
				this->last = first;
				if (this->curr == first)
					this->curr = last;
			}
		}
		ConstBinaryTreeIterator() : curr(NULL), first(NULL), last(NULL), end(NULL), comp(key_compare())
		{
		}
		ConstBinaryTreeIterator(const iterator& it) : curr(it.curr), first(it.first), last(it.last), end(it.end), comp(it.comp)
		{
		}
		reference operator*() const
		{
			return (this->curr->data);
		}
		pointer operator->() const
		{
			return (&this->curr->data);
		}
		ConstBinaryTreeIterator& operator++()
		{
			Node* tmp = this->curr;
			if (this->curr == this->end)
			{
				this->curr = this->first;
			}
			else if ((tmp->right == NULL && this->comp(1, 2)) || (tmp->left == NULL && this->comp(2, 1)))
			{
				tmp = tmp->parent;
				while (tmp != NULL && this->comp(tmp->data.first, this->curr->data.first))
					tmp = tmp->parent;
				if (tmp == NULL)
					this->curr = this->end;
				else
					this->curr = tmp;
			}
			else if (this->comp(1, 2))
			{
				tmp = tmp->right;
				while (tmp != NULL && tmp->left != NULL)
				{
					tmp = tmp->left;
				}
				this->curr = tmp;
			}
			else
			{
				tmp = tmp->left;
				while (tmp != NULL && tmp->right != NULL)
				{
					tmp = tmp->right;
				}
				this->curr = tmp;
			}
			return (*this);
		}
		ConstBinaryTreeIterator operator++(int)
		{
			ConstBinaryTreeIterator tmp = *this;
			++*this;
			return (tmp);
		}
		ConstBinaryTreeIterator& operator--()
		{
			Node* tmp = this->curr;
			if (this->curr == this->end)
			{
				this->curr = this->last;
			}
			else if ((tmp->left == NULL && this->comp(1, 2)) || (tmp->right == NULL && this->comp(2, 1)))
			{
				tmp = tmp->parent;
				while (tmp != NULL && this->comp(this->curr->data.first, tmp->data.first))
					tmp = tmp->parent;
				if (tmp == NULL)
					this->curr = this->end;
				else
					this->curr = tmp;
			}
			else if (this->comp(1, 2))
			{
				tmp = tmp->left;
				while (tmp != NULL && tmp->right != NULL)
				{
					tmp = tmp->right;
				}
				this->curr = tmp;
			}
			else
			{
				tmp = tmp->right;
				while (tmp != NULL && tmp->left != NULL)
				{
					tmp = tmp->left;
				}
				this->curr = tmp;
			}
			return (*this);
		}
		ConstBinaryTreeIterator operator--(int)
		{
			ConstBinaryTreeIterator tmp = *this;
			--*this;
			return (tmp);
		}
		friend bool
		operator==(const ConstBinaryTreeIterator& x, const ConstBinaryTreeIterator& y)
		{ return x.curr == y.curr; }

		friend bool
		operator!=(const ConstBinaryTreeIterator& x, const ConstBinaryTreeIterator& y)
		{ return x.curr != y.curr; }
		Node* curr; 
		Node* first;
		Node* last;
		Node* end;
		key_compare comp;
	};
	template <class T, class Compare, class Node=ft::BinaryNode<T>, class A=std::allocator<Node> >
	class BinaryTree
	{
	public:
		typedef A 										allocator_type;
		typedef T										value_type;
		typedef Compare									key_compare;
		typedef ft::ConstBinaryTreeIterator<value_type, key_compare> const_iterator;
		typedef ft::BinaryTreeIterator<value_type, key_compare>		 iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
      	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef size_t									size_type;
		BinaryTree() : root(NULL), alloc(allocator_type()), comp(key_compare())
		{
			this->end = this->alloc.allocate(1);
			this->alloc.construct(this->end, Node(value_type()));
			this->last = this->end;
			this->first = this->end;
		}
		~BinaryTree()
		{
		}
		ft::pair<iterator, bool>	insertPair(value_type data)
		{
			if (this->root == NULL)
			{
				this->root = this->alloc.allocate(1);
				this->alloc.construct(this->root, Node(data));
				this->end->data.first++;
				this->first = this->root;
				this->last = this->root;
				return ft::make_pair(iterator(this->root, this->first, this->last, this->end), true);
			}
			else
			{
				Node* curr = this->root;
				while (true)
				{
					if (data.first < curr->data.first)
					{
						if (curr->left == NULL)
						{
							curr->left = this->alloc.allocate(1);
							this->alloc.construct(curr->left, Node(data, curr));
							if (data.first < this->first->data.first)
								this->first = curr->left;
							this->end->data.first++;
							return ft::make_pair(iterator(curr->left, this->first, this->last, this->end), true);
						}
						else
							curr = curr->left;
					}
					else if (data.first > curr->data.first)
					{
						if (curr->right == NULL)
						{
							curr->right = this->alloc.allocate(1);
							this->alloc.construct(curr->right, Node(data, curr));
							if (data.first > this->first->data.first)
								this->last = curr->right;
							this->end->data.first++;
							return ft::make_pair(iterator(curr->left, this->first, this->last, this->end), true);
						}
						else
							curr = curr->right;
					}
					else
					{
						return ft::make_pair(iterator(curr, this->first, this->last, this->end), false);
					}
				}
			}
		}
		Node*	findKey(typename value_type::first_type value) const
		{
			Node* curr = this->root;
			while (true)
			{
				if (curr == NULL)
					break;
				else if (curr->data.first == value)
					return (curr);
				else if (value < curr->data.first)
					curr = curr->left;
				else if (value > curr->data.first)
					curr = curr->right;
			}
			return (this->end);
		}
		Node*	getFirstNode(Node* node)
		{
			while (node != NULL && node->left != NULL)
				node = node->left;
			return (node);
		}
		Node*	getLastNode(Node* node)
		{
			while (node != NULL && node->right != NULL)
				node = node->right;
			return (node);
		}
		void	findKey(Node*& curr, typename value_type::first_type value) const
		{
			while (true)
			{
				if (curr == NULL)
					break;
				else if (curr->data.first == value)
					break;
				else if (value < curr->data.first)
					curr = curr->left;
				else if (value > curr->data.first)
					curr = curr->right;
			}
		}
		void	removeKey(typename value_type::first_type value)
		{
			Node* node = this->root;

			findKey(node, value);
			if (node == NULL)
				return ;
			if (node->right == NULL && node->left == NULL)
			{
				if (node != this->root)
        		{
					if (node == node->parent->left) {
						node->parent->left = NULL;
					}
					else {
						node->parent->right = NULL;
					}
					this->first = getFirstNode(this->root);
					this->last = getLastNode(this->root);
				}
				else
				{
					this->root = NULL;
					this->first = this->end;
					this->last = this->end;
				}
				this->end->data.first--;
				this->alloc.destroy(node);
				this->alloc.deallocate(node, 1);
			}
			else if (node->left == NULL)
			{
				if (node != this->root)
        		{
					if (node == node->parent->left) {
						node->parent->left = node->right;
					}
					else {
						node->parent->right = node->right;
					}
					node->right->parent = node->parent;
				}
				else
				{
					node->right->parent = node->parent;
					this->root = node->right;
				}
				this->first = getFirstNode(this->root);
				this->last = getLastNode(this->root);
				this->alloc.destroy(node);
				this->alloc.deallocate(node, 1);
				this->end->data.first--;
			}
			else if (node->right == NULL)
			{
				if (node != this->root)
        		{
					if (node == node->parent->left) {
						node->parent->left =  node->left;
					}
					else {
						node->parent->right =  node->left;
					}
					node->left->parent = node->parent;
				}
				else
				{
					node->left->parent = node->parent;
					this->root = node->left;
				}
				this->first = getFirstNode(this->root);
				this->last = getLastNode(this->root);
				this->alloc.destroy(node);
				this->alloc.deallocate(node, 1);
				this->end->data.first--;
			}
			else
			{
				Node* tmp = this->getFirstNode(node->right);
				value_type sv = tmp->data;
				removeKey(tmp->data.first);
				node->data.first = sv.first;
				node->data.second = sv.second;
			}
		}
		void	swap(BinaryTree& lst)
		{
			Node* tmp_root = this->root;
			Node* tmp_last = this->last;
			Node* tmp_first = this->first;
			Node* tmp_end = this->end;
			allocator_type tmp_alloc = this->alloc;
			key_compare tmp_comp = this->comp;
			this->root = lst.root;
			this->last = lst.last;
			this->alloc = lst.alloc;
			this->end = lst.end;
			this->first = lst.first;
			this->comp = lst.comp;
			lst.root = tmp_root;
			lst.last = tmp_last;
			lst.alloc = tmp_alloc;
			lst.comp = tmp_comp;
			lst.end = tmp_end;
			lst.first = tmp_first;
		}
		size_type	size() const
		{
			return (this->end->data.first);
		}
		size_type	max_size() const
		{
			return this->alloc.max_size();
		}
		Node* 	root;
		Node*	last;
		Node*	first;
		Node*	end;
		allocator_type alloc;
		key_compare		comp;
	};
}

#endif