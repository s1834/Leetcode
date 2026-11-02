class Solution {
    public:
        bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
            int x = target[0];
            int y = target[1];
            int z = target[2];
    
            bool xFound = false, yFound = false, zFound = false;
            int n = triplets.size();
            for(int i = 0; i < n; i++) {
                int a = triplets[i][0];
                int b = triplets[i][1];
                int c = triplets[i][2];
    
                if(a > x || b > y || c > z) continue;
    
                if(a == x) xFound = true;
                if(b == y) yFound = true;
                if(c == z) zFound = true;
            }
    
            return xFound && yFound && zFound;
        }
    };

/*
Problem: LeetCode 1899 - Merge Triplets to Form Target Triplet

Approach: Greedy + Filtering + Coordinate Matching

Intuition:
----------
We are given a list of triplets and a target triplet.

We can merge two triplets by taking the maximum value at
each corresponding position.

For example:

    [1, 3, 2] and [2, 1, 4]

After merging:

    [max(1, 2), max(3, 1), max(2, 4)]
    = [2, 3, 4]

Our goal is to determine whether we can obtain the target
triplet by merging some of the given triplets.

Key Observation:
----------------
Since merging uses the maximum operation, values can only
increase, never decrease.

Therefore, any triplet containing a value greater than the
corresponding target value cannot be used.

For example:

    target  = [3, 5, 4]
    triplet = [2, 6, 3]

This triplet is invalid because:

    6 > 5

If we merge this triplet, the second coordinate will become
at least 6, making it impossible to obtain the target.

Hence, we ignore such triplets.

Among the remaining valid triplets, we only need to check
whether each target coordinate appears at least once in
its corresponding position.

--------------------------------------------------
1. Extract Target Coordinates
--------------------------------------------------

int x = target[0];
int y = target[1];
int z = target[2];

Store the three target values separately for easier
comparison with the given triplets.

--------------------------------------------------
2. Initialize Coordinate Matching Flags
--------------------------------------------------

bool xFound = false, yFound = false, zFound = false;

These flags indicate whether we have found a valid
triplet matching each target coordinate.

- xFound: A valid triplet has first coordinate equal to x.
- yFound: A valid triplet has second coordinate equal to y.
- zFound: A valid triplet has third coordinate equal to z.

Initially, all flags are false.

--------------------------------------------------
3. Iterate Through All Triplets
--------------------------------------------------

int n = triplets.size();

for(int i = 0; i < n; i++) {

    int a = triplets[i][0];
    int b = triplets[i][1];
    int c = triplets[i][2];

    Extract the three coordinates of the current triplet.

}

--------------------------------------------------
4. Skip Invalid Triplets
--------------------------------------------------

if(a > x || b > y || c > z)
    continue;

A triplet is invalid if any coordinate exceeds the
corresponding target coordinate.

Why?

Because merging takes coordinate-wise maximums.

Once a coordinate exceeds its target value, no future
merge can decrease it.

Therefore, such a triplet cannot contribute to a
successful construction.

--------------------------------------------------
5. Check Matching Coordinates
--------------------------------------------------

if(a == x) xFound = true;
if(b == y) yFound = true;
if(c == z) zFound = true;

For every valid triplet, check which target coordinates
it can provide.

We do not need all three coordinates to match within
the same triplet.

Different triplets can contribute different coordinates.

For example:

    target = [3, 5, 4]

    Valid triplets:
        [3, 2, 1]
        [1, 5, 2]
        [2, 3, 4]

The first triplet provides x = 3.
The second triplet provides y = 5.
The third triplet provides z = 4.

Merging them gives:

    [max(3, 1, 2),
     max(2, 5, 3),
     max(1, 2, 4)]

    = [3, 5, 4]

Which exactly matches the target.

--------------------------------------------------
6. Return the Final Result
--------------------------------------------------

return xFound && yFound && zFound;

Return true only when all three target coordinates
have been found among valid triplets.

Otherwise, return false.

--------------------------------------------------
7. Example Walkthrough
--------------------------------------------------

Input:

triplets = [[2, 5, 3],
            [1, 8, 4],
            [3, 2, 4]]

target = [3, 5, 4]

Initially:

    xFound = false
    yFound = false
    zFound = false

Triplet 1: [2, 5, 3]

    All coordinates are <= target.

    b == 5

    yFound = true

Triplet 2: [1, 8, 4]

    b = 8 > 5

    Skip this triplet.

Triplet 3: [3, 2, 4]

    All coordinates are <= target.

    a == 3
    c == 4

    xFound = true
    zFound = true

Final flags:

    xFound = true
    yFound = true
    zFound = true

Result:

    true

Because merging:

    [2, 5, 3] and [3, 2, 4]

Produces:

    [3, 5, 4]

--------------------------------------------------
8. Why Does This Greedy Approach Work?
--------------------------------------------------

The merge operation takes the maximum of each coordinate.

This gives us two important properties:

1. Invalid triplets can be safely ignored.

   Any coordinate exceeding the target makes that
   triplet unusable because maximum values cannot decrease.

2. Valid triplets can be combined independently.

   Every coordinate of a valid triplet is <= the target.

   Therefore, merging valid triplets never exceeds
   the target.

   If we find at least one valid triplet matching each
   target coordinate, merging those triplets produces
   exactly the target.

Thus, checking the three coordinate flags is both
necessary and sufficient.

--------------------------------------------------
9. Complexity Analysis
--------------------------------------------------

Let n be the number of triplets.

Time Complexity: O(n)

We traverse all triplets exactly once.

For each triplet, we perform a constant number of
comparisons.

Space Complexity: O(1)

We only use:
- Three target variables.
- Three coordinate variables.
- Three boolean flags.
- A few loop variables.

No additional data structure is required.

Core Idea:
----------
Since merging takes coordinate-wise maximums:

1. Ignore triplets containing any coordinate greater
   than the target.

2. Among the remaining triplets, check whether each
   target coordinate can be matched.

3. If all three coordinates can be matched, return true.

The entire problem reduces to finding three matching
coordinates among valid triplets.
*/