#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <memory>
#include "pair.hpp"
#include "type_traits.hpp"
#include "iterator.hpp"
#include <iostream>

namespace ft
{
	template <class T>
	class List
	{
	public:
		T		data;
		List*	prev;
		List*	next;
		List*	test;
		List*	best;
		List(T data) : data(data), prev(NULL), next(NULL)
		{
		}
	};
	template <class T, class Linked=ft::List<T> >
	class LinkedListIterator
	{
	public:
		typedef T	 value_type;
		typedef T& reference;
		typedef T* pointer;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t			 difference_type;
		LinkedListIterator(Linked* curr) : curr(curr)
		{
		}
		LinkedListIterator() : curr()
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
		LinkedListIterator& operator++()
		{
			this->curr = this->curr->next;
			return (*this);
		}
		LinkedListIterator operator++(int)
		{
			LinkedListIterator tmp = *this;
			++*this;
			return (tmp);
		}
		LinkedListIterator& operator--()
		{
			this->curr = this->curr->prev;
			return (*this);
		}
		LinkedListIterator operator--(int)
		{
			LinkedListIterator tmp = *this;
			--*this;
			return (tmp);
		}
		friend bool
		operator==(const LinkedListIterator& x, const LinkedListIterator& y)
		{ return x.curr == y.curr; }

		friend bool
		operator!=(const LinkedListIterator& x, const LinkedListIterator& y)
		{ return x.curr != y.curr; }
		Linked* curr; 
	};
	template <class T, class Linked=ft::List<T> >
	class ConstLinkedListIterator
	{
	public:
		typedef T	 value_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef ft::LinkedListIterator<T> iterator;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t			 difference_type;
		ConstLinkedListIterator(Linked* curr) : curr(curr)
		{
		}
		ConstLinkedListIterator() : curr()
		{
		}
		ConstLinkedListIterator(const iterator& it) : curr(it.curr)
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
		ConstLinkedListIterator& operator++()
		{
			this->curr = this->curr->next;
			return (*this);
		}
		ConstLinkedListIterator operator++(int)
		{
			ConstLinkedListIterator tmp = *this;
			++*this;
			return (tmp);
		}
		ConstLinkedListIterator& operator--()
		{
			this->curr = this->curr->prev;
			return (*this);
		}
		ConstLinkedListIterator operator--(int)
		{
			ConstLinkedListIterator tmp = *this;
			--*this;
			return (tmp);
		}
		friend bool
		operator==(const ConstLinkedListIterator& x, const ConstLinkedListIterator& y)
		{ return x.curr == y.curr; }

		friend bool
		operator!=(const ConstLinkedListIterator& x, const ConstLinkedListIterator& y)
		{ return x.curr != y.curr; }
		Linked* curr; 
	};
	template <class T, class Compare, class Linked=ft::List<T>, class A=std::allocator<Linked> >
	class LinkedList
	{
	public:
		typedef A 										allocator_type;
		typedef T										value_type;
		typedef ft::ConstLinkedListIterator<value_type>	const_iterator;
		typedef ft::LinkedListIterator<value_type>		iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
      	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef size_t									size_type;
		typedef Compare									key_compare;
		LinkedList() : alloc(allocator_type()), comp(key_compare())
		{
			this->first = this->alloc.allocate(1);
			this->alloc.construct(this->first, List<value_type>(value_type()));
			this->first->next = this->first;
			this->first->prev = this->first;
			this->last = this->first;
		}
		~LinkedList()
		{
		}
		ft::pair<iterator, bool>	insertPair(value_type data)
		{
			Linked* curr = this->first;
			while (curr != this->last && this->comp(curr->data.first, data.first))
			{
				curr = curr->next;
			}
			if (curr == this->last)
			{
				bool chk = false;
				Linked* new_lst = this->alloc.allocate(1);
				this->alloc.construct(new_lst, List<value_type>(data));
				if (this->first == this->last)
				{
					this->first = new_lst;
					chk = true;
				}
				else
				{
					new_lst->next = curr->next;
					new_lst->prev = curr->prev;
					curr->prev->next = new_lst;
				}
				this->alloc.destroy(curr);
				this->alloc.deallocate(curr, 1);
				Linked* end_list = this->alloc.allocate(1);
				if (!ft::is_integral<typename value_type::first_type>::value)
					this->alloc.construct(end_list, List<value_type>(value_type()));
				else
					this->alloc.construct(end_list, List<value_type>(ft::make_pair(data.first + 1, data.second)));
				end_list->next = this->first;
				end_list->prev = new_lst;
				new_lst->next = end_list;
				if (chk)
					new_lst->prev = end_list;
				this->last = end_list;
				return ft::make_pair(iterator(new_lst), true);
			}
			else if (this->comp(data.first, curr->data.first))
			{
				Linked* new_lst = this->alloc.allocate(1);
				this->alloc.construct(new_lst, List<value_type>(data));
				if (curr == this->first)
					this->first = new_lst;
				new_lst->next = curr;
				new_lst->prev = curr->prev;
				curr->prev->next = new_lst;
				curr->prev = new_lst;
				return ft::make_pair(iterator(new_lst), true);
			}
			return ft::make_pair(iterator(curr), false);
		}
		Linked*	findKey(typename value_type::first_type value) const
		{
			Linked* curr = this->first;
			while (curr != this->last)
			{
				if (curr->data.first == value)
					break;
				curr = curr->next;
			}
			return (curr);
		}
		void	removeKey(typename value_type::first_type value)
		{
			Linked* curr = this->first;
			while (curr != this->last)
			{
				if (curr->data.first == value)
					break;
				curr = curr->next;
			}
			if (curr == this->first)
			{
				this->first = curr->next;
			}
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			this->alloc.destroy(curr);
			this->alloc.deallocate(curr, 1);
		}
		void	swap(LinkedList& lst)
		{
			Linked* tmp_first = this->first;
			Linked* tmp_last = this->last;
			allocator_type tmp_alloc = this->alloc;
			this->first = lst.first;
			this->last = lst.last;
			this->alloc = lst.alloc;
			lst.first = tmp_first;
			lst.last = tmp_last;
			lst.alloc = tmp_alloc;
		}
		size_type	size() const
		{
			size_type i = 0;
			Linked* curr = this->first;
			while (curr != this->last)
			{
				curr = curr->next;
				i++;
			}
			return (i);
		}
		size_type	max_size() const
		{
			return this->alloc.max_size();
		}
		Linked* first;
		Linked*	last;
		allocator_type alloc;
		key_compare		comp;
	};
}

#endif