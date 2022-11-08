#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <stack>
#include <vector>
#include "./map/map.hpp"
#include "./stack/stack.hpp"
#include "./vector/vector.hpp"
#include <ctime>

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public TESTED_CONT::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename TESTED_CONT::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

template<typename T>
void	printVecInfo(T& vec)
{
	std::cout << vec.empty() << std::endl;
	std::cout << vec.size() << std::endl;
	std::cout << vec.max_size() << std::endl;
	for (typename T::iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	for (typename T::reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
	{
		std::cout << *it << std::endl;
	}
}

template<typename T>
void	printMapInfo(T& mp)
{
	std::cout << mp.empty() << std::endl;
	std::cout << mp.size() << std::endl;
	std::cout << mp.max_size() << std::endl;
	for (typename T::iterator it = mp.begin(); it != mp.end(); it++)
	{
		std::cout << it->first << ":" << it->second << std::endl;
	}
	for (typename T::reverse_iterator it = mp.rbegin(); it != mp.rend(); it++)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
}

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
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	try {
		stack_int.push(5);
		std::cout << stack_int.top() << std::endl;
		std::cout << stack_int.empty() << std::endl;
		std::cout << stack_int.size() << std::endl;
		stack_int.push(10);
		std::cout << stack_int.top() << std::endl;
		std::cout << stack_int.empty() << std::endl;
		std::cout << stack_int.size() << std::endl;
		stack_int.pop();
		std::cout << stack_int.top() << std::endl;
		std::cout << stack_int.empty() << std::endl;
		std::cout << stack_int.size() << std::endl;
		{
			TESTED_CONT::stack<int> cpy(stack_int);
			std::cout << stack_int.top() << std::endl;
			std::cout << stack_int.empty() << std::endl;
			std::cout << stack_int.size() << std::endl;
		}
		{
			TESTED_CONT::stack<int> cpy;
			cpy = stack_int;
			std::cout << stack_int.top() << std::endl;
			std::cout << stack_int.empty() << std::endl;
			std::cout << stack_int.size() << std::endl;
		}
		printVecInfo(vector_int);
		vector_int.push_back(5);
		printVecInfo(vector_int);
		std::cout << vector_int.back() << std::endl;
		std::cout << vector_int.front() << std::endl;
		vector_int.assign(5, 10);
		printVecInfo(vector_int);
		std::cout << vector_int.back() << std::endl;
		std::cout << vector_int.front() << std::endl;
		std::cout << vector_int.at(4) << std::endl;
		TESTED_CONT::vector<int> vec;
		printVecInfo(vec);
		vec = vector_int;
		printVecInfo(vec);
		std::cout << vec.back() << std::endl;
		std::cout << vec.front() << std::endl;
		std::cout << vec.at(4) << std::endl;
		TESTED_CONT::vector<int> vec2(vec);
		printVecInfo(vec2);
		std::cout << vec2.back() << std::endl;
		std::cout << vec2.front() << std::endl;
		std::cout << vec2.at(4) << std::endl;
		vector_int.erase(vector_int.begin(), vector_int.end());
		printVecInfo(vector_int);
		vector_int.assign(vec.begin(), vec.end());
		printVecInfo(vector_int);
		std::cout << vector_int.back() << std::endl;
		std::cout << vector_int.front() << std::endl;
		std::cout << vector_int.at(4) << std::endl;
		vector_int.insert(vector_int.begin() + 1, 4);
		printVecInfo(vector_int);
		std::cout << vector_int.back() << std::endl;
		std::cout << vector_int.front() << std::endl;
		std::cout << vector_int.at(1) << std::endl;
		vector_int.insert(vector_int.begin() + 1, vec.begin(), vec.end());
		printVecInfo(vector_int);
		std::cout << vector_int.back() << std::endl;
		std::cout << vector_int.front() << std::endl;
		std::cout << vector_int.at(1) << std::endl;
		vector_int.clear();
		printVecInfo(vector_int);
		vector_int = vec;
		vector_int.insert(vector_int.begin(), 10, 5);
		printVecInfo(vector_int);
		std::cout << vector_int.back() << std::endl;
		std::cout << vector_int.front() << std::endl;
		vector_int.erase(vector_int.begin() + 1);
		printVecInfo(vector_int);
		std::cout << vector_int.back() << std::endl;
		std::cout << vector_int.front() << std::endl;
		vector_int.pop_back();
		printVecInfo(vector_int);
		std::cout << vector_int.back() << std::endl;
		std::cout << vector_int.front() << std::endl;
		vector_int.reserve(100);
		printVecInfo(vector_int);
		vector_int.reserve(1);
		printVecInfo(vector_int);
		vector_int.resize(5, 10);
		printVecInfo(vector_int);
		vector_int.resize(10, 5);
		printVecInfo(vector_int);
		int *data = vector_int.data();
		std::cout << data[0] << std::endl;
		
		printVecInfo(vector_str);
		vector_str.push_back("sup");
		printVecInfo(vector_str);
		std::cout << vector_str.back() << std::endl;
		std::cout << vector_str.front() << std::endl;
		vector_str.assign(5, "bro");
		printVecInfo(vector_str);
		std::cout << vector_str.back() << std::endl;
		std::cout << vector_str.front() << std::endl;
		std::cout << vector_str.at(4) << std::endl;
		TESTED_CONT::vector<std::string> vecstr;
		printVecInfo(vecstr);
		vecstr = vector_str;
		printVecInfo(vecstr);
		std::cout << vecstr.back() << std::endl;
		std::cout << vecstr.front() << std::endl;
		std::cout << vecstr.at(4) << std::endl;
		TESTED_CONT::vector<std::string> vecstr2(vecstr);
		printVecInfo(vecstr2);
		std::cout << vecstr2.back() << std::endl;
		std::cout << vecstr2.front() << std::endl;
		std::cout << vecstr2.at(4) << std::endl;
		vector_str.erase(vector_str.begin(), vector_str.end());
		printVecInfo(vector_str);
		vector_str.assign(vecstr.begin(), vecstr.end());
		printVecInfo(vector_str);
		std::cout << vector_str.back() << std::endl;
		std::cout << vector_str.front() << std::endl;
		std::cout << vector_str.at(4) << std::endl;
		vector_str.insert(vector_str.begin() + 1, "hi");
		printVecInfo(vector_str);
		std::cout << vector_str.back() << std::endl;
		std::cout << vector_str.front() << std::endl;
		std::cout << vector_str.at(1) << std::endl;
		vector_str.insert(vector_str.begin() + 1, vecstr.begin(), vecstr.end());
		printVecInfo(vector_str);
		std::cout << vector_str.back() << std::endl;
		std::cout << vector_str.front() << std::endl;
		std::cout << vector_str.at(1) << std::endl;
		vector_str.clear();
		printVecInfo(vector_str);
		vector_str = vecstr;
		vector_str.insert(vector_str.begin(), 10, "yo");
		printVecInfo(vector_str);
		std::cout << vector_str.back() << std::endl;
		std::cout << vector_str.front() << std::endl;
		vector_str.erase(vector_str.begin() + 1);
		printVecInfo(vector_str);
		std::cout << vector_str.back() << std::endl;
		std::cout << vector_str.front() << std::endl;
		vector_str.pop_back();
		printVecInfo(vector_str);
		std::cout << vector_str.back() << std::endl;
		std::cout << vector_str.front() << std::endl;
		vector_str.reserve(100);
		printVecInfo(vector_str);
		vector_str.reserve(1);
		printVecInfo(vector_str);
		vector_str.resize(5, "hello");
		printVecInfo(vector_str);
		vector_str.resize(10, "hey");
		printVecInfo(vector_str);
		std::string *datastr = vector_str.data();
		std::cout << datastr[0] << std::endl;

		TESTED_CONT::map<int, std::string> mp_test;
		mp_test.insert(TESTED_CONT::make_pair(5, "hello"));
		mp_test.insert(TESTED_CONT::make_pair(3, "hey"));
		mp_test.insert(TESTED_CONT::make_pair(2, "yo"));
		mp_test.insert(TESTED_CONT::make_pair(1, "sup"));
		mp_test.insert(TESTED_CONT::make_pair(0, "bro"));
		TESTED_CONT::pair<TESTED_CONT::map<int, std::string>::iterator, bool> pr1 = mp_test.insert(TESTED_CONT::make_pair(6, "lmao"));
		std::cout << pr1.first->first << pr1.first->second << pr1.second << std::endl;
		std::cout << mp_test.at(3) << std::endl;
		printMapInfo(mp_test);
		TESTED_CONT::map<int, std::string> tmp_mp;
		tmp_mp = mp_test;
		printMapInfo(tmp_mp);
		mp_test.clear();
		printMapInfo(mp_test);
		TESTED_CONT::map<int, std::string> tmp_mp2(tmp_mp);
		printMapInfo(tmp_mp2);
		mp_test = tmp_mp2;
		std::cout << mp_test.count(2) << std::endl;
		std::cout << mp_test.upper_bound(3)->first << std::endl;
		std::cout << mp_test.lower_bound(2)->first << std::endl;
		std::cout << mp_test.find(3)->first << std::endl;
		TESTED_CONT::pair<TESTED_CONT::map<int, std::string>::iterator, TESTED_CONT::map<int, std::string>::iterator> pr = mp_test.equal_range(3);
		std::cout << pr.first->first << pr.second->first << std::endl;
		std::cout << mp_test.erase(5) << std::endl;
		printMapInfo(mp_test);
		mp_test.erase(mp_test.begin());
		printMapInfo(mp_test);
		mp_test.erase(mp_test.begin(), mp_test.end());
		printMapInfo(mp_test);
		mp_test.insert(tmp_mp2.begin(), tmp_mp2.end());
		printMapInfo(mp_test);
		mp_test.insert(mp_test.begin(), TESTED_CONT::make_pair(10, "lol"));
		printMapInfo(mp_test);
		mp_test.swap(tmp_mp2);
		printMapInfo(mp_test);
		printMapInfo(tmp_mp2);

		TESTED_CONT::map<std::string, int> mp_str;
		mp_str.insert(TESTED_CONT::make_pair("hey", 0));
		mp_str.insert(TESTED_CONT::make_pair("hi", 5));
		mp_str.insert(TESTED_CONT::make_pair("yo", 3));
		mp_str.insert(TESTED_CONT::make_pair("sup", 23));
		mp_str.insert(TESTED_CONT::make_pair("hello", 11));
		TESTED_CONT::pair<TESTED_CONT::map<std::string, int>::iterator, bool> prstr1 = mp_str.insert(TESTED_CONT::make_pair("bro", 55));
		std::cout << prstr1.first->first << prstr1.first->second << prstr1.second << std::endl;
		std::cout << mp_str.at("yo") << std::endl;
		printMapInfo(mp_str);
		TESTED_CONT::map<std::string, int> tmp_mpstr;
		tmp_mpstr = mp_str;
		printMapInfo(tmp_mpstr);
		mp_str.clear();
		printMapInfo(mp_str);
		TESTED_CONT::map<std::string, int> tmp_mpstr2(tmp_mpstr);
		printMapInfo(tmp_mpstr2);
		mp_str = tmp_mpstr2;
		std::cout << mp_str.count("hi") << std::endl;
		std::cout << mp_str.upper_bound("hey")->first << std::endl;
		std::cout << mp_str.lower_bound("hello")->first << std::endl;
		std::cout << mp_str.find("sup")->first << std::endl;
		TESTED_CONT::pair<TESTED_CONT::map<std::string, int>::iterator, TESTED_CONT::map<std::string, int>::iterator> prstr = mp_str.equal_range("hey");
		std::cout << prstr.first->first << prstr.second->first << std::endl;
		std::cout << mp_str.erase("hey") << std::endl;
		printMapInfo(mp_str);
		mp_str.erase(mp_str.begin(), mp_str.end());
		printMapInfo(mp_str);
		mp_str.insert(tmp_mpstr2.begin(), tmp_mpstr2.end());
		printMapInfo(mp_str);
		mp_str.insert(mp_str.begin(), TESTED_CONT::make_pair("lol", 11));
		printMapInfo(mp_str);
		mp_str.swap(tmp_mpstr2);
		printMapInfo(mp_str);
		printMapInfo(tmp_mpstr2);
		mp_str.erase(mp_str.begin());
		printMapInfo(mp_str);
	}
	catch (std::exception &exp)
	{
		std::cerr << exp.what() << std::endl;
	}
	return (0);
}