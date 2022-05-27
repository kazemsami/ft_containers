#include <iostream>
#include "vector.hpp"

int main()
{
	ft::vector<int> vec;
	vec.push_back(5);
	vec.push_back(10);
	vec.push_back(15);
	vec.push_back(14);
	ft::vector<int>::iterator begin = vec.begin();
	ft::vector<int>::iterator end = vec.begin();
	std::cout << *(it + 3) << std::endl;
}