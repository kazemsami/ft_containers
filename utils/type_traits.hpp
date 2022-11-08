#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
	template<bool B, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<typename T, T V>
	struct integral_constant
	{
		static const bool value = V;
		typedef T			value_type;
		typedef integral_constant<T, V>   type;
	};

	typedef integral_constant<bool, true>     true_type;

  	typedef integral_constant<bool, false>    false_type;

	template<typename>
		struct is_integral_helper
		: public false_type { };

	template<>
		struct is_integral_helper<bool>
		: public true_type { };

	template<>
		struct is_integral_helper<char>
		: public true_type { };

	template<>
		struct is_integral_helper<signed char>
		: public true_type { };

	template<>
		struct is_integral_helper<unsigned char>
		: public true_type { };

	template<>
		struct is_integral_helper<wchar_t>
		: public true_type { };

	template<>
		struct is_integral_helper<short>
		: public true_type { };

	template<>
		struct is_integral_helper<unsigned short>
		: public true_type { };

	template<>
		struct is_integral_helper<int>
		: public true_type { };

	template<>
		struct is_integral_helper<unsigned int>
		: public true_type { };

	template<>
		struct is_integral_helper<long>
		: public true_type { };

	template<>
		struct is_integral_helper<unsigned long>
		: public true_type { };

	template<>
		struct is_integral_helper<long long>
		: public true_type { };

	template<>
		struct is_integral_helper<unsigned long long>
		: public true_type { };

	template< class T > struct remove_cv                   { typedef T type; };
	template< class T > struct remove_cv<const T>          { typedef T type; };
	template< class T > struct remove_cv<volatile T>       { typedef T type; };
	template< class T > struct remove_cv<const volatile T> { typedef T type; };
	
	template<typename T>
    struct is_integral
    : public is_integral_helper<typename ft::remove_cv<T>::type>::type
    { };

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt1, class InputIt2>
	inline bool
	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
	  for (; first1 != last1; ++first1, (void) ++first2)
	    if (!(*first1 == *first2))
	      return false;
	  return true;
	}
	template<class T, class U>
	struct is_same : ft::false_type {};
	
	template<class T>
	struct is_same<T, T> : ft::true_type {};
}

#endif