#include <istream>
#include <fstream>
#include <iostream>

void printFile(std::istream & is);
bool balanceFile(std::istream & is);

int main(int argc, char * argv[]) {
	// Guarantee filename argument.
	if (argc < 2) {
		std::cout << "Missing filename argument!" << std::endl;
		return 1;
	}
	// Open file.
	std::ifstream ifile(argv[1]);
	if (!ifile) {
		std::cout << "File not found!" << std::endl;
		return 1;
	}
	// Print the file with line numbers.
	printFile(ifile);
	// Check the file for balance. Print when imbalances are encounters.
	if (balanceFile(ifile)) {
		std::cout << "Balanced!" << std::endl;
	} else {
		std::cout << "NOT balanced!" << std::endl;
	}
}

void printFile(std::istream & is) {}
bool balanceFile(std::istream & is) { return true; }
