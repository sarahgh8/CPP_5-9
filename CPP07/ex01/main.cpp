

#include "iter.hpp"



int main(void)
{
	int numbers[] = {1, 2, 3, 4};
	std::string words[] = {"one", "two", "three"};
	const int constNumbers[] = {10, 20, 30};

    const std::string constWords[] = {"one", "two", "three"};
	iter(numbers, 4, print<int>);
	iter(numbers, 4, byTwo<int>);
	iter(numbers, 4, print<int>);

	iter(words, 3, print<std::string>);
	iter(constNumbers, 3, print_const<int>);
	iter(constWords, 3, print_const<std::string>);

	return 0;
}
