/**
 * An anagram finder, for Vic and Calvin.
 */

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

constexpr int DICT_LIMIT = 30000;
constexpr int RESULTS_LIMIT = 20;

int loadDictionary(std::istream & dictfile, std::string dict[]);
int permuteRecur(
	std::string word,
	std::string const dict[],
	int dict_size,
	std::string results[]
);
void printRecur(std::string const arr[], int size);

int main() {
	// Read valid words from file containing words separated by newlines.
	std::ifstream dictfile("words.txt");
	if (!dictfile) {
		std::cout << "File not found!" << std::endl;
		return 1;
	}
	std::string dict[DICT_LIMIT];  // Valid words.
	int const dict_size = loadDictionary(dictfile, dict);
	dictfile.close();
	// Read word to match anagrams against from user input.
	std::string word;
	std::cout << "Please enter a word to find anagrams of: ";
	std::cin >> word;
	// Match anagrams.
	std::string results[RESULTS_LIMIT];  // Matched anagrams.
	int const results_size = permuteRecur(word, dict, dict_size, results);
	if (results_size <= 0) {
		std::cout << "No matches found." << std::endl;
	} else {
		std::cout << results_size << " matches found:" << std::endl;
		printRecur(results, results_size);
	}
}


int loadDictionaryHelper(
	std::istream & dictfile,
	std::string dict[],
	int dict_size = 0
) {
	std::string line;
	if (dict_size >= DICT_LIMIT || !std::getline(dictfile, line)) {
		return dict_size;
	} else {
		*dict = line;
		return loadDictionaryHelper(dictfile, dict + 1, dict_size + 1);
	}
}
int loadDictionary(std::istream & dictfile, std::string dict[]) {
	return loadDictionaryHelper(dictfile, dict);
}

std::string filterByCompare(std::string s, char pivot, bool keepGreater) {
	if (s.empty()) {
		return s;
	} else if (keepGreater == (s.front() > pivot)) {
		return s.front() + filterByCompare(s.substr(1), pivot, keepGreater);
	} else {
		return filterByCompare(s.substr(1), pivot, keepGreater);
	}
}
std::string quickSort(std::string s) {
	if (s.empty()) {
		return s;
	} else {
		// Choose pivot element.
		char const pivot = s.front();
		std::string const rest = s.substr(1);
		// Find the lesser elements and the greater-or-equal elements.
		std::string const lesser = filterByCompare(rest, pivot, false);
		std::string const greater = filterByCompare(rest, pivot, true);
		// Conquer!
		return quickSort(lesser) + pivot + quickSort(greater);
	}
}
int permuteRecurHelper(
	std::string sorted_word,
	std::string const dict[],
	int dict_size,
	std::string results[],
	int results_size = 0
) {
	if (results_size >= RESULTS_LIMIT || dict_size <= 0) {
		return results_size;
	} else {
		bool is_anagram = sorted_word == quickSort(*dict);
		if (is_anagram) {
			*results = *dict;
		}
		return permuteRecurHelper(
			sorted_word,
			dict + 1,
			dict_size - 1,
			results + is_anagram,
			results_size + is_anagram
		);
	}
}
int permuteRecur(
	std::string word,
	std::string const dict[],
	int dict_size,
	std::string results[]
) {
	return permuteRecurHelper(quickSort(word), dict, dict_size, results);
}

void printRecur(std::string const arr[], int size) {
	if (size > 0) {
		std::cout << *arr << std::endl;
		printRecur(arr+1, size-1);
	}
}
