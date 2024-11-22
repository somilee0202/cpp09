#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>

PmergeMe::PmergeMe(char* c[], int s) {
	for(int i = 1; i < s; i++) {
		std::stringstream ss(c[i]);
		int num = 0;
		ss >> num;
		if(ss.fail()) throw InputError();
		V.push_back(std::make_pair(num, i - 1));
		L.push_back(std::make_pair(num, i - 1));
	}
}

PmergeMe::~PmergeMe() {}

void PmergeMe::makeJArr(int d) {
	J[0] = 1;
	J[1] = 3;
	for(int i = 2; i < d; i++)
		J[i] = J[i - 1] + 2 * J[i - 2];
}

std::vector<std::pair<int, unsigned long> > PmergeMe::mergeVector(std::vector<std::pair<int, unsigned long> > v1, std::vector<std::pair<int, unsigned long> > v2) {
	std::vector<std::pair<int, unsigned long> > v3 = v1;
	for(unsigned int i = 0; J[i] < )
	return v1;
}

std::vector<std::pair<int, unsigned long> > PmergeMe::PmergeVector(std::vector<std::pair<int, unsigned long> > v, unsigned long depth) {
	if(v.size() == 1) return v;

	std::vector<std::pair<int, unsigned long> > v1, v2;
	unsigned long i = 0;
	for(; i < v.size()/2; i ++) {
		std::pair<int, unsigned long> a = v[i * 2];
		std::pair<int, unsigned long> b = v[i * 2 +1];

		if(b.first > a.first) std::swap(a, b);
		v1.push_back(a); v2.push_back(b);
	}
	if(i * 2 < v.size()) 
		v1.push_back(v[i * 2]);
	v1 = PmergeVector(v1, depth + 1);
	return mergeVector(v1, v2);
}

// std::list<std::pair<int, unsigned long> > PmergeMe::PmergeList(std::list<std::pair<int, unsigned long> > l, unsigned long depth) {}

void PmergeMe::DoPmerge() {
	for(unsigned long i = 0; i < V.size(); i++) {
		std::cout << V[i].first << '(' << V[i].second << ')' << ' ';
	}
	std::cout << std::endl;
	makeJArr(J_MAX);
	for(int i = 0; i < J_MAX; i++) {
		std::cout << J[i] << ' ';
	}
	std::cout << std::endl;
	V = PmergeVector(V, 1);
	for(unsigned long i = 0; i < V.size(); i++) {
		std::cout << V[i].first << '(' << V[i].second << ')' << ' ';
	}
	std::cout << std::endl;
}

PmergeMe::InputError::InputError() : logic_error("Error") {}