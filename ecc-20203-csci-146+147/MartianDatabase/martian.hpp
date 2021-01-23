#ifndef MARTIAN_HPP
#define MARTIAN_HPP

#include <istream>
#include <string>

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

#endif
