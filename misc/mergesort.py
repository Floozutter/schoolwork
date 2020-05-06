"""
A recursive implementation of mergesort, for Ryan.
"""

from typing import TypeVar, List

T = TypeVar("T")


def merge(a: List[T], b: List[T]) -> List[T]:
    """Merges two lists that are sorted in ascending order."""
    if not a:       return b
    if not b:       return a
    if a[0] < b[0]: return a[0:1] + merge(a[1:], b)
    else:           return b[0:1] + merge(a, b[1:])

def mergesort(lst: List[T]) -> List[T]:
    """Returns the list sorted using mergesort."""
    s = len(lst)  # size
    if s < 2: return lst
    else:     return merge(mergesort(lst[:s//2]), mergesort(lst[s//2:]))


if __name__ == "__main__":
    from functools import partial
    from typing import Callable
    def check_sort(sort: Callable[[List[T]], List[T]], lst: List[T]) -> bool:
        """Compares the sorting function against Python's sorted."""
        return sorted(lst) == sort(lst)
    check_mergesort = partial(check_sort, mergesort)

    from random import randrange
    def randlist(size: int) -> List[int]:
        """Generate a list of random integers within [0, 100)."""
        return [randrange(100) for _ in range(size)]

    for size in (0, 1, 2, 17, 100):
        assert check_mergesort(randlist(size))

    print("Passed all tests!")
