/**
 * @file triangle.cpp
 * Prints out a right triangle using recursion.
 */

#include <iostream>
#include <sstream>

void print_stars(std::ostream& ostr, size_t n);
void print_triangle(std::ostream& ostr, size_t size);

int main(int argc, char* argv[]) {
	std::istringstream iss;
	size_t size;
	
	// Guarantee that a size argument was passed in from the command line.
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " SIZE" << std::endl;
		return 1;
	}
	
	// Guarantee that the size argument is valid.
	iss.str(argv[1]);
	if (!(iss >> size)) {
		std::cerr << "Invalid SIZE: " << argv[1] << std::endl;
		return 1;
	}
	
	// Print the triangle to standard output using the size argument.
	print_triangle(std::cout, size);
	std::cout << std::flush;
	
	return 0;
}


/**
 * Prints out a number of asterisks (*), ending with a newline.
 *
 * @param[out] ostr Output stream.
 * @param[in] n Number of asterisks.
 */
void print_stars(std::ostream& ostr, size_t n) {
	if (n == 0) {
		ostr << '\n';
	} else {
		ostr << '*';
		print_stars(ostr, n-1);
	}
}

/**
 * Prints out a right triangle of asterisks, starting with the base.
 *
 * @param[out] ostr Output stream.
 * @param[in] size Length of the base and the number of rows.
 */
void print_triangle(std::ostream& ostr, size_t size) {
	if (size > 0) {
		print_stars(ostr, size);
		print_triangle(ostr, size-1);
	}
}