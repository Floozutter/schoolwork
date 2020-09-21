/**
 * A function to check if the sum of any combination of elements in an array
 * is equal to a target value, for Calvin and Vic.
 *
 * Relevant xkcd:
 * https://xkcd.com/287/
 */

#include <cassert>

bool combinationSum(int const arr[], int size, int target) {
	if (size == 0) {
		// When the array is empty, target must be the empty sum.
		return target == 0;
	} else {
		// Check if either excluding or including the head element works.
		return combinationSum(arr+1, size-1, target)
			|| combinationSum(arr+1, size-1, target-arr[0]);
	}
}

int main() {
	// Given tests:
	int const ex[] = {2, 4, 8, 6};
	assert(combinationSum(ex, 3, 10));
	assert(combinationSum(ex, 3, 12));
	assert(!combinationSum(ex, 4, 11));
	assert(combinationSum(ex, 0, 0));
	// My tests:
	int const my[] = {-2, 3};
	assert(combinationSum(my, 2, 0));
	assert(combinationSum(my, 2, -2));
	assert(combinationSum(my, 2, 3));
	assert(combinationSum(my, 2, 1));
	assert(!combinationSum(my, 2, 5));
	return 0;
}
