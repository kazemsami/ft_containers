#include <iostream>
#include "vector.hpp"
#include "map.hpp"
#include <vector>
#include <map>
#include <stack>

int		main(void)
{
	std::stack<std::string>:: mp;
	mp::
	mp[10] = "hello";
	mp[9] = "hello";

	for (ft::map<int, std::string>::iterator it = mp.begin(); it != mp.end(); it++)
	{
		std::cout << (*it).first << std::endl;
	}

	return (0);
}