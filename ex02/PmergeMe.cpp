#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cmath>

PmergeMe::PmergeMe(char* c[], int s) {
    for(int i = 1; i < s; i++) {
        std::stringstream ss(c[i]);
        int num = 0;
        ss >> num;
        if(ss.fail()) throw InputError();
        V.push_back(std::make_pair(num, i - 1));
        L.push_back(std::make_pair(num, i - 1));
		D.push_back(std::make_pair(num, i - 1));
    }
}

PmergeMe::~PmergeMe() {}

void PmergeMe::makeJArr(int d) {
    J[0] = 1; J[1] = 3;
    for(int i = 2; i < d; i++) {
        J[i] = J[i - 1] + 2 * J[i - 2];
    }
}

bool compareFirst(const std::pair<int, unsigned long> &a, const std::pair<int, unsigned long> &b) {
    return a.first < b.first;
}

std::vector<std::pair<int, unsigned long> > PmergeMe::mergeVector(std::vector<std::pair<int, unsigned long> > v1, std::vector<std::pair<int, unsigned long> > v2, unsigned long depth) {
    std::vector<std::pair<int, unsigned long> > v3 = v1;
    std::pair<int, unsigned long> top = v1[0];
    std::pair<int, unsigned long> bottom = v2[top.second / static_cast<unsigned long>(pow(2, depth))];
    v3.insert(v3.begin(), bottom);

    for(unsigned long i = 1; J[i - 1] <= v1.size(); i++) {
        for(unsigned long j = std::min(J[i] - 1 , v1.size() - 1); j >= J[i - 1]; j--) {
            top = v1[j];
            bottom = v2[top.second / static_cast<unsigned long>(pow(2, depth))];
            unsigned long max_range = std::min(static_cast<unsigned long>(pow(2, i + 1) - 1), v3.size());
            std::vector<std::pair<int, unsigned long> >::iterator it = std::lower_bound(v3.begin(), v3.begin() + max_range, bottom, compareFirst);
            v3.insert(it, bottom);
        }
    }

    if(v1.size() != v2.size()) {
        bottom = v2[v2.size() - 1];
        std::vector<std::pair<int, unsigned long> >::iterator it = std::lower_bound(v3.begin(), v3.end(), bottom, compareFirst);
        v3.insert(it, bottom);
    }

    return v3;
}

std::vector<std::pair<int, unsigned long> > PmergeMe::PmergeVector(std::vector<std::pair<int, unsigned long> > v, unsigned long depth) {
    if(v.size() == 1) return v;

    std::vector<std::pair<int, unsigned long> > v1, v2;
    std::vector<std::pair<int, unsigned long> >::iterator it = v.begin();

    for(unsigned long i = 0; i < v.size() / 2; i++) {
        std::pair<int, unsigned long> a = *it++;
        std::pair<int, unsigned long> b = *it++;

        if(b.first > a.first) std::swap(a, b);
        v1.push_back(a); v2.push_back(b);
    }
    if(it != v.end()) v2.push_back(*it);

    v1 = PmergeVector(v1, depth + 1);
    return mergeVector(v1, v2, depth);
}
/////////////////////////////////////////////////////////
std::deque<std::pair<int, unsigned long> > PmergeMe::mergeDeque(std::deque<std::pair<int, unsigned long> > d1, std::deque<std::pair<int, unsigned long> > d2, unsigned long depth) {
    std::deque<std::pair<int, unsigned long> > d3 = d1;
    std::pair<int, unsigned long> top = d1[0];
    std::pair<int, unsigned long> bottom = d2[top.second / static_cast<unsigned long>(pow(2, depth))];
    d3.insert(d3.begin(), bottom);

    for(unsigned long i = 1; J[i - 1] <= d1.size(); i++) {
        for(unsigned long j = std::min(J[i] - 1 , d1.size() - 1); j >= J[i - 1]; j--) {
            top = d1[j];
            bottom = d2[top.second / static_cast<unsigned long>(pow(2, depth))];
            unsigned long max_range = std::min(static_cast<unsigned long>(pow(2, i + 1) - 1), d3.size());
            std::deque<std::pair<int, unsigned long> >::iterator it = std::lower_bound(d3.begin(), d3.begin() + max_range, bottom, compareFirst);
            d3.insert(it, bottom);
        }
    }

    if(d1.size() != d2.size()) {
        bottom = d2[d2.size() - 1];
        std::deque<std::pair<int, unsigned long> >::iterator it = std::lower_bound(d3.begin(), d3.end(), bottom, compareFirst);
        d3.insert(it, bottom);
    }

    return d3;
}

std::deque<std::pair<int, unsigned long> > PmergeMe::PmergeDeque(std::deque<std::pair<int, unsigned long> > d, unsigned long depth) {
    if(d.size() == 1) return d;

    std::deque<std::pair<int, unsigned long> > d1, d2;
    std::deque<std::pair<int, unsigned long> >::iterator it = d.begin();

    for(unsigned long i = 0; i < d.size() / 2; i++) {
        std::pair<int, unsigned long> a = *it++;
        std::pair<int, unsigned long> b = *it++;

        if(b.first > a.first) std::swap(a, b);
        d1.push_back(a); d2.push_back(b);
    }
    if(it != d.end()) d2.push_back(*it);

    d1 = PmergeDeque(d1, depth + 1);
    return mergeDeque(d1, d2, depth);
}
/////////////////////////////////////////////////////////

std::list<std::pair<int, unsigned long> > PmergeMe::mergeList(std::list<std::pair<int, unsigned long> > l1, std::list<std::pair<int, unsigned long> > l2, unsigned long depth) {
	std::list<std::pair<int, unsigned long> > l3 = l1;
    std::pair<int, unsigned long> top = *l1.begin();

	std::list<std::pair<int, unsigned long> >::iterator it = l2.begin();
	std::advance(it, top.second / static_cast<unsigned long>(pow(2, depth)));
    std::pair<int, unsigned long> bottom = *it;
    l3.push_front(bottom);

    for (unsigned long i = 1; J[i - 1] <= l1.size(); i++) {
        for (unsigned long j = std::min(J[i] - 1, l1.size() - 1); j >= J[i - 1]; j--) {
			it = l1.begin();
			std::advance(it, j);
            top = *it;

			it = l2.begin();
			std::advance(it, top.second / static_cast<unsigned long>(pow(2, depth)));
			bottom = *it;

            it = l1.begin();
			while(it->first < bottom.first) {
				it++;
			}
            l3.insert(it, bottom);
        }
    }

    if (l1.size() != l2.size()) {
        bottom = l2.back();
		std::list<std::pair<int, unsigned long> >::iterator it = l1.begin();
		while(it->first < bottom.first) {
			it++;
		}
		l3.insert(it, bottom);
    }

    return l3;
}


std::list<std::pair<int, unsigned long> > PmergeMe::PmergeList(std::list<std::pair<int, unsigned long> > l, unsigned long depth) {
    if (l.size() == 1) return l;

    std::list<std::pair<int, unsigned long> > l1, l2;
    std::list<std::pair<int, unsigned long> >::iterator it = l.begin();

    for (unsigned long i = 0; i < l.size() / 2; ++i) {
        std::pair<int, unsigned long> a = *it++;
        std::pair<int, unsigned long> b = *it++;

        if (b.first > a.first) std::swap(a, b);
        l1.push_back(a); l2.push_back(b);
    }
    if (it != l.end()) l2.push_back(*it);

    l1 = PmergeList(l1, depth + 1);
    return mergeList(l1, l2, depth);
}

void PmergeMe::DoPmerge() {
    std::cout << "Before: ";
    unsigned long i = 0;
    for(; i < std::min(V.size(), static_cast<unsigned long>(4)); i++)
        std::cout << V[i].first << ' ';
    if(i == V.size() - 1)
        std::cout << V[i].first << std::endl;
    else std::cout << "[...]" << std::endl;

    makeJArr(J_MAX);
    clock_t v_start = clock();
    V = PmergeVector(V, 1);
    clock_t v_end = clock();

    clock_t l_start = clock();
    L = PmergeList(L, 1);
    clock_t l_end = clock();
	//////////////////////////
	clock_t d_start = clock();
    D = PmergeDeque(D, 1);
    clock_t d_end = clock();
	//////////////////////////

    std::cout << "After: ";
    for(i = 0; i < std::min(V.size(), static_cast<unsigned long>(4)); i++)
        std::cout << V[i].first << ' ';
    if(i == V.size() - 1)
        std::cout << V[i].first << std::endl;
    else std::cout << "[...]" << std::endl;

    std::cout << "Time to process a range of 5 elements with std::vector : " << static_cast<double>(v_end - v_start) * 1e6 / CLOCKS_PER_SEC << " us\n";
    std::cout << "Time to process a range of 5 elements with std::list : " << static_cast<double>(l_end - l_start) * 1e6 / CLOCKS_PER_SEC << " us\n";
    std::cout << "Time to process a range of 5 elements with std::deque : " << static_cast<double>(d_end - d_start) * 1e6 / CLOCKS_PER_SEC << " us\n";
}

PmergeMe::InputError::InputError() : logic_error("Error") {}
