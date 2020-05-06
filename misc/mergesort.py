"""
A recursive implementation of mergesort, for Ryan (not Rayan).
"""

from abc import ABCMeta, abstractmethod
from typing import TypeVar, Any, List


class Comparable(metaclass=ABCMeta):
    @abstractmethod
    def __lt__(self, other: Any) -> bool: ...

C = TypeVar("C", bound=Comparable)


def merge(a: List[C], b: List[C]) -> List[C]:
    """Merges two lists that are sorted in ascending order."""
    if   not a:       return b
    elif not b:       return a
    elif a[0] < b[0]: return a[0:1] + merge(a[1:], b)
    else:             return b[0:1] + merge(a, b[1:])

def mergesort(lst: List[C]) -> List[C]:
    """Returns the list sorted using mergesort."""
    s = len(lst)  # size
    if s < 2: return lst
    else:     return merge(mergesort(lst[:s//2]), mergesort(lst[s//2:]))


if __name__ == "__main__":
    from functools import partial
    from typing import Callable
    def check_sort(sort: Callable[[List[C]], List[C]], lst: List[C]) -> bool:
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
