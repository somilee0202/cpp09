#include "RPN.hpp"
#include <sstream>

RPN::RPN() {}
RPN::~RPN() {}
int RPN::calculateRPN(std::string str) {
	std::stringstream ss(str);
	std::string t;
	while(std::getline(ss, t, ' ')) {
		if(!t.size()) continue;
		if((t == "+" || t == "-" || t == "*" || t == "/") && s.size() >= 2) {
			int a = s.top(); s.pop();
			int b = s.top(); s.pop();
			if(t == "+") s.push(b + a);
			else if(t == "-") s.push(b - a);
			else if(t == "*") s.push(b * a);
			else if(t == "/") {
				if(a == 0) throw InputError();
				s.push(b / a);
			}
		}
		else {
			std::stringstream tss(t);
			int num;
			if(tss >> num && 0 <= num && num <= 9) {
				s.push(num);
			}
			else throw InputError();
		}
	}
	if(s.size() != 1) throw InputError();
	return s.top();
}

RPN::InputError::InputError() : std::logic_error("Error") {}