#include "constants.hpp"
#include <string>

void count_ascii(std::string s, int (& counter)[128]) {
	if (!s.empty()) {
		if (0 <= s.front() && s.front() < 128) {
			++counter[s.front()];
		}
		count_ascii(s.substr(1), counter);
	}
}

void zero(int arr[], int size) {
	if (size > 0) {
		*arr = 0;
		zero(arr + 1, size - 1);
	}
}

bool arr_equal(int const a[], int const b[], int size) {
	if (size <= 0) {
		return true;
	} else if (*a == *b) {
		return arr_equal(a + 1, b + 1, size - 1);
	} else {
		return false;
	}
}

int permuteRecurHelper(
	int const (& model_counter)[128],
	int (& other_counter)[128],
	std::string const dict[],
	int dict_size,
	std::string results[],
	int results_size = 0
) {
	if (results_size >= RESULTS_LIMIT || dict_size <= 0) {
		return results_size;
	} else {
		zero(other_counter, 128);
		count_ascii(*dict, other_counter);
		bool const is_anagram = arr_equal(model_counter, other_counter, 128);
		if (is_anagram) {
			*results = *dict;
		}
		return permuteRecurHelper(
			model_counter,
			other_counter,
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
	int model_counter[128] = {0};
	count_ascii(word, model_counter);
	int other_counter[128];
	return permuteRecurHelper(
		model_counter,
		other_counter,
		dict,
		dict_size,
		results
	);
}
