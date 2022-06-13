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
		typedef typename A::const_reference const_reference;
		typedef typename A::size_type size_type;
		typedef typename A::pointer pointer;
		typedef typename A::const_pointer const_pointer;
		typedef ft::wrap_iter<pointer> iterator;
		typedef ft::wrap_iter<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	private:
		pointer _start;
		pointer _end;
		pointer _capa;
		allocator_type _alloc;
	public:
		explicit vector(size_type sz, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc)
		{
			this->_start = this->_alloc.allocate(sz);
			this->_capa = this->_start + sz;
			this->_end = this->_start;
			for (size_type i = 0; i < sz; i++)
			{
				this->_alloc.construct(this->_end, value);
				this->_end++;
			}
		}
		template <class InputIterator>
		vector(InputIterator begin, InputIterator end, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) : _alloc(alloc)
		{
			size_type i;

			i = 0;
			for (InputIterator it = begin; it != end; ++it)
				++i;
			this->_start = this->_alloc.allocate(i);
			this->_capa = this->_start + i;
			this->_end = this->_start;
			for (InputIterator it = begin; it != end; ++it)
			{
				this->_alloc.construct(this->_end, *it);
				this->_end++;
			}
		}
		explicit vector(const allocator_type &a = allocator_type()) : _start(NULL), _end(NULL), _capa(NULL), _alloc(a)
		{
		}
		vector(const vector& other) : _start(NULL), _end(NULL), _capa(NULL), _alloc(allocator_type())
		{
			if (this != &other)
			{
				this->insert(this->begin(), other.begin(), other.end());
			}
		}
		~vector()
		{
			this->clear();
			this->_alloc.deallocate(this->_start, this->capacity());
		}
		pointer data()
		{
			return (this->_start);
		}
		const pointer data() const
		{
			return (this->_start);;
		}
		iterator insert( iterator pos, const T& value )
		{
			difference_type diff = &(*pos) - this->_start;
			if (this->capacity() >= this->size() + 1)
			{
				for (size_type i = 0; i < this->size() - diff; i++)
				{
					if (i > 0)
						this->_alloc.destroy(this->_end - i);
					this->_alloc.construct(this->_end - i, *(this->_end - i - 1));
				}
				this->_alloc.destroy(&(*pos));
				this->_alloc.construct(&(*pos), value);
				this->_end++;
			}
			else
			{
				if (this->capacity() == 0)
					this->reserve(1);
				else
					this->reserve(2 * this->capacity());
				pos = iterator(this->_start + diff);
				for (size_type i = 0; i < this->size() - diff; i++)
				{
					if (i > 0)
						this->_alloc.destroy(this->_end - i);
					this->_alloc.construct(this->_end - i, *(this->_end - i - 1));
				}
				this->_alloc.destroy(&(*pos));
				this->_alloc.construct(&(*pos), value);
				this->_end++;
			}
			return (pos);
		}
		void insert( iterator pos, size_type count, const T& value )
		{
			difference_type diff = &(*pos) - this->_start;
			if (this->capacity() >= this->size() + count)
			{
				for (size_type i = 0; i < this->size() - diff; i++)
				{
					if (i > 0)
						this->_alloc.destroy(this->_end - i + count);
					this->_alloc.construct(this->_end - i + count - 1, *(this->_end - i - 1));
				}
				for (size_type i = 0; i < count; ++i)
				{
					this->_alloc.destroy(&(*(pos + i)));
					this->_alloc.construct(&(*(pos + i)), value);
				}
				this->_end += count;
			}
			else
			{
				this->reserve(this->size() + count);
				pos = iterator(this->_start + diff);
				for (size_type i = 0; i < this->size() - diff; i++)
				{
					if (i > 0)
						this->_alloc.destroy(this->_end - i + count);
					this->_alloc.construct(this->_end - i + count - 1, *(this->_end - i - 1));
				}
				for (size_type i = 0; i < count; ++i)
				{
					this->_alloc.destroy(&(*(pos + i)));
					this->_alloc.construct(&(*(pos + i)), value);
				}
				this->_end += count;
			}
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
		{
			difference_type diff = &(*pos) - this->_start;
			size_type count = 0;
			for (InputIt it = first; it != last; it++)
				count++;
			if (this->capacity() >= this->size() + count)
			{
				for (size_type i = 0; i < this->size() - diff; i++)
				{
					if (i > 0)
						this->_alloc.destroy(this->_end - i + count);
					this->_alloc.construct(this->_end - i + count - 1, *(this->_end - i - 1));
				}
				for (size_type i = 0; i < count; ++i)
				{
					this->_alloc.destroy(&(*(pos + i)));
					this->_alloc.construct(&(*(pos + i)), *first);
					first++;
				}
				this->_end += count;
			}
			else
			{
				this->reserve(this->size() + count);
				pos = iterator(this->_start + diff);
				for (size_type i = 0; i < this->size() - diff; i++)
				{
					if (i > 0)
						this->_alloc.destroy(this->_end - i + count);
					this->_alloc.construct(this->_end - i + count - 1, *(this->_end - i - 1));
				}
				for (size_type i = 0; i < count; ++i)
				{
					this->_alloc.destroy(&(*(pos + i)));
					this->_alloc.construct(&(*(pos + i)), *first);
					first++;
				}
				this->_end += count;
			}
		}
		void assign( size_type count, const T& value )
		{
			this->clear();
			if (this->capacity() >= count)
			{
				while (count--)
				{
					this->_alloc.construct(this->_end, value);
					this->_end++;
				}
			}
			else
			{
				this->clear();
				this->reserve(count);
				while (count--)
				{
					this->_alloc.construct(this->_end, value);
					this->_end++;
				}
			}
		}
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			size_type count;
			
			count = 0;
			for (InputIterator it = first; it != last; it++)
				count++;
			this->clear();
			if (this->capacity() >= count)
			{
				while (count--)
				{
					this->_alloc.construct(this->_end, *first);
					first++;
					this->_end++;
				}
			}
			else
			{
				this->clear();
				this->reserve(count);
				while (count--)
				{
					this->_alloc.construct(this->_end, *first);
					first++;
					this->_end++;
				}
			}
		}
		vector& operator=(const vector& other)
		{
			if (this != &other)
			{
				this->clear();
				this->insert(this->begin(), other.begin(), other.end());
			}
			return (*this);
		}
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}
		const_reference	at(size_type pos) const
		{
			if (pos >= this->size())
				throw std::out_of_range("vector");
			return *(this->_start + pos);
		}
		reference	at(size_type pos)
		{
			if (pos >= this->size())
				throw std::out_of_range("vector");
			return *(this->_start + pos);
		}
		void	swap(vector & vec)
		{
			pointer tmp_start = this->_start;
			pointer tmp_end = this->_end;
			pointer tmp_capa = this->_capa;
			allocator_type tmp_alloc = this->_alloc;

			this->_start = vec._start;
			this->_end = vec._end;
			this->_capa = vec._capa;
			this->_alloc = vec._alloc;

			vec._start = tmp_start;
			vec._end = tmp_end;
			vec._capa = tmp_capa;
			vec._alloc = tmp_alloc;
		}
		void	pop_back()
		{
			this->_alloc.destroy(&this->back());
			this->_end--;
		}
		void	push_back(const value_type& element)
		{
			if (this->size() == this->capacity())
			{
				if (this->capacity() == 0)
					this->reserve(1);
				else
				{
					this->reserve(2 * this->capacity());
				}
			}
			this->_alloc.construct(this->_end, element);
			this->_end++;
		}
		iterator	erase(iterator pos)
		{
			if (pos == this->end() - 1)
				this->_alloc.destroy(&(*pos));
			else
			{
				for (iterator i = pos; i != this->end() - 1; i++)
				{
					this->_alloc.destroy(&(*i));
					this->_alloc.construct(&(*i), *(i + 1));
				}
			}
			this->_end--;
			return (pos);
		}
		iterator	erase(iterator begin, iterator end)
		{
			size_type sz;
			
			sz = 0;
			for (iterator it = begin; it != end; it++)
				sz++;
			if (end == this->end())
			{
				for (iterator it = begin; it != end; it++)
					this->_alloc.destroy(&(*it));
			}
			else
			{
				for (iterator it = begin; it != end; it++)
					this->_alloc.destroy(&(*it));
				for (iterator it = begin; it != this->end() - sz; it++)
					this->_alloc.construct(&(*it), *(it + sz));
			}
			this->_end -= sz;
			return (begin);
		}
		void	clear()
		{
			size_type tmp = this->size();
			for (size_type i = 0; i < tmp; i++)
			{
				this->_alloc.destroy(this->_end - 1);
				this->_end--;
			}
		}
		void	reserve(size_type am)
		{
			if (am > this->capacity())
			{
				pointer tmp_start = this->_start;
				size_type tmp_capa = this->capacity();
				size_type sz = this->size();
				this->_start = this->_alloc.allocate(am);
				this->_end = this->_start;
				this->_capa = this->_start + am;
				for(size_type i = 0; i < sz; i++)
				{
					this->_alloc.construct(this->_end, *tmp_start);
					this->_end++;
					tmp_start++;
				}
				this->_alloc.deallocate(tmp_start - sz, tmp_capa);

			}
		}
		size_type	capacity() const
		{
			return (this->_capa - this->_start);
		}
		size_type	max_size() const
		{
			return (std::min<size_type>(this->_alloc.max_size(), std::numeric_limits<difference_type>::max()));
		}
		reference	back()
		{
			return (*(this->_end - 1));
		}
		reference	front()
		{
			return (*(this->_start));
		}
		const_reference	back() const
		{
			return (*(this->_end - 1));
		}
		const_reference	front() const
		{
			return (*(this->_start));
		}
		void	resize(size_type n, value_type value = value_type())
		{
			if (n < this->size())
			{
				size_type sz = this->size();
				for (size_type i = n; i < sz; ++i)
				{
					this->_alloc.destroy(this->_end - 1);
					this->_end--;
				}
			}
			else if (n > this->size())
				this->insert(this->end(), n - this->size(), value);
		}
		bool	empty() const
		{
			return (this->size() == 0);
		}
		size_type size() const
		{
			return (this->_end - this->_start);
		}
		iterator begin()
		{
			return (iterator(this->_start));
		}
		iterator end()
		{
			return (iterator(this->_end));
		}
		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}
		const_iterator begin() const
		{
			return (const_iterator(this->_start));
		}
		const_iterator end() const
		{
			return (const_iterator(this->_end));
		}
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin()));
		}
		reference  operator[](difference_type n)
		{
			return *(this->_start + n);
		}
		const_reference  operator[](difference_type n) const
		{
			return *(this->_start + n);
		}
	};
	template<typename Tp, typename Alloc>
    inline bool
    operator==(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
    { return (x.size() == y.size()
	      && std::equal(x.begin(), x.end(), y.begin())); }
	template<typename Tp, typename Alloc>
    inline bool
    operator!=(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
    { return (!(x == y)); }
	template<typename Tp, typename Alloc>
    inline bool
    operator<(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
    { return std::lexicographical_compare(x.begin(), x.end(),
					  y.begin(), y.end()); }
	template<typename Tp, typename Alloc>
    inline bool
    operator<=(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
    { return (!(y < x)); }
	template<typename Tp, typename Alloc>
    inline bool
    operator>(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
    { return (y < x); }
	template<typename Tp, typename Alloc>
    inline bool
    operator>=(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
    { return (!(x < y)); }
}

#endif