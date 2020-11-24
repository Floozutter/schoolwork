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
	// Create database.
	MartianDatabase mdb{ifile};
	// Menu.
}
