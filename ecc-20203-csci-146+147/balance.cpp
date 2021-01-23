#include <string>
#include <istream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <stack>
#include <map>
#include <set>

std::map<std::string, std::string> const OPENER_TO_CLOSER{
	{"{", "}"},
	{"(", ")"},
	{"[", "]"},
	{"'", "'"},
	{"\"", "\""},
	{"/*", "*/"}
};
std::set<std::string> const CLOSERS{
	"}",
	")",
	"]",
	"'",
	"\"",
	"*/"
};

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
	// Check the file for balance.
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

bool balanceFile(std::istream & is) {
	// Alias for convenience.
	std::map<std::string, std::string> const & O2C = OPENER_TO_CLOSER;
	// Record to store history.
	struct Token {
		std::string str;
		unsigned int line_n;
	};
	// Helper functions for printing.
	auto const printMatch = [](Token opener, Token closer){
		std::cout << "Matched pair " << opener.str << " and " << closer.str;
		std::cout << " at lines " << opener.line_n << ", " << closer.line_n;
		std::cout << "." << std::endl;
	};
	auto const printMiss = [](Token t){
		std::cout << "Unmatched " << t.str << " at line "<< t.line_n;
		std::cout << "." << std::endl;
	};
	// Start algorithm.
	std::stack<Token> ostack;
	auto const quoteZone = [&o = ostack]{
		return !o.empty() && (o.top().str == "'" || o.top().str == "\"");
	};
	auto const blockZone = [&o = ostack]{
		return !o.empty() && (o.top().str == "/*");
	};
	unsigned int line_number{1};
	for (char c; is.get(c);) {
		// Get token.
		int const d{is.peek()};
		std::string s(1, c);
		if (c == '\n') {
			// Newline.
			++line_number;
			if (quoteZone()) {
				printMiss(ostack.top());
				return false;
			}
			continue;
		} else if (!quoteZone() && !blockZone() && c == '/' && d == '/') {
			// Inline comment.
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			++line_number;
			continue;
		} else if (quoteZone() && c == '\\') {
			// Escape character.
			is.ignore();
			if (d == '\n') {
				++line_number;
			}
			continue;
		} else if (c == '/' && d == '*' || c == '*' && d == '/') {
			// Block comment token.
			s.push_back(d);
			is.ignore();
		}
		Token const token{s, line_number};
		// Handle token.
		if (!ostack.empty() && O2C.at(ostack.top().str) == token.str) {
			// The token can resolve a match. Print and resolve.
			printMatch(ostack.top(), token);
			ostack.pop();
		} else if (quoteZone()) {
			// The token is within quotes. Discard the token.
			continue;
		} else if (blockZone()) {
			// The token is within a block comment. Discard the token.
			continue;
		} else if (O2C.find(token.str) != O2C.end()) {
			// The token is an opener. Push the token onto the stack.
			ostack.push(token);
		} else if (CLOSERS.find(token.str) != CLOSERS.end()) {
			// The token is an unmatched closer. Report the imbalance.
			printMiss(token);
			return false;
		}
	}
	// Guarantee no hanging openers.
	if (ostack.empty()) {
		return true;
	} else {
		printMiss(ostack.top());
		return false;
	}
}
