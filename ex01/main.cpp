#include "RPN.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	if(argc != 2) {
		std::cout << "Error\n";
		return 1;
	}
	try {
		RPN rpn;
		std::cout << rpn.calculateRPN(std::string(argv[1])) << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}