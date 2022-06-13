#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
	const int size = 5;
	ft::vector<int> vct(size);
	vct.push_back(5);
	vct.push_back(10);
	vct.push_back(7);
	vct.push_back(5);
	vct.push_back(3);
	ft::vector<int>::reverse_iterator it = vct.rbegin();
	ft::vector<int>::reverse_iterator mid_it;
	mid_it = it + 3;
	std::cout << *mid_it << std::endl;
}