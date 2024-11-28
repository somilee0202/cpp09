#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#define J_MAX 30

class PmergeMe {
private:
	unsigned long num;
	unsigned long J[J_MAX];
	std::vector<std::pair<int, unsigned long> > V;
	std::deque<std::pair<int, unsigned long> > D;

	PmergeMe(const PmergeMe &a);
	PmergeMe &operator=(const PmergeMe &a);
	PmergeMe();
	void makeJArr(int d);
	std::vector<std::pair<int, unsigned long> > mergeVector(std::vector<std::pair<int, unsigned long> > v1, std::vector<std::pair<int, unsigned long> > v2, unsigned long depth);
	std::vector<std::pair<int, unsigned long> > PmergeVector(std::vector<std::pair<int, unsigned long> > v, unsigned long depth);
public:
	PmergeMe(char *c[], int s);
	~PmergeMe();

	void DoPmerge();

	class InputError :public std::logic_error {
	public:
		InputError();
	};
	std::deque<std::pair<int, unsigned long> > mergeDeque(std::deque<std::pair<int, unsigned long> > d1, std::deque<std::pair<int, unsigned long> > d2, unsigned long depth);
	std::deque<std::pair<int, unsigned long> > PmergeDeque(std::deque<std::pair<int, unsigned long> > d, unsigned long depth);
};

#endif
