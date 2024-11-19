#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

BitcoinExchange::BitcoinExchange(std::string file_name) {
	std::ifstream file(file_name);
	if (!file.is_open()) {
		std::cerr << "File Error\n";
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::vector<std::string> row;
		std::stringstream ss(line);

		std::string cell;
		while (std::getline(ss, cell, ',')) {
			
		}
	}
	file.close();
}
BitcoinExchange::~BitcoinExchange() {}

float BitcoinExchange::CalculatePrice(std::string input_file) {
	std::ifstream file(input_file);
	if (!file.is_open()) {
		std::cerr << "File Error\n";
		return 1;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::vector<std::string> row;
		std::stringstream ss(line);

		std::string cell;
		while (std::getline(ss, cell, '|')) {
			row.push_back(cell);
		}
		BitcoinExchange bitcoinExchange("data.csv");
		for(unsigned long i = 0; i < row.size(); i++) {
			std::cout << bitcoinExchange.CalculatePrice(row);
			std::cout << row[i] << ' ';
		}
		std::cout << std::endl;
	}
	file.close();
}

BitcoinExchange::NotPositiveNumber::NotPositiveNumber() : logic_error("Error: not a positive number.\n") {}

BitcoinExchange::TooLargeNumber::TooLargeNumber() : logic_error("Error: too large a number.\n") {}

BitcoinExchange::BadInput::BadInput(std::string date) : logic_error("Error: bad input => " + date + "\n") {}