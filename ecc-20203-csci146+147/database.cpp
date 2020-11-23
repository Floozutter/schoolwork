#include <iostream>
#include <fstream>
#include <istream>
#include <string>

int const MAX_MARTIANS = 100;

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
	MartianDatabase(std::istream & is);  // Initialize with input stream.
	~MartianDatabase();
	bool addMartian(Martian const & m);  // Returns true if sufficient space.
	bool deleteMartian(std::string ssn);  // Returns true if found.
	bool isEmpty();
	bool isFull();    
	void printMartians(Criterion crit);  // Prints items sorted by criterion.
private:
    Martian* m_unsorted[MAX_MARTIANS];
    Martian* m_fname[MAX_MARTIANS];
    Martian* m_lname[MAX_MARTIANS];
    Martian* m_ssn[MAX_MARTIANS];
	size_t m_size = 0;
};
