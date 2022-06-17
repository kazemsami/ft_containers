#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container=ft::vector<T> >
	class stack
	{
	public:
		typedef typename Container::value_type		value_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
		typedef typename Container::size_type		size_type;
		typedef	Container							container_type;
		explicit stack( const Container& cont = Container() ) : c(cont)
		{
		}
		stack( const stack& other ) : c(other.c)
		{
		}
		stack& operator=( const stack& other )
		{
			if (this != &other)
			{
				this->c = other.c;
			}
			return (*this);
		}
		~stack()
		{
		}
		bool empty() const
		{
			return (this->c.empty());
		}
		size_type size() const
		{
			return (this->c.size());
		}
		reference top()
		{
			return (this->c.back());
		}
		const_reference top() const
		{
			return (this->c.back());
		}
		void push(const value_type& val)
		{
			this->c.push_back(val);
		}
		void pop()
		{
			this->c.pop_back();
		}
		template<typename Tp, typename Cont>
		friend bool
		operator==(const stack<Tp, Cont>& x, const stack<Tp, Cont>& y);

		template<typename Tp, typename Cont>
			friend bool
			operator<(const stack<Tp, Cont>& x, const stack<Tp, Cont>& y);

		template<typename Tp, typename Cont>
			friend bool
			operator!=(const stack<Tp, Cont>& x, const stack<Tp, Cont>& y);

		template<typename Tp, typename Cont>
			friend bool
			operator>(const stack<Tp, Cont>& x, const stack<Tp, Cont>& y);

		template<typename Tp, typename Cont>
			friend bool
			operator<=(const stack<Tp, Cont>& x, const stack<Tp, Cont>& y);

		template<typename Tp, typename Cont>
			friend bool
			operator>=(const stack<Tp, Cont>& x, const stack<Tp, Cont>& y);
	protected:
		container_type c;
	};

	template<typename Tp, typename Container>
		inline bool
		operator==(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
		{ return x.c == y.c; }

	template<typename Tp, typename Container>
		inline bool
		operator<(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
		{ return x.c < y.c; }

	template<typename Tp, typename Container>
		inline bool
		operator!=(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
		{ return !(x == y); }

	template<typename Tp, typename Container>
		inline bool
		operator>(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
		{ return y < x; }

	template<typename Tp, typename Container>
		inline bool
		operator<=(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
		{ return !(y < x); }

	template<typename Tp, typename Container>
		inline bool
		operator>=(const stack<Tp, Container>& x, const stack<Tp, Container>& y)
		{ return !(x < y); }
}
#endif