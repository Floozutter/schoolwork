#include "constants.hpp"
#include <string>

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
		char const pivot = s.front();
		std::string const rest = s.substr(1);
		std::string const lesser = filterByCompare(rest, pivot, false);
		std::string const greater = filterByCompare(rest, pivot, true);
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
