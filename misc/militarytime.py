"""
Mikael's CSULB CECS 174 exercise on working with the 24-hour clock!
"""

## Mikael's code:


# I ended up rewriting this version from the ground up, so that's why it prob looks very different :/

# asking for user input
time1 = input("Enter the first time as hours:minutes in 24 hour clock: ""\n")
time2 = input("Enter the second time as hours:minutes in 24 hour clock: ""\n")

# variable declaration
list1 = []
list2 = []
hour1 = 0
hour2 = 0
minute1 = 0
minute2 = 0
error = False

# checking for format error; splitting user input into hours and minutes
if (":" in time1) and (":" in time2):
    list1 = time1.split(":")
    list2 = time2.split(":")
else:
    print("Invalid format !!!")
    error = True

# checking for alphabetic input error
if not error:
    for i in range(len(list1)):
        if not list1[i].isnumeric():
            print("Invalid entry - input should be numbers only.")
            error = True
    for i in range(len(list2)):
        if not list2[i].isnumeric():
            print("Invalid entry - input should be numbers only.")
            error = True

# declaring hours and minutes
if not error:
    hour1 = int(list1[0])
    hour2 = int(list2[0])
    minute1 = int(list1[1])
    minute2 = int(list2[1])

# checking for time range error
if not error:
    if (hour1 < 0) or (hour1 > 24) or (minute1 < 0) or (minute1 > 59):
        print("Invalid time range.")
        error = True
    if (hour2 < 0) or (hour2 > 24) or (minute2 < 0) or (minute2 > 59):
        print("Invalid time range.")
        error = True

# comparing both inputs
if not error:
    if hour1 < hour2:
        print("time1 comes first")
    elif hour1 == hour2:
        if minute1 < minute2:
            print("time1 comes first")
        elif minute1 == minute2:
            print("time1 and time2 are the same")
        else:
            print("time2 comes first")
    else:
        print("time2 comes first")
