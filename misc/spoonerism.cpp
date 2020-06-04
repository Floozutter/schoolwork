/**
 * @file spoonerism.cpp
 * A rigidly prespecified "spoonerism" checker, for Calvin and his friend.
 * By "spoonerism", I'm fairly certain that the prompt means "anagram".
 * Also, I really wish that the prompt were not so specific.
 *
 * Prompt:
 * Write a C++ program which prompts the user to enter two C-strings, word1
 * and word2, one at a time and determines if word1 and word2 are spoonerisms.
 * The inputs word1 and word2 may be either words or phrases. Note that all
 * the letters of word1 are lowercase letters.
 * Your solution must be based on the following approach:
 *   - For each letter in word1, search word2 for it.
 *   - If the letter is found in word2, replace it with a '*' and continue.
 *   - Otherwise, return false.
 * User defined functions must be used to solve the problem.
 * You are not allowed to modify the original C-strings word1 and word2.
 * In this question, you are not allowed to use any of the functions built
 * into the C-string library except for strlen.
 */

#include <cstdio>
#include <cstring>

const size_t MAXSIZE = 32;

bool find_and_star(char s[], size_t size, char c);
bool spoonerism(char (&a)[MAXSIZE], char (&b)[MAXSIZE]);

int main() {
	// Buffers for user input.
	char word1[MAXSIZE], word2[MAXSIZE];
	
	// Prompt user input.
	std::printf("Please enter two strings.\n");
	
	// Get user input.
	if (fgets(word1, MAXSIZE, stdin) == nullptr) { return 1; }
	if (fgets(word2, MAXSIZE, stdin) == nullptr) { return 1; }
	
	// Print result of spoonerism check.
	if (spoonerism(word1, word2)) {
		std::printf("\nYay! Spoonerism.\n");
	} else {
		std::printf("\nNay, no spoonerism.\n");
	}
	std::printf("\nThe two strings were:\n");
	std::printf("%s", word1);
	std::printf("%s", word2);
	std::printf("\nHopefully, the two strings are unmodified.\n");
	
	// Say bye.
	std::printf("Bye-bye!\n");
	return 0;
}


/**
 * Replaces the first matching char in a string with an asterisk.
 * @param[in, out] s The string argument.
 * @param[in] size The size of the string argument.
 * @param[in] c The character to match against.
 * @return True if a matching char was found, false otherwise.
 */
bool find_and_star(char s[], size_t size, char c) {
	for (std::size_t i = 0; i < size; i++) {
		if (s[i] == c) {
			s[i] = '*';
			return true;
		}
	}
	return false;
}

/**
 * Checks if two C-strings are "spoonerisms".
 * @param[in] a
 * @param[in] b
 * @return Is spoon?
 */
bool spoonerism(char (&a)[MAXSIZE], char (&b)[MAXSIZE]) {
	// Check if a[] and b[] have the same size.
	std::size_t size = strlen(a);
	if (size != strlen(b)) { return false; }
	// Make a mutable copy of b[].
	char mutb[MAXSIZE];
	for (std::size_t i = 0; i < size; i++) {
		mutb[i] = b[i];
	}
	// Check if there is a char in b[] for every char in a[].
	for (std::size_t i = 0; i < size; i++) {
		if (!find_and_star(mutb, size, a[i])) {
			return false;
		}
	}
	return true;
}