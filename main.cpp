#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <stack>
#include <vector>
#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <ctime>

#include <stdlib.h>

#define MAX_RAM 4294967299
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	TESTED_CONT::vector<std::string> vector_str;
	TESTED_CONT::vector<int> vector_int;
	TESTED_CONT::stack<int> stack_int;
	TESTED_CONT::vector<Buffer> vector_buffer;
	TESTED_CONT::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	TESTED_CONT::map<int, int> map_int;
	time_t start, end;

	time(&start);

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	time(&end);

	std::cout << "It took " << end - start << " seconds to push back " << COUNT << " buffers in vector" << std::endl;


	time(&start);

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	time(&end);
	std::cout << "It took " << end - start << " seconds to use vectors [](index) operator " << COUNT << " times" << std::endl;
	TESTED_CONT::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	time(&start);

	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(TESTED_CONT::make_pair(rand(), rand()));
	}
	time(&end);
	TESTED_CONT::map<int, int> test;
	std::cout << "It took " << end - start << " seconds to insert " << COUNT << " pairs in map" << std::endl;

	time(&start);

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	time(&end);
	std::cout << "It took " << end - start << " seconds to access or add " << 10000 << " pairs in map" << std::endl;
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	time(&start);
	{
		TESTED_CONT::map<int, int> copy = map_int;
	}
	time(&end);
	std::cout << "It took " << end - start << " seconds to assign " << map_int.size() << " pairs to new copy map" << std::endl;
	return (0);
}