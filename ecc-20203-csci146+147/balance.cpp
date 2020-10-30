#include <string>
#include <istream>
#include <fstream>
#include <iostream>
#include <iomanip>

void printFile(std::istream & is);
bool balanceFile(std::istream & is);

int main(int argc, char * argv[]) {
	// Guarantee filename argument.
	if (argc < 2) {
		std::cout << "Missing filename argument!" << std::endl;
		return 1;
	}
	// Open file.
	std::ifstream ifile{argv[1]};
	if (!ifile) {
		std::cout << "File not found!" << std::endl;
		return 1;
	}
	// Print the file with line numbers.
	printFile(ifile);
	// Reset input file stream.
	ifile.clear();
	ifile.seekg(0);
	// Check the file for balance. Print when imbalances are encounters.
	if (balanceFile(ifile)) {
		std::cout << "Balanced!" << std::endl;
	} else {
		std::cout << "NOT balanced!" << std::endl;
	}
}

void printFile(std::istream & is) {
	// Get the line number prefix width.
	unsigned int const prefix_width{[&is]{
		// Save start position.
		std::istream::pos_type const start_pos{is.tellg()};
		// Count the number of lines.
		unsigned int line_count{0};
		for (std::string dummy; std::getline(is, dummy);) {
			++line_count;
		}
		// Reset input stream back to start position.
		is.clear();
		is.seekg(start_pos);
		// Return the number of digits in the number of lines.
		return static_cast<unsigned int>(std::to_string(line_count).size());
	}()};
	// Print lines.
	unsigned int line_number{1};
	for (std::string line; std::getline(is, line);) {
		std::cout << std::setw(prefix_width) << line_number << " ";
		std::cout << line << std::endl;
		++line_number;
	}
}

bool balanceFile(std::istream & is) { return true; }
