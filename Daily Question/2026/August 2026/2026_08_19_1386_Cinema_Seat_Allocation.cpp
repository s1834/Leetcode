class Solution {
    public:
        int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
            unordered_map<int, vector<bool>> mp;
    
            for (auto &seat : reservedSeats) {
                int row = seat[0];
                int col = seat[1];
                
                // only create a vector for rows that actually appear in reservedSeats
                if (!mp.count(row)) mp[row] = vector<bool>(11, false);
    
                mp[row][col] = true;
            }
    
            int ans = 2 * (n - mp.size());
            for(auto &x : mp) {
                bool left = !mp[x.first][2] && !mp[x.first][3] && !mp[x.first][4] && !mp[x.first][5];
                bool middle = !mp[x.first][4] && !mp[x.first][5] && !mp[x.first][6] && !mp[x.first][7];
                bool right = !mp[x.first][6] && !mp[x.first][7] && !mp[x.first][8] && !mp[x.first][9];
    
                if(left && right) ans += 2;
                else if(left || middle || right) ans++;
            }
    
            return ans;
        }
    };

/*
LeetCode 1386. Cinema Seat Allocation

Approach:
---------

Each row has 10 seats:

    1 2 3 4 5 6 7 8 9 10

A family needs 4 consecutive seats.

The only possible groups of 4 seats are:

    Left:
        2 3 4 5

    Middle:
        4 5 6 7

    Right:
        6 7 8 9

Notice that seats 1 and 10 are never part of a family group.

------------------------------------------------------------

Key Observation:
----------------

If a row has NO reserved seats, we can always place:

    2 families

For example:

    Family 1 -> seats 2,3,4,5
    Family 2 -> seats 6,7,8,9

So we can initially count:

    2 * (number of rows with no reservations)

------------------------------------------------------------

Why Use unordered_map?
----------------------

    unordered_map<int, vector<bool>> mp;

We only need to store information for rows that actually have
reserved seats.

There can be a very large number of rows (up to n), but only
reserved rows can have their answer different from 2.

So instead of creating a 10-seat representation for every row,
we create one only when a row appears in reservedSeats.

For example:

    reservedSeats = [[2,5], [2,8], [5,3]]

Only rows:

    2
    5

are stored in mp.

All other rows automatically contribute 2 families.

------------------------------------------------------------

Store Reserved Seats:
---------------------

    for(auto &seat : reservedSeats) {

        int row = seat[0];
        int col = seat[1];

        if(!mp.count(row))
            mp[row] = vector<bool>(11, false);

        mp[row][col] = true;
    }

The vector has size 11 so that we can directly use:

    mp[row][1]
    mp[row][2]
    ...
    mp[row][10]

Index 0 is simply unused.

A value of:

    true

means that the seat is reserved.

A value of:

    false

means that the seat is available.

------------------------------------------------------------

Count Rows With No Reservations:
---------------------------------

    int ans = 2 * (n - mp.size());

Here:

    n

is the total number of rows.

And:

    mp.size()

is the number of rows that contain at least one reserved seat.

Therefore:

    n - mp.size()

is the number of completely empty rows.

Every such row can fit 2 families.

So:

    ans = 2 * emptyRows

------------------------------------------------------------

Now Process Rows With Reservations:
------------------------------------

For every reserved row, we check whether each possible group
of 4 seats is available.

There are only three relevant groups:

    Left:
        2,3,4,5

    Middle:
        4,5,6,7

    Right:
        6,7,8,9

------------------------------------------------------------

Left Group:
------------

    bool left =
        !mp[x.first][2] &&
        !mp[x.first][3] &&
        !mp[x.first][4] &&
        !mp[x.first][5];

This checks whether all seats:

    2,3,4,5

are available.

If all four are unreserved:

    left = true

and one family can sit there.

------------------------------------------------------------

Middle Group:
-------------

    bool middle =
        !mp[x.first][4] &&
        !mp[x.first][5] &&
        !mp[x.first][6] &&
        !mp[x.first][7];

This checks:

    4,5,6,7

If all four are available:

    middle = true

------------------------------------------------------------

Right Group:
-------------

    bool right =
        !mp[x.first][6] &&
        !mp[x.first][7] &&
        !mp[x.first][8] &&
        !mp[x.first][9];

This checks:

    6,7,8,9

If all four are available:

    right = true

------------------------------------------------------------

Why Can't We Simply Add left + middle + right?
-----------------------------------------------

Because the groups overlap.

Left uses:

    2 3 4 5

Middle uses:

    4 5 6 7

Right uses:

    6 7 8 9

So:

    left + middle

cannot both be used because they share seats:

    4,5

Similarly:

    middle + right

cannot both be used because they share:

    6,7

However:

    left + right

DO NOT overlap.

Therefore, if both are available, we can place 2 families.

------------------------------------------------------------

Case 1: Both Left and Right Available
--------------------------------------

    if(left && right)
        ans += 2;

We can place:

    Family 1 -> 2,3,4,5
    Family 2 -> 6,7,8,9

So this row contributes:

    2 families

The middle group doesn't matter in this case because the left
and right groups already give the maximum possible answer.

------------------------------------------------------------

Case 2: At Least One Group Available
-------------------------------------

    else if(left || middle || right)
        ans++;

If left, middle, OR right is available, we can place at least
one family.

Since this condition is reached only when:

    left && right

is false, we cannot place two families.

Therefore, this row contributes:

    1 family

------------------------------------------------------------

Case 3: No Group Available
---------------------------

If:

    left == false
    middle == false
    right == false

then:

    ans

is not increased.

So this row contributes:

    0 families

------------------------------------------------------------

Example:
--------

Suppose a row has reserved seats:

    [1, 5]

Then:

    Left = false

because seat 5 is reserved.

    Middle = true

because:

    4,5,6,7

actually seat 5 is reserved, so middle is also false.

    Right = true

if seats 6,7,8,9 are all free.

Therefore this row can place one family on the right:

    6,7,8,9

So:

    ans += 1

------------------------------------------------------------

Another Example:
-----------------

Suppose a row has no relevant reserved seats:

    reserved = []

Then:

    left = true
    middle = true
    right = true

But we do NOT add 3.

Instead:

    left && right

is true, so:

    ans += 2

because at most 2 families can fit in a row.

This is also why completely empty rows are directly counted as
2.

------------------------------------------------------------

Important Observation:
-----------------------

The middle group:

    4,5,6,7

is only needed when the left and right groups cannot both be
used.

Why?

If:

    left = true
    right = true

we already have the maximum:

    2 families

If either left or right is blocked, the middle group might still
allow one family.

So the logic:

    if(left && right)
        +2
    else if(left || middle || right)
        +1

covers all cases.

------------------------------------------------------------

Overall Flow:
-------------

        Store reserved seats
                 |
                 ↓
       Count completely empty rows
                 |
                 ↓
     Start answer with 2 families
     for every empty row
                 |
                 ↓
       Process only reserved rows
                 |
        +--------+--------+
        |        |        |
       LEFT    MIDDLE    RIGHT
        |        |        |
        +--------+--------+
                 |
                 ↓
       left && right ?
          /       \
        YES       NO
         |         |
        +2     any available?
                    |
                 YES -> +1
                 NO  -> +0

------------------------------------------------------------

Why This Works:
---------------

A row can contain at most 2 families because the two families
must occupy disjoint groups of four seats among seats 2 through 9.

The only way to place 2 families is:

    2,3,4,5

and:

    6,7,8,9

Therefore:

    left && right -> 2

Otherwise, if any valid group exists:

    left || middle || right -> 1

Otherwise:

    0

Rows with no reservations automatically satisfy the best case
and contribute 2.

------------------------------------------------------------

Complexity:
-----------

Let:

    R = number of reserved seats

We process every reserved seat once to build the map:

    O(R)

Then we process every row that appears in reservedSeats.

For each such row, we check only a constant number of seats:

    O(1)

So:

    Time Complexity: O(R)

The map stores information only for rows containing reservations.
Each stored row has a fixed-size vector of 11 elements.

Therefore:

    Space Complexity: O(R)

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This problem looks like a large grid problem because n can be
very large, but we should NOT process every row.

The important observation is:

    "Only rows containing reserved seats can behave differently
     from the default case."

So:

    1. Assume every row can fit 2 families.
    2. Store only rows with reservations.
    3. For each reserved row, check:
           Left   = 2,3,4,5
           Middle = 4,5,6,7
           Right  = 6,7,8,9
    4. If left && right -> add 2.
    5. Otherwise, if any group works -> add 1.
    6. Otherwise -> add 0.

The key trick is combining the default answer for untouched rows
with explicit handling only for the rows that actually matter.
*/