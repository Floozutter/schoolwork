"""
A function to compute a parking fee, for Regan.

"Let's say you want to park your car in the SNA Airport parking structure,
and you have to select one of the two options of short term parking
(option = 1) or long term parking (option = 2). Here is the details of how
much you will be charged based on each option:
	Option 1: First 20 minutes will cost you $3 and each additional 20 minutes
	(or fraction of 20 minutes) will cost you $1. Daily maximum is $20. Weekly
	maximum is $60.
	Option 2: First hour will cost you $5 and each additional hour (or fraction of
	an hour) will cost you $1. Daily maximum is $20. Weekly maximum is $60."
"""

from math import ceil


def parkingrate_helper(
	minutes: int,
	minutes_per_charge: int,
	charge_initial: int,
	charge_next: int,
	max_daily: int,
	max_weekly: int
) -> int:
	total, day, week = 0, 0, 0  # Current charges.
	for timestep in range(ceil(minutes/minutes_per_charge)):
		if timestep % 72 == 0: day = 0  # Daily reset.
		if timestep % 504 == 0: week = 0  # Weekly reset.
		if (day < max_daily and week < max_weekly):  # Below maximums?
			charge = charge_initial if timestep == 0 else charge_next
			total += charge
			day += charge
			week += charge
	return total

def parkingrate(option: int, minutes: int) -> int:
	if option == 1:
		return parkingrate_helper(
			minutes,
			20,
			3,
			1,
			20,
			60
		)
	elif option == 2:
		return parkingrate_helper(
			minutes,
			60,
			5,
			1,
			20,
			60
		)
	else:
		raise ValueError("Invalid option!")
