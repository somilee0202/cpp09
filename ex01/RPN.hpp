#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <stdexcept>

class RPN {
private:
	std::stack<int> s;
	RPN(const RPN &a);
	RPN &operator=(const RPN &a);
public:
	RPN();
	~RPN();
	bool checkOperator(std::string t);
	bool checkNum(std::string t);
	int calculateOperations(std::string t);
	int calculateRPN(std::string str);

	class InputError :public std::logic_error {
	public:
		InputError();
	};
};

#endif