class Solution {
    public:
        long long maximumValue(int n, int s, int m) {
            if (n == 1) return s;
            return (long long)s +  m + ((long long)(n / 2) - 1) * (m - 1);
        }
    };

/*

Idea:
------
To maximize the largest value in the sequence, we should
increase the sequence whenever possible while still
maintaining the alternating pattern.

There are two possible alternating forms:

1.

High > Low < High > Low ...

2.

Low < High > Low < High ...

Starting from seq[0] = s, the second pattern allows us
to immediately increase the next element by m, leading
to the largest possible values.

------------------------------------------------------------

Key Observation:
----------------

Whenever we move from a "low" position to a "high"
position,

the largest increase allowed is

+m.

To continue alternating,

the next "low" position must be at least 1 smaller than
the previous "high".

Therefore,

every complete pair of moves

High → Low → High

can increase the maximum value by

(m - 1).

------------------------------------------------------------

Pattern:
--------

Starting value

s

First peak

s + m

Second peak

s + m + (m - 1)

Third peak

s + m + 2 × (m - 1)

...

Each additional peak contributes

(m - 1)

to the maximum value.

------------------------------------------------------------

Algorithm:
----------

If

n == 1

the sequence contains only the starting element.

Return

s.

------------------------------------------------------------

Otherwise,

1.

The first peak is

s + m.

2.

There are

(n / 2) - 1

additional peaks.

3.

Each additional peak increases the maximum value by

(m - 1).

Hence,

Answer =

s + m + ((n / 2) - 1) × (m - 1)

------------------------------------------------------------

Example:
--------

Input

n = 4

s = 3

m = 5

Sequence

3

8

7

12

Maximum Value

12

Formula

3 + 5 + (2 - 1) × 4

= 12

------------------------------------------------------------

Example:

n = 6

s = 2

m = 3

Possible sequence

2

5

4

7

6

9

Maximum

9

Formula

2 + 3 + (3 - 1) × 2

= 9

------------------------------------------------------------

Why This Works:
---------------

The maximum element always occurs at a peak.

The first peak is obtained by increasing the starting
value by the maximum allowed amount m.

Every subsequent peak requires one intermediate valley,
which must be at least 1 smaller than the previous peak
to preserve the alternating property.

Thus,

each new peak can increase by only

(m - 1)

over the previous peak.

------------------------------------------------------------

Time Complexity:
----------------

O(1)

Only a few arithmetic operations are performed.

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

No extra space is used.

*/