"""
A heart-shaped plot, for Shauen.

"Draw a heart using the equation y = x^(2/3) +- sqrt(1 - x^2). Set the color
to red and increase the number of points to make the curve smooth. Hide the
axes and adjust the ratio to make the heart look better."
"""

import matplotlib.pyplot as plt
from typing import Tuple, List


def heart(x: float) -> Tuple[float, float]:
	"""Computes the double-valued heart function."""
	a = (x**2)**(1/3)  # Single-valued term.
	b = (1 - x**2)**(1/2)  # Double-valued term.
	return (a + b, a - b)

def linspace(start: float, stop: float, n: int) -> List[float]:
	"""Returns a List of linearly spaced numbers."""
	if n <= 0:
		return []
	elif n == 1:
		return [start]
	else:
		step = (stop - start)/(n - 1)
		return [start + step*i for i in range(n)]


if __name__ == "__main__":
	# Set up figure.
	fig = plt.figure()
	ax = fig.add_subplot(1, 1, 1)
	ax.axis("off")
	ax.set_xlim(-1.5, 1.5)
	ax.set_ylim(-1.25, 1.75)
	# Plot.
	xs = linspace(-1, 1, 1000)
	ys1, ys2 = zip(*map(heart, xs))
	ax.plot(xs, ys1, color="red")
	ax.plot(xs, ys2, color="red")
	# Show figure.
	fig.show()
