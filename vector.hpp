#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "type_traits.hpp"
#include <stdexcept>
#include <limits>
#include <memory>

namespace ft
{
	template <class T, class A = std::allocator<T> >
	class vector
	{
	public:
		typedef A allocator_type;
		typedef typename A::value_type value_type;
		typedef typename A::reference reference;
		typedef typename A::difference_type difference_type;
		typedef typename A::size_type size_type;
		typedef typename A::pointer pointer;
		typedef ft::wrap_iter<pointer> iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
	private:
		pointer arr;
		size_type capa;
		size_type sz;
		allocator_type end_cap;
		allocator_type& alloc()
		{
			return (end_cap);
		}
	public:
		vector() : arr(new T[0]), capa(0), sz(0), end_cap(allocator_type())
		{
		}
		vector(size_type sz, const T& value = T(), const allocator_type& alloc = allocator_type()) : arr(new T[sz]), capa(sz), sz(sz), end_cap(alloc)
		{
			for (size_type i = 0; i < sz; ++i)
				arr[i] = value;
		}
		vector(iterator begin, iterator end, const allocator_type& alloc = allocator_type()) : arr(new T[0]), capa(0), sz(0), end_cap(alloc)
		{
			size_type i;

			i = 0;
			for (iterator it = begin; it != end; ++it)
				++i;
			this->reserve(i);
			for (iterator it = begin; it != end; ++it)
				arr[this->sz++] = *it; 
		}
		vector(const allocator_type &a) : arr(new T[0]), capa(0), sz(0), end_cap(a)
		{
		}
		vector(const vector& other)
		{
			if (this != &other)
			{
				this->capa = other.capa;
				this->sz = other.sz;
				this->end_cap = other.end_cap;
				this->arr = new T[other.capa];
				for (size_type i = 0; i < other.capa; ++i)
					this->arr[i] = other.arr[i];
			}
		}
		~vector()
		{
			delete [] this->arr;
		}
		T* data()
		{
			return (this->arr);
		}
		const T* data() const
		{
			return (this->arr);
		}
		void assign( size_type count, const T& value )
		{
			this->resize(count);
			for (size_type i = 0; i < count; i++)
			{
				this->arr[i] = value;
			}
		}
		void assign(iterator first, iterator last)
		{
			size_type i;
			i = 0;
			for (iterator it = first; it != last; it++)
				i++;
			this->resize(i);
			i = 0;
			for (iterator it = first; it != last; it++)
				this->arr[i++] = *it;
		}
		vector& operator=(const vector& other)
		{
			if (this != &other)
			{
				this->capa = other.capa;
				this->sz = other.sz;
				this->end_cap = other.end_cap;
				delete [] this->arr;
				this->arr = new T[other.capa];
				for (size_type i = 0; i < other.capa; ++i)
					this->arr[i] = other.arr[i];
			}
			return (*this);
		}
		allocator_type get_allocator() const
		{
			return (end_cap);
		}
		reference	at(size_type pos)
		{
			if (pos >= this->sz)
				throw std::out_of_range("vector");
			return (this->arr[pos]);
		}
		void	push_back(T element)
		{
			if (this->sz == this->capa)
			{
				if (this->capa == 0)
					this->reserve(1);
				else
					this->reserve(2 * this->capa);
			}
			this->arr[sz] = element;
			sz++;
		}
		iterator	erase(iterator pos)
		{
			for (iterator it = pos; it != this->end() - 1; it++)
			{
				*it = *(it + 1);
			}
			this->sz--;
			return (pos);
		}
		iterator	erase(iterator begin, iterator end)
		{
			int	i;

			i = 0;
			for (iterator it = begin; it != end; it++)
				++i;
			for (iterator it = end; it != this->end(); it++)
			{
				*(it - i) = *it;
			}
			this->sz -= i;
			return (begin);
		}
		void	clear()
		{
			this->sz = 0;
		}
		void	reserve(size_type am)
		{
			if (am > this->capa)
			{
				T *temp = new T[am];
				for (size_type i = 0; i < this->capa; ++i)
					temp[i] = this->arr[i];
				delete[] this->arr;
				this->capa = am;
				this->arr = temp;
			}
		}
		size_type	capacity() const
		{
			return (this->capa);
		}
		size_type	max_size() const
		{
			return (std::min<size_type>(this->end_cap.max_size(), std::numeric_limits<difference_type>::max()));
		}
		T&	back()
		{
			return (this->arr[this->sz - 1]);
		}
		T&	front()
		{
			return (this->arr[0]);
		}
		void	resize(size_type n)
		{
			if (n < this->sz)
				for (size_type i = n; i < this->sz; ++i)
					this->arr[i] = 0;
			else if (this->capa < n && this->capa * 2 > n)
				this->reserve(this->capa * 2);
			else
				this->reserve(n);
			this->sz = n;
		}
		bool	empty() const
		{
			return (this->sz == 0);
		}
		size_type size()
		{
			return (this->sz);
		}
		iterator begin()
		{
			return (iterator(this->arr));
		}
		iterator end()
		{
			return (iterator(this->arr + this->sz));
		}
		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}
		reference  operator[](difference_type n) const 
		{
			return *(this->arr + n);
		}
	};
}

#endif