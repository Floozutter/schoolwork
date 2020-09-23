/**
 * An anagram finder, for Vic and Calvin.
 */

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

constexpr int DICT_LIMIT = 30000;
constexpr int RESULTS_LIMIT = 20;

int loadDictionary(std::istream & dictfile, std::string dict[DICT_LIMIT]);
int permuteRecur(
	std::string word,
	std::string const dict[DICT_LIMIT],
	int dict_size,
	std::string results[RESULTS_LIMIT]
);
void printRecur(std::string const results[RESULTS_LIMIT], int results_size);


int main() {
	// Read valid words from file containing words separated by newlines.
	std::ifstream dictfile("words.txt");
	if (!dictfile) {
		std::cout << "File not found!" << std::endl;
		return 1;
	}
	std::string dict[DICT_LIMIT];  // Valid words.
	int const dict_size = loadDictionary(dictfile, dict);
	// Read word to match anagrams against from user input.
	std::string word;
	std::cout << "Please enter a word to find anagrams of: ";
	std::cin >> word;
	// Match anagrams.
	std::string results[RESULTS_LIMIT];  // Matched anagrams.
	int const results_size = permuteRecur(word, dict, dictsize, anagrams);
	if (results_size <= 0) {
		cout << "No matches found." << endl;
	} else {
		printRecur(results, results_size);
	}
}
