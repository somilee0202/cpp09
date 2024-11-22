#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
	if(argc < 2 || argc > 10000) {
		std::cout << "Error\n";
		return 1;
	}
	try {
		PmergeMe pm(argv, argc);
		pm.DoPmerge();
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}