#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <vector>

namespace ft
{
	template<typename Iterator>
    struct iterator_traits
    {
      typedef typename Iterator::iterator_category iterator_category;
      typedef typename Iterator::value_type        value_type;
      typedef typename Iterator::difference_type   difference_type;
      typedef typename Iterator::pointer           pointer;
      typedef typename Iterator::reference         reference;
    };
 	template<typename Tp>
    struct iterator_traits<Tp*>
    {
      typedef std::random_access_iterator_tag 	iterator_category;
      typedef Tp                         		value_type;
      typedef ptrdiff_t                   		difference_type;
      typedef Tp*                        		pointer;
      typedef Tp&                        		reference;
    };

  	template<typename Tp>
    struct iterator_traits<const Tp*>
    {
      typedef std::random_access_iterator_tag iterator_category;
      typedef Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef const Tp*                  pointer;
      typedef const Tp&                  reference;
    };

	template <class T>
	class reverse_iterator
	{
	public:
		typedef T                                        		iterator_type;
		typedef typename iterator_traits<T>::difference_type 	difference_type;
		typedef typename iterator_traits<T>::reference       	reference;
		typedef typename iterator_traits<T>::pointer         	pointer;
		typedef typename iterator_traits<T>::value_type			value_type;
		typedef typename iterator_traits<T>::iterator_category	iterator_category;
	private:
		iterator_type current;
	public:
		reverse_iterator(): current()
		{
		}
		explicit reverse_iterator(const iterator_type& arr): current(arr)
		{
		}
		template<typename Iter>
        reverse_iterator(const reverse_iterator<Iter>& i) : current(i.base())
		{
		}
		reverse_iterator(const reverse_iterator& x) : current(x.current)
		{ 
		}
		iterator_type base() const
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
	};
	template <typename T>
	inline bool operator!=(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <typename T, typename T2>
	inline bool operator!=(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T2> rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <typename T>
	inline bool operator==(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <typename T, typename T2>
	inline bool operator==(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T2> rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <typename T>
	inline bool operator>(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
	{
		return (rhs.base() > lhs.base());
	}
	template <typename T, typename T2>
	inline bool operator>(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T2> rhs)
	{
		return (rhs.base() > lhs.base());
	}
	template <typename T>
	inline bool operator<(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
	{
		return (rhs.base() < lhs.base());
	}
	template <typename T, typename T2>
	inline bool operator<(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T2> rhs)
	{
		return (rhs.base() < lhs.base());
	}
	template <typename T>
	inline bool operator>=(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
	{
		return (rhs.base() >= lhs.base());
	}
	template <typename T, typename T2>
	inline bool operator>=(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T2> rhs)
	{
		return (rhs.base() >= lhs.base());
	}
	template <typename T>
	inline bool operator<=(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
	{
		return (rhs.base() <= lhs.base());
	}
	template <typename T, typename T2>
	inline bool operator<=(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T2> rhs)
	{
		return (rhs.base() <= lhs.base());
	}
	template<typename Iterator>
    inline typename ft::reverse_iterator<Iterator>::difference_type
    operator-(const ft::reverse_iterator<Iterator>& lhs,
	      const ft::reverse_iterator<Iterator>& rhs)
    { return rhs.base() - lhs.base(); }

	template<typename Iterator, typename Iterator2>
    inline typename ft::reverse_iterator<Iterator>::difference_type
    operator-(const ft::reverse_iterator<Iterator>& lhs,
	      const ft::reverse_iterator<Iterator2>& rhs)
    { return rhs.base() - lhs.base(); }

  	template<typename Iterator>
    inline ft::reverse_iterator<Iterator>
    operator+(typename ft::reverse_iterator<Iterator>::difference_type
	      n, const ft::reverse_iterator<Iterator>& i)
    { return ft::reverse_iterator<Iterator>(i.base() - n); }

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
		wrap_iter(): ptr(pointer())
		{
		}
		explicit wrap_iter(const pointer& arr): ptr(arr)
		{
		}
		template<typename Iter>
        wrap_iter(const wrap_iter<Iter>& i) : ptr(i.base())
		{
		}
		~wrap_iter() {}
		pointer base() const
		{
			return (ptr);
		}
		reference operator*() const
		{
			return (*this->ptr);
		}
		pointer operator->() const
		{
			return (ptr);
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
		wrap_iter operator+(difference_type am) const
		{
			return (wrap_iter(ptr + am));
		}
		wrap_iter operator-(difference_type am) const
		{
			return (wrap_iter(ptr - am));
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
		reference  operator[](difference_type n) const 
		{
			return (ptr[n]);
		}
	};
	template <typename T>
	inline bool operator!=(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T*> rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <typename T, typename T2>
	inline bool operator!=(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T2*> rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <typename T>
	inline bool operator==(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T*> rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <typename T, typename T2>
	inline bool operator==(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T2*> rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <typename T>
	inline bool operator>(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T*> rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <typename T, typename T2>
	inline bool operator>(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T2*> rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <typename T>
	inline bool operator<(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T*> rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <typename T, typename T2>
	inline bool operator<(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T2*> rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <typename T>
	inline bool operator>=(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T*> rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <typename T, typename T2>
	inline bool operator>=(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T2*> rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <typename T>
	inline bool operator<=(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T*> rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template <typename T, typename T2>
	inline bool operator<=(const ft::wrap_iter<T*> lhs, const ft::wrap_iter<T2*> rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template<typename Iterator>
    inline typename ft::wrap_iter<Iterator>::difference_type
    operator-(const ft::wrap_iter<Iterator>& lhs,
	      const ft::wrap_iter<Iterator>& rhs)
    { return lhs.base() - rhs.base(); }

	template<typename Iterator, typename Iterator2>
    inline typename ft::wrap_iter<Iterator>::difference_type
    operator-(const ft::wrap_iter<Iterator>& lhs,
	      const ft::wrap_iter<Iterator2>& rhs)
    { return lhs.base() - rhs.base(); }

  	template<typename Iterator>
    inline ft::wrap_iter<Iterator>
    operator+(typename ft::wrap_iter<Iterator>::difference_type
	      n, const ft::wrap_iter<Iterator>& i)
    { return ft::wrap_iter<Iterator>(i.base() + n); }
}

#endif