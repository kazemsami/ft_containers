#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <vector>

namespace ft
{
	template<typename _Iterator>
    struct iterator_traits
    {
      typedef typename _Iterator::iterator_category iterator_category;
      typedef typename _Iterator::value_type        value_type;
      typedef typename _Iterator::difference_type   difference_type;
      typedef typename _Iterator::pointer           pointer;
      typedef typename _Iterator::reference         reference;
    };

 	template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
      typedef std::random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef _Tp*                        pointer;
      typedef _Tp&                        reference;
    };

  	template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
      typedef std::random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef const _Tp*                  pointer;
      typedef const _Tp&                  reference;
    };
	template<class category, class tp, class distance = ptrdiff_t, class ptr = tp*, class ref = tp&>
	struct iterator
	{
		typedef tp			value_type;
		typedef distance	difference_type;
		typedef ptr   		pointer;
		typedef ref			reference;
		typedef category	iterator_category;
	};
	template <class T>
	class reverse_iterator : public ft::iterator<typename iterator_traits<T>::iterator_category,
						typename iterator_traits<T>::value_type,
						typename iterator_traits<T>::difference_type,
						typename iterator_traits<T>::pointer,
						typename iterator_traits<T>::reference>
	{
	public:
		typedef T                                        		iterator_type;
		typedef typename iterator_traits<T>::difference_type 	difference_type;
		typedef typename iterator_traits<T>::reference       	reference;
		typedef typename iterator_traits<T>::pointer         	pointer;
	private:
		pointer current;
		reverse_iterator(pointer cur) : current(cur) {}
		reverse_iterator& operator=(const reverse_iterator<T>& u)
		{
			current = u.base(); return *this;
		}
		pointer base() const
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
		pointer ptr;
	public:
		wrap_iter(pointer arr): ptr(arr)
		{
		}
		~wrap_iter() {}
		pointer base()
		{
			return (ptr);
		}
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
		reference  operator[](difference_type n) const 
		{
			return *(*this + n);
		}
	};
	template <typename T>
	bool operator!=(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T*> rhs)
	{
		return (lhs.base() != rhs.base());
	}
}

#endif