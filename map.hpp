#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "pair.hpp"
#include "BinaryTree.hpp"
#include "type_traits.hpp"
#include <memory>

namespace ft
{
	template<typename Arg1, typename Arg2, typename Result>
    struct binary_function
    {
      typedef Arg1 	first_argument_type; 
      typedef Arg2 	second_argument_type;
      typedef Result 	result_type;
    };
	template<typename Tp>
    struct less : public ft::binary_function<Tp, Tp, bool>
    {
      bool
      operator()(const Tp& x, const Tp& y) const
      { return x < y; }
    };
	template <typename Key, typename T, typename Compare = ft::less<Key>,
	    typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<Key, T>						value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef ft::BinaryTree<value_type, Compare>			binary_tree;
		typedef	typename binary_tree::iterator				iterator;
		typedef typename binary_tree::reverse_iterator		reverse_iterator;
		typedef typename binary_tree::const_iterator			const_iterator;
		typedef typename binary_tree::const_reverse_iterator	const_reverse_iterator;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef size_t		 								size_type;
      	typedef ptrdiff_t									difference_type;
		class value_compare : ft::binary_function<value_type, value_type, bool>
		{
			friend class map<key_type, mapped_type, key_compare, Alloc>;
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c)
			{

			}
		public:
			bool operator() (const value_type& x, const value_type& y) const
			{
				return (comp(x.first, y.first));
			}
		};
		map()
		{
		}
		explicit map( const key_compare& comp,
              const allocator_type& alloc = allocator_type())
		: alloc(alloc), comp(comp)
		{
		}
		template< class InputIt >
		map( InputIt first, InputIt last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
		: alloc(alloc), comp(comp)
		{
			this->insert(first, last);
		}
		map(const map& other) : alloc(other.alloc), comp(other.comp)
		{
			this->insert(other.begin(), other.end());
		}
		~map()
		{
			this->clear();
		}
		map& operator=(const map& other)
		{
			if (this != &other)
			{
				this->clear();
				this->insert(other.begin(), other.end());
			}
			return (*this);
		}
		key_compare key_comp() const
		{
			return (key_compare());
		}
		value_compare value_comp() const
		{
			return (value_compare(key_compare()));
		}
		mapped_type& operator[] (const key_type& key)
		{
			if (this->find(key) == this->end())
				this->insert(ft::make_pair(key, mapped_type()));
			iterator tmp = this->find(key);
			return ((*tmp).second);
		} 
		iterator find (const key_type& key)
		{
			return (iterator(this->bst.findKey(key), this->bst.first, this->bst.last, this->bst.end)); 
		}
		const_iterator find (const key_type& key) const
		{
			return (const_iterator(this->bst.findKey(key), this->bst.first, this->bst.last, this->bst.end));
		}
		const_iterator lower_bound(const key_type& key) const
		{
			for (const_iterator it = this->begin(); it != this->end(); it++)
			{
				if (!this->comp((*it).first, key))
					return (it);
			}
			return (this->end());
		}
		iterator lower_bound(const key_type& key)
		{
			for (iterator it = this->begin(); it != this->end(); it++)
			{
				if (!this->comp((*it).first, key))
					return (it);
			}
			return (this->end());
		}
		const_iterator upper_bound(const key_type& key) const
		{
			for (const_iterator it = this->begin(); it != this->end(); it++)
			{
				if (this->comp(key, (*it).first))
					return (it);
			}
			return (this->end());
		}
		iterator upper_bound(const key_type& key)
		{
			for (iterator it = this->begin(); it != this->end(); it++)
			{
				if (this->comp(key, (*it).first))
					return (it);
			}
			return (this->end());
		}
		size_type count (const key_type& key) const
		{
			if (this->find(key) != this->end())
					return (1);
			return (0);
		}
		ft::pair<iterator,iterator> equal_range( const Key& key )
		{
			return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
		}
		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
		{
			return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
		}
		bool empty() const
		{
			return (this->bst.first == this->bst.last);
		}
		size_type size() const
		{
			return (this->bst.size());
		}
		size_type max_size() const
		{
			return (this->bst.max_size());
		}
		ft::pair<iterator,bool>	insert(const value_type& value)
		{
			return (this->bst.insertPair(value));
		}
		iterator	insert(iterator position, const value_type& value)
		{
			(void)position;
			return (this->bst.insertPair(value).first);
		}
		template< class InputIt >
		void insert( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
		{
			for (InputIt it = first; it != last; it++)
				this->insert(*it);
		}
		void clear()
		{
			this->erase(this->begin(), this->end());
		}
		void erase(iterator pos)
		{
			this->erase((*pos).first);
		}
		size_type erase(const key_type& key)
		{
			if (this->find(key) != this->end())
			{
				this->bst.removeKey(key);
				return (1);
			}
			return (0);
		}
		void erase(iterator first, iterator last)
		{
			for (iterator it = first; it != last; it++)
			{
				this->erase((*it).first);
			}
		}
		iterator begin()
		{
			return (iterator(this->bst.first, this->bst.first, this->bst.last, this->bst.end));
		}
		iterator end()
		{
			return (iterator(this->bst.end, this->bst.first, this->bst.last, this->bst.end));
		}
		const_iterator begin() const
		{
			return (const_iterator(this->bst.first, this->bst.first, this->bst.last, this->bst.end));
		}
		const_iterator end() const
		{
			return (const_iterator(this->bst.end, this->bst.first, this->bst.last, this->bst.end));
		}
		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin()));
		}
		void swap(map& m)
		{
			this->bst.swap(m.bst);
			allocator_type tmp_alloc = this->alloc;
			key_compare tmp_comp = this->comp;
			this->alloc = m.alloc;
			this->comp = m.comp;
			m.alloc = tmp_alloc;
			m.comp = tmp_comp;
		}
	private:
		binary_tree		bst;
		allocator_type	alloc;
		key_compare		comp;
	};
	template<typename Key, typename Tp, typename Compare, typename Alloc>
    inline bool
    operator==(const map<Key, Tp, Compare, Alloc>& x,
	       const map<Key, Tp, Compare, Alloc>& y)
    {
		return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
    }

	template<typename Key, typename Tp, typename Compare, typename Alloc>
    inline bool
    operator<(const ft::map<Key, Tp, Compare, Alloc>& x,
	      const ft::map<Key, Tp, Compare, Alloc>& y)
    { return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

	template<typename Key, typename Tp, typename Compare, typename Alloc>
		inline bool
		operator!=(const ft::map<Key, Tp, Compare, Alloc>& x,
			const ft::map<Key, Tp, Compare, Alloc>& y)
		{ return !(x == y); }

	template<typename Key, typename Tp, typename Compare, typename Alloc>
		inline bool
		operator>(const ft::map<Key, Tp, Compare, Alloc>& x,
			const ft::map<Key, Tp, Compare, Alloc>& y)
		{ return y < x; }

	template<typename Key, typename Tp, typename Compare, typename Alloc>
		inline bool
		operator<=(const ft::map<Key, Tp, Compare, Alloc>& x,
			const ft::map<Key, Tp, Compare, Alloc>& y)
		{ return !(y < x); }

	template<typename Key, typename Tp, typename Compare, typename Alloc>
		inline bool
		operator>=(const ft::map<Key, Tp, Compare, Alloc>& x,
			const ft::map<Key, Tp, Compare, Alloc>& y)
		{ return !(x < y); }

	template<typename Key, typename Tp, typename Compare, typename Alloc>
		inline void
		swap(ft::map<Key, Tp, Compare, Alloc>& x,
		ft::map<Key, Tp, Compare, Alloc>& y)
		{ x.swap(y); }
}

#endif