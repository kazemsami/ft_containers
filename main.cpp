#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
	ft::vector<int> test(9, 10);
	ft::vector<int> vec;
	vec.assign(10, 6);
	std::cout << vec.capacity() << std::endl;
	std::cout << vec.size() << std::endl;
	vec.assign(5, 6);
	std::cout << vec.capacity() << std::endl;
	std::cout << vec.size() << std::endl;
	vec.resize(10);
	std::cout << vec.capacity() << std::endl;
	std::cout << vec.size() << std::endl;
	ft::vector<int>::iterator begin = vec.begin();
	ft::vector<int>::iterator end = vec.end();
	for (ft::vector<int>::iterator it = begin; it != end; it++)
	{
		std::cout << *it << std::endl;
	}
}