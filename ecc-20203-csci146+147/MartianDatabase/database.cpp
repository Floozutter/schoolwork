#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <algorithm>
#include <optional>
#include <memory>

int constexpr MAX_MARTIANS{100};

struct Martian {
	std::string fname;
	std::string lname;
	std::string ssn;
};

enum class Criterion {
	first,
	last,
	ssn
};

class MartianDatabase {
public:
	MartianDatabase(std::istream & is);
	~MartianDatabase();
	bool addMartian(Martian const & m);  // Returns false if not enough space.
	bool deleteMartian(std::string ssn);  // Returns false if not found.
	bool isEmpty() const;
	bool isFull() const;
	void printMartians(Criterion crit) const;  // Prints items sorted by crit.
private:
	void sort();
	Martian * m_unsorted[MAX_MARTIANS];
	Martian * m_fname[MAX_MARTIANS];
	Martian * m_lname[MAX_MARTIANS];
	Martian * m_ssn[MAX_MARTIANS];
	size_t m_size{0};
};

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
		[ssn](Martian const * const & m){ return m->ssn == ssn; }
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
			std::cout << m->fname << " " << m->lname << m->ssn << std::endl;
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

int main(int argc, char * argv[]) {
	// Guarantee filename argument.
	if (argc < 2) {
		std::cout << "Missing filename argument for database!" << std::endl;
		return 1;
	}
	// Open file.
	std::ifstream ifile{argv[1]};
	if (!ifile) {
		std::cout << "File not found!" << std::endl;
		return 1;
	}
	// Create database.
	MartianDatabase mdb{ifile};
	// Menu.
}
