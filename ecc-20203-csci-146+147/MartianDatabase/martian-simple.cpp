#include "martian.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

MartianDatabase::MartianDatabase(std::istream & is) {
	for (std::string line; std::getline(is, line);) {
		std::istringstream iss{line};
		Martian m;
		iss >> m.fname >> m.lname >> m.ssn;
		if (iss) {
			if (!this->addMartian(m)) {
				return;
			}
		}
	}
}

MartianDatabase::~MartianDatabase() {
	for (size_t i{0}; i < this->m_size; ++i) {
		delete this->m_unsorted[i];
	}
}

bool MartianDatabase::addMartian(Martian const & m) {
	if (this->m_size < MAX_MARTIANS) {
		Martian * const nm{new Martian{m}};
		this->m_unsorted[this->m_size] = nm;
		this->m_fname[this->m_size] = nm;
		this->m_lname[this->m_size] = nm;
		this->m_ssn[this->m_size] = nm;
		++this->m_size;
		this->sort();
		return true;
	} else {
		return false;
	}
}

void overwrite_m_with_last(
	Martian * martians[],
	size_t size,
	Martian const * m
) {
	for (size_t i{0}; i < size; ++i) {
		if (martians[i] == m) {
			martians[i] = martians[size - 1];
		}
	}
}
bool MartianDatabase::deleteMartian(std::string ssn) {
	Martian const * m{nullptr};
	for (size_t i{0}; i < this->m_size; ++i) {
		if (this->m_unsorted[i]->ssn == ssn) {
			m = this->m_unsorted[i];
			break;
		}
	}
	if (!m) {
		return false;
	} else {
		overwrite_m_with_last(this->m_unsorted, this->m_size, m);
		overwrite_m_with_last(this->m_fname, this->m_size, m);
		overwrite_m_with_last(this->m_lname, this->m_size, m);
		overwrite_m_with_last(this->m_ssn, this->m_size, m);
		--this->m_size;
		this->sort();
		delete m;
		return true;
	}
}

bool MartianDatabase::isEmpty() const {
	return this->m_size <= 0;
}

bool MartianDatabase::isFull() const {
	return this->m_size >= MAX_MARTIANS;
}

void MartianDatabase::printMartians(Criterion crit) const {
	Martian const * const * arr{nullptr};
	switch (crit) {
	case (Criterion::first): arr = this->m_fname; break;
	case (Criterion::last):  arr = this->m_lname; break;
	case (Criterion::ssn):   arr = this->m_ssn; break;
	default:                 arr = this->m_unsorted; break;
	}
	for (size_t i{0}; i < this->m_size; ++i) {
		std::cout << arr[i]->fname << " " << arr[i]->lname << " ";
		std::cout << arr[i]->ssn << std::endl;
	}
}

bool cmp_fname(Martian const * a, Martian const * b) {
	return a->fname < b->fname;
}
bool cmp_lname(Martian const * a, Martian const * b) {
	return a->lname < b->lname;
}
bool cmp_ssn(Martian const * a, Martian const * b) {
	return a->ssn < b->ssn;
}
void MartianDatabase::sort() {
	std::sort(this->m_fname, this->m_fname + this->m_size, cmp_fname);
	std::sort(this->m_lname, this->m_lname + this->m_size, cmp_lname);
	std::sort(this->m_ssn, this->m_ssn + this->m_size, cmp_ssn);
}
