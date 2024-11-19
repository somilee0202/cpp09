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
		bitcoinExchange.CalculatePrice(argv[1]);
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	// std::ifstream file(argv[1]);
	// if (!file.is_open()) {
	// 	std::cerr << "File Error\n";
	// 	return 1;
	// }
	// std::string line;
	// while (std::getline(file, line)) {
	// 	std::vector<std::string> row;
	// 	std::stringstream ss(line);

	// 	std::string cell;
	// 	while (std::getline(ss, cell, '|')) {
	// 		row.push_back(cell);
	// 	}
	// 	BitcoinExchange bitcoinExchange("data.csv");
	// 	for(unsigned long i = 0; i < row.size(); i++) {
	// 		std::cout << bitcoinExchange.CalculatePrice(row);
	// 		std::cout << row[i] << ' ';
	// 	}
	// 	std::cout << std::endl;
	// }
	// file.close();
	return 0;
}