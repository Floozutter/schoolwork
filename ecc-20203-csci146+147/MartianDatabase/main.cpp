#include "martian.hpp"
#include <fstream>
#include <iostream>

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
	// Load database.
	MartianDatabase mdb{ifile};
	std::cout << "Database loaded!" << std::endl;
	// Menu.
	while (true) {
		std::cout << std::endl;
		std::cout << "[add/del/print/quit]: ";
		std::string option;
		std::cin >> option;
		if (option == "add") {
			if (mdb.isFull()) {
				std::cout << "Database is full!" << std::endl;
			} else {
				std::cout << "[FIRST_NAME] [LAST_NAME] [SSN]: ";
				Martian m;
				std::cin >> m.fname >> m.lname >> m.ssn;
				if (mdb.addMartian(m)) {
					std::cout << "Successfully added!" << std::endl;
				} else {
					std::cout << "Something went wrong!" << std::endl;
				}
			}
		} else if (option == "del") {
			if (mdb.isEmpty()) {
				std::cout << "Database is empty!" << std::endl;
			} else {
				std::cout << "[SSN]: ";
				std::string ssn;
				std::cin >> ssn;
				if (mdb.deleteMartian(ssn)) {
					std::cout << "Successfully deleted!" << std::endl;
				} else {
					std::cout << "Martian not found!" << std::endl;
				}
			}
		} else if (option == "print") {
			std::cout << "Order by [first/last/ssn]: ";
			std::string order;
			std::cin >> order;
			Criterion crit;
			if (order == "first") {
				crit = Criterion::first;
			} else if (order == "last") {
				crit = Criterion::last;
			} else {
				crit = Criterion::ssn;
			}
			mdb.printMartians(crit);
		} else if (option == "quit") {
			break;
		}
	}
	// Say bye.
	std::cout << "Bye-bye!" << std::endl;
	return 0;
}
