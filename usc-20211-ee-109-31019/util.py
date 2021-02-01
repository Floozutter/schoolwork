def p(*resistances: float) -> float:
    """Computes the total resistance of resistors in parallel."""
    return 1 / sum(1 / r for r in resistances)
