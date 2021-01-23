/**
 * A function to delete 'G's from a C string, for Vic.
 *
 * Write a function named deleteG that accepts one character pointer as a
 * parameter and returns no value. The parameter is a C string. This function
 * must remove all of the upper and lower case 'G' letters from the string.
 * The resulting string must be a valid C string. Your function must declare
 * no more than one local variable in addition to the parameter; that
 * additional variable must be of a pointer type. Your function must not use
 * any square brackets and must not use the strlen or strcpy library functions.
 */

#include <cstdio>

void deleteG(char* str) {
	// Use str as the iterator to copy to,
	// and ptr as the iterator to copy from.
	// For each char in the C string (as pointed to by ptr)...
	for (char* ptr = str; *ptr != '\0'; ++ptr) {
		// If the char is neither a 'G' nor a 'g'...
		if (*ptr != 'G' && *ptr != 'g') {
			// Then set the value at str to that char, and increment str.
			*str = *ptr;
			++str;
		}
	}
	// Null-terminate the string.
	*str = '\0';
}

int main() {
	char msg[100] = (
		"I recall the glass gate next to Gus in Lagos, near the gold bridge."
	);
	std::puts(msg);
	deleteG(msg);
	std::puts(msg);
}
