#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#define J_MAX 30

class PmergeMe {
private:
	unsigned long J[J_MAX];
	std::vector<std::pair<int, unsigned long> > V;
	std::list<std::pair<int, unsigned long> > L;

	PmergeMe(const PmergeMe &a);
	PmergeMe &operator=(const PmergeMe &a);
	PmergeMe();
	void makeJArr(int d);
	// bool compareFirst(const std::pair<int, unsigned long> &a, const std::pair<int, unsigned long> &b);
	std::vector<std::pair<int, unsigned long> > mergeVector(std::vector<std::pair<int, unsigned long> > v1, std::vector<std::pair<int, unsigned long> > v2, unsigned long depth);
	std::vector<std::pair<int, unsigned long> > PmergeVector(std::vector<std::pair<int, unsigned long> > v, unsigned long depth);
	// std::list<std::pair<int, unsigned long> > PmergeList(std::list<std::pair<int, unsigned long> > l, unsigned long depth);
public:
	PmergeMe(char *c[], int s);
	~PmergeMe();

	void DoPmerge();

	class InputError :public std::logic_error {
	public:
		InputError();
	};
	std::vector<std::pair<int, unsigned long> > testMerge(std::vector<std::pair<int, unsigned long> > v1, std::vector<std::pair<int, unsigned long> > v2);
};

#endif