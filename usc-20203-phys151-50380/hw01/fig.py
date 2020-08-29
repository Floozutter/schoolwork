import matplotlib.pyplot as plt
from typing import List


X0 = 4.00
V0 = 2.00
V1 = 1.00


def x(t: float) -> float:
	return (V1/4)*t**4 + V0*t + X0

def v(t: float) -> float:
	return V1*t**3 + V0

def a(t: float) -> float:
	return 3*V1*t**2

def linspace(start: float, stop: float, n: int) -> List[float]:
	"""Returns a List of linearly spaced numbers."""
	if n <= 0:
		return []
	elif n == 1:
		return [start]
	else:
		step = (stop - start)/(n - 1)
		return [start + step*i for i in range(n)]	

def make_fig():
	fig = plt.figure(figsize=(6, 12))
	ts = linspace(0, 1, 100)
	# Position subplot.
	x_ax = fig.add_subplot(3, 1, 1)
	x_ax.set_title("Position")
	x_ax.set_ylabel("x(t) (meters)")
	x_ax.set_ylim(0, 7)
	x_ax.plot(ts, list(map(x, ts)), "r")
	# Velocity subplot.
	v_ax = fig.add_subplot(3, 1, 2)
	v_ax.set_title("Velocity")
	v_ax.set_ylabel("v(t) (meters/second)")
	v_ax.set_ylim(0, 7)
	v_ax.plot(ts, list(map(v, ts)), "g")
	# Acceleration subplot.
	a_ax = fig.add_subplot(3, 1, 3)
	a_ax.set_title("Acceleration")
	a_ax.set_ylim(0, 7)
	a_ax.set_ylabel("a(t) (meters/second^2)")
	a_ax.plot(ts, list(map(a, ts)), "b")
	a_ax.set_xlabel("t (seconds)")
	# Adjustments.
	fig.subplots_adjust(hspace=0.25)
	return fig
	

if __name__ == "__main__":
	make_fig().savefig("fig.pdf", bbox_inches="tight")
