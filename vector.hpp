#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdexcept>

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
		class iterator
		{
		public:
			typedef typename A::difference_type difference_type;
			typedef typename A::value_type value_type;
			typedef typename A::reference reference;
			typedef typename A::pointer pointer;
		private:
			pointer ptr;
			unsigned int sz;
			int index;
		public:
			iterator(T *arr, unsigned int sz, int begin): ptr(arr), sz(sz)
			{
				if (begin)
					this->index = 0;
				else
					this->index = sz;
			}
			~iterator() {}
			T &operator*() const
			{
				if (this->index == (int)this->sz)
					throw std::out_of_range("Trying to access wrong index");
				return (ptr[this->index]);
			}
			iterator& operator+=(int am)
			{
				if ((this->index + am) > (int)this->sz)
					throw std::out_of_range("Trying to add more than limit");
				this->index += am;
				return (*this);
			}
			iterator& operator-=(int am)
			{
				if ((this->index - am) < 0)
					throw std::out_of_range("Trying to minus more than limit");
				this->index -= am;
				return (*this);
			}
			iterator operator+(int am)
			{
				iterator tmp = *this;
				tmp += am;
				return (tmp);
			}
			iterator operator-(int am)
			{
				iterator tmp = *this;
				tmp -= am;
				return (tmp);
			}
			iterator& operator++()
			{
				if (this->index >= (int)this->sz)
					throw std::out_of_range("Trying to increment more than limit");
				this->index++;
				return (*this);
			}
			iterator& operator++(int)
			{
				iterator tmp = *this;
				++*this;
				return (tmp);
			}
			iterator& operator--()
			{
				if (this->index == 0)
					throw std::out_of_range("Trying to decrement more than limit");
				this->index--;
				return (*this);
			}
			iterator& operator--(int)
			{
				iterator tmp = *this;
				--(*this);
				return (tmp);
			}
			bool operator==(const iterator &t) const
			{
        		return t.index == this->index;
			}
			bool operator!=(const iterator &t) const
			{
				return t.index != this->index;
			}
		};
	private:
		T *arr;
		size_type capacity;
		size_type sz;
	public:
		vector() : arr(new T[1]), capacity(1), sz(0)
		{
		}
		vector(iterator begin, iterator end)
		{
			for (iterator it = begin; it != end; ++it)
			{
				if (this->sz == this->capacity)
				{
					this->reserve(2 * this->capacity);
				}
				this->arr[sz] = *it;
				sz++;
			}
		}
		void	push_back(T element)
		{
			if (this->sz == this->capacity)
			{
				this->reserve(2 * this->capacity);
			}
			this->arr[sz] = element;
			sz++;
		}
		void	reserve(size_type am)
		{
			if (am > this->capacity)
			{
				T *temp = new T[am];
				for (size_type i = 0; i < this->capacity; ++i)
					temp[i] = this->arr[i];
				delete[] this->arr;
				capacity = am;
				this->arr = temp;
			}
		}
		size_type size()
		{
			return (this->sz);
		}
		iterator begin()
		{
			return (iterator(this->arr, this->sz, 1));
		}
		iterator end()
		{
			return (iterator(this->arr, this->sz, 0));
		}
	};
}

#endif