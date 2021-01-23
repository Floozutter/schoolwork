#include "martian.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <optional>
#include <memory>

MartianDatabase::MartianDatabase(std::istream & is) {
	auto const parseMartian = [](
		std::string const & line
	) -> std::optional<Martian> {
		std::istringstream iss{line};
		Martian m;
		iss >> m.fname >> m.lname >> m.ssn;
		if (iss) {
			return m;
		} else {
			return {};
		} 
	};
	for (std::string line; std::getline(is, line);) {
		if (auto maybe_martian = parseMartian(line)) {
			if (!this->addMartian(*maybe_martian)) {
				return;
			}
		}
	}
}

MartianDatabase::~MartianDatabase() {
	std::for_each(
		this->m_unsorted,
		this->m_unsorted + this->m_size,
		std::default_delete<Martian>()
	);
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

bool MartianDatabase::deleteMartian(std::string ssn) {
	auto const it{std::find_if(
		this->m_unsorted,
		this->m_unsorted + this->m_size,
		[&ssn](Martian const * const & m){ return m->ssn == ssn; }
	)};
	if (it == this->m_unsorted + this->m_size) {
		return false;
	} else {
		Martian * const m{*it};
		auto const overwrite_m_with_last = [m, s = this->m_size](auto arr){
			*std::find(arr, arr + s, m) = arr[s - 1];
		};
		overwrite_m_with_last(this->m_unsorted);
		overwrite_m_with_last(this->m_fname);
		overwrite_m_with_last(this->m_lname);
		overwrite_m_with_last(this->m_ssn);
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
	auto arr = [this](
		Criterion crit
	) -> Martian * const (&)[MAX_MARTIANS] {
		switch (crit) {
		case Criterion::first: return this->m_fname;
		case Criterion::last:  return this->m_lname;
		case Criterion::ssn:   return this->m_ssn;
		default:               return this->m_unsorted;
		}
	}(crit);
	std::for_each(
		arr,
		arr + this->m_size,
		[](Martian const * const & m){
			std::cout << m->fname << " " << m->lname << " ";
			std::cout << m->ssn << std::endl;
		}
	);
}

void MartianDatabase::sort() {
	auto const helper = [s = this->m_size](auto arr, auto cmp){
		std::sort(arr, arr + s, cmp);
	};
	using M = Martian const * const &;
	helper(this->m_fname, [](M a, M b){ return a->fname < b->fname; });
	helper(this->m_lname, [](M a, M b){ return a->lname < b->lname; });
	helper(this->m_ssn,   [](M a, M b){ return a->ssn < b->ssn; });
}
