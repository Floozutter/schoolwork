"""
A program to count the possible pairs of disjoint subsets, for Christian.

"Let n be a positive integer and define [n] to be the set of the first n
positive integers. That is, [n] = {1, 2, 3, ... , n}. We want to select two
disjoint, possibly empty subsets A, B of [n]. In how many ways can we do
this?"
"""

from itertools import chain, combinations, product
from typing import FrozenSet, Tuple, Iterator

FS = FrozenSet


def brackets(n: int) -> FS[int]:
	return frozenset(range(1, n+1))

def powerset(s: FS[int]) -> FS[FS[int]]:
	return frozenset(map(frozenset, chain.from_iterable(
		combinations(s, r) for r in range(len(s)+1)
	)))

def disjoint_pairs(ss: FS[FS[int]]) -> Tuple[Tuple[FS[int], FS[int]], ...]:
	pairs = product(ss, ss)
	return tuple(filter(
		lambda p: p[0].isdisjoint(p[1]),
		pairs
	))


if __name__ == "__main__":
	for i in range(10): 
		print(f"[{i}] : {len(disjoint_pairs(powerset(brackets(i))))}")
