#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>

BitcoinExchange::BitcoinExchange(std::string file_name) {
	std::ifstream file(file_name);
	if (!file.is_open()) {
		throw WrongDataFile();
	}
	std::string line;
	std::getline(file, line);
	std::stringstream ss(line);
	std::string date, value;
	if(!std::getline(ss, date, ',') || !std::getline(ss, value)) {
		throw WrongDataFile();
	}
	date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
	value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
	if(date != "date" || value != "exchange_rate") {
		throw WrongDataFile();
	}
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		double cost;
		if(!std::getline(ss, date, ',') || !(ss >> cost) || !checkDate(date)) {
			throw WrongDataFile();
		}
		coin_data.insert(std::pair<std::string, double>(date, cost));
	}
	file.close();
}
BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::checkDate(std::string date) {
	std::stringstream ss(date);
	char del1, del2;
	int year, month, day;
	ss >> year >> del1 >> month >> del2 >> day;
	if(ss.fail() || del1 != '-' || del2 != '-') return false;

	time_t timer = time(NULL);
	struct tm* t = localtime(&timer);
	if(year < 2009 || year > t->tm_year + 1900 || month < 1 || month > 12 || day < 1 || day > 31) return false;
	if(month == 2) {
		if(year % 4 == 0 && year % 100 == 0 && (day < 1 || day > 29)) return false;
		else if(day < 1 || day > 28) return false;
	}
	if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
	date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
	if(date.size() != 10) return false;
	return true;
}

bool BitcoinExchange::checkValue(double value) {
	if(value < 0) {
		std::cout << "Error: not a positive number.\n";
		return false;
	}
	if(value > INT_MAX) {
		std::cout << "Error: too large a number.\n";
		return false;
	}
	return true;
}

double BitcoinExchange::calculatePrice(std::string date, double amount) {
	std::map<std::string, double>::iterator it = coin_data.upper_bound(date);
	double price = 0.0;
	if(it != coin_data.end()) {
		price = (--it)->second * amount;
	}
	return price;
}

void BitcoinExchange::getExchange(std::string input_file) {
	std::ifstream file(input_file);
	if (!file.is_open()) {
		throw WrongInputFile();
	}
	std::string line;
	std::getline(file, line);
	std::stringstream ss(line);
	std::string date, value;
	if(!std::getline(ss, date, '|') || !std::getline(ss, value)) {
		throw WrongInputFile();
	}
	date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
	value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
	if(date != "date" || value != "value") {
		throw WrongInputFile();
	}
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		double amount;
		if(!std::getline(ss, date, '|')) {
			std::cout << "Error: bad input\n";
			continue;
		}
		if (!checkDate(date)) {
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		if(!(ss >> amount)) {
			std::cout << "Error: bad input\n";
			continue;
		}
		if (!checkValue(amount)) {
			continue;
		}
		date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
		double price = calculatePrice(date, amount);
		std::cout << date << " => " << amount << " = " << price << std::endl;
	}
	file.close();
}

BitcoinExchange::WrongDataFile::WrongDataFile() : logic_error("Error: wrong data file.") {}

BitcoinExchange::WrongInputFile::WrongInputFile() : logic_error("Error: wrong input file.") {}