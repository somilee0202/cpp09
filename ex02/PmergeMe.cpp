#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

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

bool compareFirst(const std::pair<int, unsigned long> &a, const std::pair<int, unsigned long> &b) {
	return a.first < b.first;
}

std::vector<std::pair<int, unsigned long> > PmergeMe::mergeVector(std::vector<std::pair<int, unsigned long> > v1, std::vector<std::pair<int, unsigned long> > v2, unsigned long depth) {
	std::vector<std::pair<int, unsigned long> > v3 = v1;
	std::pair<int, unsigned long> top = v1[0];
	std::pair<int, unsigned long> bottom = v2[top.second/pow(2, depth)];
	v3.insert(v3.begin(), bottom);
	for(unsigned long i = 1; J[i - 1] <= v1.size(); i++) {
		for(unsigned long j = std::min(J[i] - 1 , v1.size() - 1); j > J[i - 1]; j--) {
			top = v1[j];
			bottom = v2[top.second/pow(2, depth)];
			std::vector<std::pair<int, unsigned long> >::iterator it = std::upper_bound(v3.begin(), v3.begin() + pow(2, i + 1) - 1, bottom, compareFirst);
			v3.insert(it, bottom);
		}
	}
	if(v1.size() != v2.size()) {
		bottom = v2[v2.size() - 1];
		std::vector<std::pair<int, unsigned long> >::iterator it = std::upper_bound(v3.begin(), v3.end(), bottom);
		v3.insert(it, bottom);
	}
	return v3;
}

std::vector<std::pair<int, unsigned long> > PmergeMe::testMerge(std::vector<std::pair<int, unsigned long> > v1, std::vector<std::pair<int, unsigned long> > v2) {
	for(unsigned long i = 0; i < v2.size(); i++) {
		v1.push_back(v2[i]);
	}
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
		v2.push_back(v[i * 2]);
	v1 = PmergeVector(v1, depth + 1);
	// std::vector<std::pair<int, unsigned long> > v3 = testMerge(v1, v2);
	std::vector<std::pair<int, unsigned long> > v3 = mergeVector(v1, v2, depth);
	return v3;
}

// std::list<std::pair<int, unsigned long> > PmergeMe::PmergeList(std::list<std::pair<int, unsigned long> > l, unsigned long depth) {}

void PmergeMe::DoPmerge() {
	for(unsigned long i = 0; i < V.size(); i++) {
		std::cout << V[i].first << '(' << V[i].second << ')' << ' ';
	}
	std::cout << std::endl;
	makeJArr(J_MAX);
	V = PmergeVector(V, 1);
	for(unsigned long i = 0; i < V.size(); i++) {
		std::cout << V[i].first << '(' << V[i].second << ')' << ' ';
	}
	std::cout << std::endl;
}

PmergeMe::InputError::InputError() : logic_error("Error") {}