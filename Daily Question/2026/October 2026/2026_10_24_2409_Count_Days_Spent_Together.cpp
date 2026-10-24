class Solution {
    private:
        int findDayOfYear(string& day, const vector<int>& cumMonthDays) {
            int month = stoi(day.substr(0, 2));
            int date  = stoi(day.substr(3));
            return cumMonthDays[month - 1] + date;
        }
    
    public:
        int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
            vector<int> monthDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
            vector<int> cumMonthDays(13, 0);
            for(int i = 1; i <= 12; i++) cumMonthDays[i] = cumMonthDays[i-1] + monthDays[i-1];
    
            int arriveAliceDay = findDayOfYear(arriveAlice, cumMonthDays);
            int leaveAliceDay = findDayOfYear(leaveAlice, cumMonthDays);
            int arriveBobDay = findDayOfYear(arriveBob, cumMonthDays);
            int leaveBobDay = findDayOfYear(leaveBob, cumMonthDays);
    
            int overLapDays = min(leaveAliceDay, leaveBobDay) - max(arriveAliceDay, arriveBobDay) + 1;
    
            return overLapDays < 0 ? 0 : overLapDays;
        }
    };

/*
Approach: Date Conversion + Prefix Sum + Interval Intersection

Intuition:
----------
Alice and Bob each have an arrival date and a departure date.
We need to count the number of days they are both present.

Instead of directly comparing dates in MM-DD format, we convert
each date into its day number within the same non-leap year.

Once all four dates are represented as integers, the overlapping
interval can be calculated easily.

The key formula is:

overlap = min(leaveAliceDay, leaveBobDay)
        - max(arriveAliceDay, arriveBobDay) + 1

The +1 is necessary because both arrival and departure dates are
inclusive.

--------------------------------------------------
1. Helper Function: findDayOfYear()
--------------------------------------------------

int findDayOfYear(string& day, const vector<int>& cumMonthDays)

This function converts a date in MM-DD format into its day number
within the year.

For example:
"03-15" represents March 15.

Step 1: Extract the Month
-------------------------
int month = stoi(day.substr(0, 2));

day.substr(0, 2) extracts the first two characters, representing
the month.

stoi() converts those characters into an integer.

For "03-15":
month = 3

Step 2: Extract the Day of the Month
------------------------------------
int date = stoi(day.substr(3));

day.substr(3) extracts the substring beginning at index 3,
which contains the day of the month.

For "03-15":
date = 15

Step 3: Calculate the Day Number
--------------------------------
return cumMonthDays[month - 1] + date;

cumMonthDays[month - 1] stores the total number of days in all
months before the current month.

Adding date gives the day number within the year.

For example:
- January 1  -> 1
- February 1 -> 32
- March 1    -> 60
- March 15   -> 74

The function assumes a non-leap year, so February has 28 days.

--------------------------------------------------
2. Store the Number of Days in Each Month
--------------------------------------------------

vector<int> monthDays = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
};

monthDays[i] stores the number of days in month i + 1.

For example:
monthDays[0] = 31  // January
monthDays[1] = 28  // February
monthDays[2] = 31  // March

February has 28 days because the problem uses dates from a
non-leap year.

--------------------------------------------------
3. Build the Cumulative Month-Day Array
--------------------------------------------------

vector<int> cumMonthDays(13, 0);

for(int i = 1; i <= 12; i++)
    cumMonthDays[i] = cumMonthDays[i-1] + monthDays[i-1];

cumMonthDays[i] stores the total number of days in the first
i months.

The array has 13 elements so that month indices can be used
directly when calculating cumulative totals.

Its values are:

cumMonthDays[0]  = 0
cumMonthDays[1]  = 31
cumMonthDays[2]  = 59
cumMonthDays[3]  = 90
cumMonthDays[4]  = 120
...
cumMonthDays[12] = 365

For example, cumMonthDays[2] = 59 means January and February
contain 59 days in total.

This preprocessing allows every date to be converted in O(1) time.

--------------------------------------------------
4. Convert All Four Dates
--------------------------------------------------

int arriveAliceDay =
    findDayOfYear(arriveAlice, cumMonthDays);

int leaveAliceDay =
    findDayOfYear(leaveAlice, cumMonthDays);

int arriveBobDay =
    findDayOfYear(arriveBob, cumMonthDays);

int leaveBobDay =
    findDayOfYear(leaveBob, cumMonthDays);

Now all dates are represented as integer day numbers.

Alice's interval is:
[arriveAliceDay, leaveAliceDay]

Bob's interval is:
[arriveBobDay, leaveBobDay]

Both intervals include their starting and ending days.

Using integer day numbers makes it straightforward to calculate
their intersection.

--------------------------------------------------
5. Calculate the Overlapping Interval
--------------------------------------------------

int overLapDays =
    min(leaveAliceDay, leaveBobDay)
    - max(arriveAliceDay, arriveBobDay) + 1;

The overlap begins on the later of the two arrival dates:

overlapStart = max(arriveAliceDay, arriveBobDay)

The overlap ends on the earlier of the two departure dates:

overlapEnd = min(leaveAliceDay, leaveBobDay)

Therefore, the number of overlapping days is:

overlapEnd - overlapStart + 1

Why use min() for the departure dates?
--------------------------------------
Both people must still be present, so the overlap cannot continue
past the earlier departure date.

Why use max() for the arrival dates?
------------------------------------
The overlap cannot begin until both people have arrived, so it
starts at the later arrival date.

Why add 1?
----------
The endpoints are inclusive.

For example, the interval from day 10 through day 12 contains:
10, 11, 12

That is 12 - 10 + 1 = 3 days.

--------------------------------------------------
6. Handle Non-Overlapping Intervals
--------------------------------------------------

return overLapDays < 0 ? 0 : overLapDays;

If the intervals do not overlap, the calculated value is negative,
so the function returns zero.

If they overlap, the calculated value is non-negative and is
returned directly.

For example:
Alice: days 10 through 12
Bob:   days 15 through 18

overlapStart = 15
overlapEnd = 12

overLapDays = 12 - 15 + 1 = -2

There are no shared days, so the answer is 0.

If the intervals touch at exactly one day, the formula correctly
returns 1.

--------------------------------------------------
7. Example Walkthrough
--------------------------------------------------

Suppose:
arriveAlice = "08-01"
leaveAlice  = "08-10"
arriveBob   = "08-05"
leaveBob    = "08-15"

Convert the dates into day numbers:

August 1:
cumMonthDays[7] + 1 = 212

August 10:
cumMonthDays[7] + 10 = 221

August 5:
cumMonthDays[7] + 5 = 216

August 15:
cumMonthDays[7] + 15 = 226

The intervals become:

Alice: [212, 221]
Bob:   [216, 226]

Calculate the overlap:

overlapStart = max(212, 216) = 216
overlapEnd   = min(221, 226) = 221

overLapDays = 221 - 216 + 1 = 6

The shared dates are August 5 through August 10.

Output: 6

--------------------------------------------------
8. Why the Algorithm Works
--------------------------------------------------

Converting every date to a day number preserves chronological order.

For two inclusive intervals, their intersection starts at the later
starting point and ends at the earlier ending point.

If the resulting end is before the start, there is no intersection.
Otherwise, subtracting the start from the end and adding one gives
the exact number of shared days.

Therefore, the algorithm correctly counts the days on which both
Alice and Bob are present.

--------------------------------------------------
9. Complexity Analysis
--------------------------------------------------

Time Complexity: O(1)

- Initializing the month-day array takes constant time.
- Building the cumulative array processes exactly 12 months.
- Converting four dates takes constant time.
- Calculating the overlap takes constant time.

Space Complexity: O(1)

The algorithm uses fixed-size arrays and a constant number of
variables, regardless of the input dates.

Core Idea:
----------
Convert all dates into day numbers, find the later arrival and
earlier departure, and calculate the inclusive intersection of
the two intervals. If the intervals do not overlap, return zero.
*/