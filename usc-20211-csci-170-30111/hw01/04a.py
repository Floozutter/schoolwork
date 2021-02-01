from itertools import combinations, chain
from typing import AbstractSet, FrozenSet, Iterator
def powerset(s: AbstractSet[int]) -> Iterator[FrozenSet[int]]:
    return chain.from_iterable(map(frozenset, combinations(s, n)) for n in range(len(s) + 1))

def main() -> None:
    a = {1, 2, 3, 4, 5}
    b = {1, 2, 3}
    c = {ss for ss in powerset(a) if len(ss & b) == 1}
    for ss in c:
        print(set(ss))

if __name__ == "__main__":
    main()
