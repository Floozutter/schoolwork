"""
A recursive solution to a 0-1 knapsack problem about gifts, for Ryan.
"""

from typing import Tuple


Gift = Tuple[int, int]  # weight, value


def max_value(gifts: Tuple[Gift, ...], weightlimit: int) -> int:
    """Returns the value of a 0-1 knapsack solution for the gifts."""
    if not gifts:
        return 0
    head, tail = gifts[0], gifts[1:]
    if head[0] > weightlimit:
        return max_value(tail, weightlimit)  # head must be excluded
    return max(
        max_value(tail, weightlimit-head[0]) + head[1],  # include head
        max_value(tail, weightlimit)                     # exclude head
    )


if __name__ == "__main__":
    # Example test.
    gifts = ((10, 70), (15, 80), (20, 140), (20, 150), (30, 200))
    weightlimit = 50
    answer = 360
    assert max_value(gifts, weightlimit) == answer

    print("Passed all tests! (There's only one, though.)")
