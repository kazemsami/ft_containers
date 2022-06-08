#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <vector>

namespace ft
{
	template <class T, bool> struct iterator_traits_impl {};
	template <class T>
	struct iterator_traits_impl<T, true>
	{
		typedef typename T::difference_type   difference_type;
		typedef typename T::value_type        value_type;
		typedef typename T::pointer           pointer;
		typedef typename T::reference         reference;
		typedef typename T::iterator_category iterator_category;
	};

	template <class T, bool> struct iterator_traits_base {};

	template <class T>
	struct iterator_traits_base<T, true>
		:  iterator_traits_impl
		<
			T,
			true
		>
	{};

	template <class T>
	struct iterator_traits
		: iterator_traits_base<T, true> {
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<class category, class tp, class distance = ptrdiff_t, class ptr = tp*, class ref = tp&>
	struct iterator
	{
		typedef tp        value_type;
		typedef distance  difference_type;
		typedef ptr   pointer;
		typedef ref reference;
		typedef category  iterator_category;
	};
	template <class T>
	class reverse_iterator : public ft::iterator<typename iterator_traits<T>::iterator_category,
						typename iterator_traits<T>::value_type,
						typename iterator_traits<T>::difference_type,
						typename iterator_traits<T>::pointer,
						typename iterator_traits<T>::reference>
	{
	private:
		T current;
	public:
		typedef T                                        		iterator_type;
		typedef typename iterator_traits<T>::difference_type 	difference_type;
		typedef typename iterator_traits<T>::reference       	reference;
		typedef typename iterator_traits<T>::pointer         	pointer;
		reverse_iterator(T cur) : current(cur) {}
		reverse_iterator& operator=(const reverse_iterator<T>& u)
		{
			current = u.base(); return *this;
		}
		T base() const
		{
			return current;
		}
		reference operator*() const
		{
			T tmp = current; return *--tmp;
		}
		pointer  operator->() const
		{
			return &operator*();
		}
		reverse_iterator& operator++()
		{
			--current; return *this;
		}
		reverse_iterator  operator++(int)
		{
			reverse_iterator tmp(*this); --current; return tmp;
		}
		reverse_iterator& operator--()
		{
			++current; return *this;
		}
		reverse_iterator  operator--(int)
		{
			reverse_iterator tmp(*this); ++current; return tmp;
		}
		reverse_iterator  operator+ (difference_type n) const
		{
			return reverse_iterator(current - n);
		}
		reverse_iterator& operator+=(difference_type n)
		{
			current -= n; return *this;
		}
		reverse_iterator  operator- (difference_type n) const
		{
			return reverse_iterator(current + n);
		}
		reverse_iterator& operator-=(difference_type n)
		{
			current += n; return *this;
		}
		reference         operator[](difference_type n) const
		{
			return *(*this + n);
		}
		bool operator==(const reverse_iterator &t) const
		{
			return t.base() == this->base();
		}
		bool operator!=(const reverse_iterator &t) const
		{
			return t.base() != this->base();
		}
	};
	template <class T>
	class wrap_iter
	{
	public:
		typedef T iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
		typedef typename ft::iterator_traits<iterator_type>::reference reference;
		typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
	private:
		iterator_type ptr;
	public:
		wrap_iter(iterator_type arr): ptr(arr)
		{
		}
		~wrap_iter() {}
		reference operator*() const
		{
			return (*this->ptr);
		}
		pointer operator->() const
		{
			return (&this->*ptr);
		}
		wrap_iter& operator+=(difference_type am)
		{
			this->ptr += am;
			return (*this);
		}
		wrap_iter& operator-=(difference_type am)
		{
			this->ptr -= am;
			return (*this);
		}
		wrap_iter operator+(difference_type am)
		{
			wrap_iter tmp = *this;
			tmp += am;
			return (tmp);
		}
		wrap_iter operator-(difference_type am)
		{
			wrap_iter tmp = *this;
			tmp -= am;
			return (tmp);
		}
		wrap_iter& operator++()
		{
			this->ptr++;
			return (*this);
		}
		wrap_iter operator++(int)
		{
			wrap_iter tmp = *this;
			++*this;
			return (tmp);
		}
		wrap_iter& operator--()
		{
			this->ptr--;
			return (*this);
		}
		wrap_iter operator--(int)
		{
			wrap_iter tmp = *this;
			--*this;
			return (tmp);
		}
		bool operator==(const wrap_iter &t) const
		{
			return t.ptr == this->ptr;
		}
		bool operator!=(const wrap_iter &t) const
		{
			return t.ptr != this->ptr;
		}
		reference  operator[](difference_type n) const 
		{
			return *(*this + n);
		}
	};
}

#endif