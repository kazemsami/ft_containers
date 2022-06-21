#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <memory>
#include "pair.hpp"
#include "type_traits.hpp"
#include <typeinfo>
#include "iterator.hpp"
#include <algorithm>
#include <string>

#define CHECK_TYPE(X) x == true

namespace ft
{
	template <class T>
	class AvlNode
	{
	public:
		T		data;
		AvlNode*	left;
		AvlNode*	right;
		AvlNode*	parent;
		int			height;
		AvlNode(T data) : data(data), left(NULL), right(NULL), parent(NULL), height(1)
		{
		}
		AvlNode(T data, AvlNode* parent) : data(data), left(NULL), right(NULL), parent(parent), height(1)
		{
		}
	};
	template <class T, class Compare, class Node=ft::AvlNode<T>, class Alloc=std::allocator<Node> >
	class AvlTreeIterator
	{
	public:
		typedef T	 value_type;
		typedef T& reference;
		typedef T* pointer;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t			 difference_type;
		typedef Alloc				allocator_type;
		typedef Compare				key_compare;
		AvlTreeIterator(Node* curr, Node* first, Node* last, Node* end) : curr(curr), first(first), last(last), end(end), comp(key_compare()), alloc(allocator_type())
		{
		}
		AvlTreeIterator() : curr(NULL), first(NULL), last(NULL), end(NULL), comp(key_compare()), alloc(allocator_type())
		{
		}
		~AvlTreeIterator()
		{
		}
		reference operator*() const
		{
			if (this->curr == NULL)
				return (this->end->data);
			else
				return (this->curr->data);
		}
		pointer operator->() const
		{
			if (this->curr == NULL)
				return (&this->end->data);
			else
				return (&this->curr->data);
		}
		AvlTreeIterator& operator++()
		{
			Node* tmp = this->curr;
			if (this->curr == NULL)
			{
				this->curr = this->first;
			}
			else if (tmp->right == NULL)
			{
				tmp = tmp->parent;
				while (tmp != NULL && this->comp(tmp->data.first, this->curr->data.first))
					tmp = tmp->parent;
				this->curr = tmp;
			}
			else
			{
				tmp = tmp->right;
				while (tmp->left != NULL)
				{
					tmp = tmp->left;
				}
				this->curr = tmp;
			}
			return (*this);
		}
		AvlTreeIterator operator++(int)
		{
			AvlTreeIterator tmp = *this;
			++*this;
			return (tmp);
		}
		AvlTreeIterator& operator--()
		{
			Node* tmp = this->curr;
			if (this->curr == NULL)
			{
				this->curr = this->last;
			}
			else if (tmp->left == NULL)
			{
				tmp = tmp->parent;
				while (tmp != NULL && this->comp(this->curr->data.first, tmp->data.first))
					tmp = tmp->parent;
				this->curr = tmp;
			}
			else
			{
				tmp = tmp->left;
				while (tmp->right != NULL)
				{
					tmp = tmp->right;
				}
				this->curr = tmp;
			}
			return (*this);
		}
		AvlTreeIterator operator--(int)
		{
			AvlTreeIterator tmp = *this;
			--*this;
			return (tmp);
		}
		friend bool
		operator==(const AvlTreeIterator& x, const AvlTreeIterator& y)
		{ return x.curr == y.curr; }

		friend bool
		operator!=(const AvlTreeIterator& x, const AvlTreeIterator& y)
		{ return x.curr != y.curr; }
		Node* curr;
		Node* first;
		Node* last;
		Node* end;
		key_compare comp;
		allocator_type alloc;
	};
	template <class T, class Compare, class Node=ft::AvlNode<T>, class Alloc=std::allocator<Node> >
	class ConstAvlTreeIterator
	{
	public:
		typedef T	 value_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef ft::AvlTreeIterator<T, Compare> iterator;
		typedef Alloc				allocator_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t			 difference_type;
		typedef Compare					key_compare;
		ConstAvlTreeIterator(Node* curr, Node* first, Node* last, Node* end) : curr(curr), first(first), last(last), end(end), comp(key_compare()), alloc(allocator_type())
		{
		}
		ConstAvlTreeIterator() : curr(NULL), first(NULL), last(NULL), end(NULL), comp(key_compare()), alloc(allocator_type())
		{
		}
		ConstAvlTreeIterator(const iterator& it) : curr(it.curr), first(it.first), last(it.last), end(it.end), comp(it.comp), alloc(it.alloc)
		{
		}
		~ConstAvlTreeIterator()
		{
		}
		reference operator*() const
		{
			if (this->curr == NULL)
				return (this->end->data);
			else
				return (this->curr->data);
		}
		pointer operator->() const
		{
			if (this->curr == NULL)
				return (&this->end->data);
			else
				return (&this->curr->data);
		}
		ConstAvlTreeIterator& operator++()
		{
			Node* tmp = this->curr;
			if (this->curr == NULL)
			{
				this->curr = this->first;
			}
			else if (tmp->right == NULL)
			{
				tmp = tmp->parent;
				while (tmp != NULL && this->comp(tmp->data.first, this->curr->data.first))
					tmp = tmp->parent;
				this->curr = tmp;
			}
			else
			{
				tmp = tmp->right;
				while (tmp->left != NULL)
				{
					tmp = tmp->left;
				}
				this->curr = tmp;
			}
			return (*this);
		}
		ConstAvlTreeIterator operator++(int)
		{
			ConstAvlTreeIterator tmp = *this;
			++*this;
			return (tmp);
		}
		ConstAvlTreeIterator& operator--()
		{
			Node* tmp = this->curr;
			if (this->curr == NULL)
			{
				this->curr = this->last;
			}
			else if (tmp->left == NULL)
			{
				tmp = tmp->parent;
				while (tmp != NULL && this->comp(this->curr->data.first, tmp->data.first))
					tmp = tmp->parent;
				this->curr = tmp;
			}
			else
			{
				tmp = tmp->left;
				while (tmp->right != NULL)
				{
					tmp = tmp->right;
				}
				this->curr = tmp;
			}
			return (*this);
		}
		ConstAvlTreeIterator operator--(int)
		{
			ConstAvlTreeIterator tmp = *this;
			--*this;
			return (tmp);
		}
		friend bool
		operator==(const ConstAvlTreeIterator& x, const ConstAvlTreeIterator& y)
		{ return x.curr == y.curr; }

		friend bool
		operator!=(const ConstAvlTreeIterator& x, const ConstAvlTreeIterator& y)
		{ return x.curr != y.curr; }
		Node* curr; 
		Node* first;
		Node* last;
		Node* end;
		key_compare comp;
		allocator_type alloc;
	};
	template <class T, class Compare, class Node=ft::AvlNode<T>, class A=std::allocator<Node> >
	class AvlTree
	{
	public:
		typedef A 										allocator_type;
		typedef T										value_type;
		typedef Compare									key_compare;
		typedef ft::ConstAvlTreeIterator<value_type, key_compare> const_iterator;
		typedef ft::AvlTreeIterator<value_type, key_compare>		 iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
      	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef size_t									size_type;
		AvlTree() : root(NULL), last(NULL), first(NULL), sz(0), alloc(allocator_type()), comp(key_compare())
		{
			this->end = this->alloc.allocate(1);
			#if CHECK_TYPE(ft::is_integral<typename value_type::first_type>::value)
			this->alloc.construct(this->end, Node(ft::make_pair(this->sz, typename value_type::second_type())));
			#else
			this->alloc.construct(this->end, Node(value_type()));
			#endif
		}
		~AvlTree()
		{
			this->alloc.destroy(this->end);
			this->alloc.deallocate(this->end, 1);
		}
		int calheight(Node *p){

            if(p->left && p->right){
				if (p->left->height < p->right->height)
					return p->right->height + 1;
				else
					return  p->left->height + 1;
            }
            else if(p->left && p->right == NULL)
			{
               return p->left->height + 1;
            }
            else if(p->left ==NULL && p->right)
			{
               return p->right->height + 1;
            }
            return 0;

		}
		int bf(Node *n){
			if (n == NULL)
				return (0);
            else if(n->left && n->right){
                return n->left->height - n->right->height; 
            }
            else if(n->left && n->right == NULL){
                return n->left->height; 
            }
            else if(n->left == NULL && n->right ){
                return -n->right->height;
            }
			return (0);
		}
		Node * rightRotate(Node *n){
			Node *p;
			Node *tp;
			p = n;
			tp = p->left;
			
			p->left = tp->right;
			tp->right = p;
			tp->height = calheight(tp);
			p->height = calheight(p);
			tp->parent = p->parent;
			if (tp->right)
				tp->right->parent = tp;
			if (tp->right && tp->right->left)
				tp->right->left->parent = tp->right;
			return tp; 
		}
		Node * leftRotate(Node *n){
			Node *p;
			Node *tp;
			p = n;
			tp = p->right;
			
			p->right = tp->left;
			tp->left = p;
			tp->height = calheight(tp);
			p->height = calheight(p);
			tp->parent = p->parent;
			if (tp->left)
				tp->left->parent = tp;
			if (tp->left && tp->left->right)
				tp->left->right->parent = tp->left;
			return tp; 
		}
		Node* insert(Node *r, value_type data)
		{
			if (r == NULL)
			{
				Node* n = this->alloc.allocate(1);
				this->alloc.construct(n, Node(data));
				this->sz++;
				this->alloc.destroy(this->end);
				this->alloc.deallocate(this->end, 1);
				this->end = this->alloc.allocate(1);
				#if CHECK_TYPE(ft::is_integral<typename value_type::first_type>::value)
				this->alloc.construct(this->end, Node(ft::make_pair(this->sz, typename value_type::second_type())));
				#else
				this->alloc.construct(this->end, Node(value_type()));
				#endif
				if (this->first == NULL)
					this->first = n;
				if (this->last == NULL)
					this->last = n;
				r = n;
				return r;             
			}
			else{
				if(this->comp(data.first, r->data.first))
				{
					r->left = insert(r->left, data);
					r->left->parent = r;
					if (this->comp(data.first, this->first->data.first))
						this->first = r->left;
				}
				else if (this->comp(r->data.first, data.first))
				{
					r->right = insert(r->right, data);
					r->right->parent = r;
					if (this->comp(this->last->data.first, data.first))
						this->last = r->right;
				}
				else
					return r;
			}

			r->height = calheight(r);

			if (bf(r) > 1 && bf(r->left) >= 0)
        		r = rightRotate(r);
 
			if (bf(r) < -1 && bf(r->right) <= 0)
				r = leftRotate(r);
		
			if (bf(r) > 1 && bf(r->left) < 0)
			{
				r->left = leftRotate(r->left);
				r = rightRotate(r);
			}
			if (bf(r) < -1 &&  bf(r->right) > 0)
			{
				r->right = rightRotate(r->right);
				r = leftRotate(r);
			}
			return r;

        }
		Node*	findKey(typename value_type::first_type value) const
		{
			Node* curr = this->root;
			while (true)
			{
				if (curr == NULL)
					return (curr);
				else if (curr->data.first == value)
					return (curr);
				else if (this->comp(value, curr->data.first))
					curr = curr->left;
				else if (this->comp(curr->data.first, value))
					curr = curr->right;
			}
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
		Node*	removeKey(Node* node, typename value_type::first_type value)
		{
			if (node == NULL)
				return NULL;
			if (this->comp(value, node->data.first))
				node->left = removeKey(node->left, value);
			else if (this->comp(node->data.first, value))
				node->right = removeKey(node->right, value);
			else if (node->right == NULL && node->left == NULL)
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
					this->first = NULL;
					this->last = NULL;
				}
				this->sz--;
				this->alloc.destroy(this->end);
				this->alloc.deallocate(this->end, 1);
				this->end = this->alloc.allocate(1);
				#if CHECK_TYPE(ft::is_integral<typename value_type::first_type>::value)
				this->alloc.construct(this->end, Node(ft::make_pair(this->sz, typename value_type::second_type())));
				#else
				this->alloc.construct(this->end, Node(value_type()));
				#endif
				this->alloc.destroy(node);
				this->alloc.deallocate(node, 1);
				return (NULL);
			}
			else if (node->left == NULL)
			{
				Node* tmp = node->right;
				if (node != this->root)
        		{
					if (node == node->parent->left) {
						node->parent->left =  tmp;
					}
					else {
						node->parent->right =  tmp;
					}
					tmp->parent = node->parent;
				}
				else
				{
					tmp->parent = node->parent;
					this->root = tmp;
				}
				this->first = getFirstNode(this->root);
				this->last = getLastNode(this->root);
				this->alloc.destroy(node);
				this->alloc.deallocate(node, 1);
				this->sz--;
				this->alloc.destroy(this->end);
				this->alloc.deallocate(this->end, 1);
				this->end = this->alloc.allocate(1);
				#if CHECK_TYPE(ft::is_integral<typename value_type::first_type>::value)
				this->alloc.construct(this->end, Node(ft::make_pair(this->sz, typename value_type::second_type())));
				#else
				this->alloc.construct(this->end, Node(value_type()));
			#endif
				node = tmp;
			}
			else if (node->right == NULL)
			{
				Node* tmp = node->left;
				if (node != this->root)
        		{
					if (node == node->parent->left) {
						node->parent->left =  tmp;
					}
					else {
						node->parent->right =  tmp;
					}
					tmp->parent = node->parent;
				}
				else
				{
					tmp->parent = node->parent;
					this->root = tmp;
				}
				this->first = getFirstNode(this->root);
				this->last = getLastNode(this->root);
				this->alloc.destroy(node);
				this->alloc.deallocate(node, 1);
				this->sz--;
				this->alloc.destroy(this->end);
				this->alloc.deallocate(this->end, 1);
				this->end = this->alloc.allocate(1);
				#if CHECK_TYPE(ft::is_integral<typename value_type::first_type>::value)
				this->alloc.construct(this->end, Node(ft::make_pair(this->sz, typename value_type::second_type())));
				#else
				this->alloc.construct(this->end, Node(value_type()));
			#endif
				node = tmp;
			}
			else
			{
				bool chk = 0;
				Node* tmp = this->getFirstNode(node->right);
				if (node == this->root)
					chk = 1;
				Node* tmp_right = node->right;
				Node* tmp_left = node->left;
				Node* tmp_parent = node->parent;
				int	svheight = node->height;
				this->alloc.destroy(node);
				this->alloc.deallocate(node, 1);
				node = this->alloc.allocate(1);
				this->alloc.construct(node, Node(ft::make_pair(tmp->data.first, tmp->data.second), tmp_parent));
				node->right = tmp_right;
				node->left = tmp_left;
				node->height = svheight;
				if (node->right)
					node->right->parent = node;
				if (node->left)
					node->left->parent = node;
				if (!chk)
				{
					if (this->comp(node->data.first, node->parent->data.first))
						node->parent->left = node;
					else
						node->parent->right = node;
				}
				else
					this->root = node;
				this->first = getFirstNode(this->root);
				this->last = getLastNode(this->root);
				node->right = removeKey(node->right, tmp->data.first);
			}

			node->height = calheight(node);

			if (bf(node) > 1 && bf(node->left) >= 0)
				node = rightRotate(node);
			if (bf(node) > 1 && bf(node->left) < 0)
			{
				node->left = leftRotate(node->left);
				node = rightRotate(node);
			}
			if (bf(node) < -1 && bf(node->right) <= 0)
				node = leftRotate(node);
			if (bf(node) < -1 && bf(node->right) > 0)
			{
				node->right = rightRotate(node->right);
				node = leftRotate(node);
			}
			return (node);
		}
		void	swap(AvlTree& lst)
		{
			Node* tmp_root = this->root;
			Node* tmp_last = this->last;
			Node* tmp_first = this->first;
			allocator_type tmp_alloc = this->alloc;
			key_compare tmp_comp = this->comp;
			size_type tmp_sz = this->sz;
			this->root = lst.root;
			this->last = lst.last;
			this->alloc = lst.alloc;
			this->sz = lst.sz;
			this->first = lst.first;
			this->comp = lst.comp;
			lst.root = tmp_root;
			lst.last = tmp_last;
			lst.alloc = tmp_alloc;
			lst.comp = tmp_comp;
			lst.first = tmp_first;
			lst.sz = tmp_sz;
		}
		size_type	size() const
		{
			return (this->sz);
		}
		size_type	max_size() const
		{
			return this->alloc.max_size();
		}
		Node* 	root;
		Node*	last;
		Node*	first;
		Node*	end;
		size_type sz;
		allocator_type alloc;
		key_compare		comp;
	};
}

#endif