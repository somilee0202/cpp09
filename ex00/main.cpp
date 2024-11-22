#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
	if(argc != 2) {
		std::cerr << "Input Error\n";
		return 1;
	}
	try {
		BitcoinExchange bitcoinExchange("data.csv");
		bitcoinExchange.getExchange(argv[1]);
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}