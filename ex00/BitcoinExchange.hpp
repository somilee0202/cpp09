#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <utility>

class BitcoinExchange {
private:
	std::map<std::string , double> coin_data;

	BitcoinExchange(const BitcoinExchange &a);
	BitcoinExchange &operator=(const BitcoinExchange &a);
	BitcoinExchange();
	bool checkDate(std::string date);
	bool checkValue(double value);
	double calculatePrice(std::string date, double amount);
public:
	BitcoinExchange(std::string data_file);
	~BitcoinExchange();

	void getExchange(std::string input_file);

	class WrongDataFile : public std::logic_error {
	public:
		WrongDataFile();
	};

	class WrongInputFile : public std::logic_error {
	public:
		WrongInputFile();
	};
};

#endif