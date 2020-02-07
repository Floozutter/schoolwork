"""
Mikael's CSULB CECS 174 exercise with the 24-hour clock!

https://en.wikipedia.org/wiki/Nychthemeron
"""

from typing import NamedTuple


# NamedTuple to represent 24-hour clock time.
class NychthemeronTime(NamedTuple):
    """24-hour clock time, with only hours and minutes."""
    hour: int
    minute: int


# Exceptions for timestamp to NychthemeronTime parsing.
class TimestampError(Exception):
    """Base class for timestamp parsing related exceptions."""
    pass

class FormatError(TimestampError):
    """Raised when a timestamp does not have exactly one colon."""
    pass

class NonNumericError(TimestampError):
    """Raised when a timestamp field is non-numeric."""
    pass

class RangeError(TimestampError):
    """Raised when a timestamp is outside the valid range."""
    pass


# Functions for working with NychthemeronTime.
def to_minutes(nt: NychthemeronTime) -> int:
    """Converts the hours and minutes of a NychthemeronTime to minutes only."""
    return (nt.hour * 60) + nt.minute


def parse_timestamp(timestamp: str) -> NychthemeronTime:
    """Parses a HH:MM timestamp string to a NychthemeronTime."""

    # Guarantee a single colon in the timestamp.
    if timestamp.count(":") != 1:
        raise FormatError(timestamp)

    # Guarantee that the timestamp fields are numerics.
    fields = timestamp.split(":")
    if not (fields[0].isnumeric() and fields[1].isnumeric()):
        raise NonNumericError(timestamp)
    
    # Guarantee that the timestamp fields are within the valid range.
    nt = NychthemeronTime(int(fields[0]), int(fields[1]))
    if not ((0 <= nt.hour < 24) and (0 <= nt.minute < 60)):
        raise RangeError(timestamp)  

    # Finally, finally! Return the NychthemeronTime.
    return nt


def prompt_timestamp(msg: str) -> NychthemeronTime:
    """Prompts the user to enter a timestamp to get a NychthemeronTime."""
    while True:  # Enter input loop.
        timestamp = input(msg)
        try:
            nt = parse_timestamp(timestamp)
            break  # Exit the input loop if successful.
        except FormatError:
            print("\tPlease use the HH:MM format.")
        except NonNumericError:
            print("\tPlease use only numerics for the hour and minute.")
        except RangeError:
            print("\tPlease enter a timestamp within the valid range.")
    return nt
        

# Example of comparing two NychthemeronTimes.
if __name__ == "__main__":
    # Introduce topic.
    print("Please enter two 24-hour timestamps to compare.\n")
    
    # Prompt user for Time A and Time B.
    timeA = prompt_timestamp("Enter a HH:MM timestamp for Time A: ")
    timeB = prompt_timestamp("Enter a HH:MM timestamp for Time B: ")

    # Find out which time is later, and report it.
    diff = to_minutes(timeA) - to_minutes(timeB)
    print("")
    if diff > 0:
        print(f"Time A is later by {abs(diff)} minutes.")
    elif diff < 0:
        print(f"Time B is later by {abs(diff)} minutes.")
    else:
        print("Time A and Time B are the same.")
