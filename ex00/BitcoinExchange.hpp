#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <vector>
#include <string>
#include <utility>

class BitcoinExchange {
private:
	std::vector<std::pair<std::string, int> > coin_data;

	BitcoinExchange(const BitcoinExchange &a);
	BitcoinExchange &operator=(const BitcoinExchange &a);
	BitcoinExchange();
public:
	BitcoinExchange(std::string data_file);
	~BitcoinExchange();

	bool CheckDate(std::string date);
	float CalculatePrice(std::string input_file);
	class NotPositiveNumber : public std::logic_error {
	public:
		NotPositiveNumber();
	};
	class TooLargeNumber : public std::logic_error {
	public:
		TooLargeNumber();
	};
	class BadInput : public std::logic_error {
	public:
		BadInput(std::string date);
	};
};

#endif // BITCOINEXCHANGE_HPP