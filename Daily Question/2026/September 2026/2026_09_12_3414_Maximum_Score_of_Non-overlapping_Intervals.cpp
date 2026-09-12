// Version 1: Recursion + Memoization (TLE)
// class Solution {
// private:     
//     struct Node {
//         long long weight = -1; // total weight
//         vector<int> idxs; // indexes used
//     };

//     int n;
//     vector<int> nextIdx; // non-overlapping next index to current i
//     vector<vector<Node>> dp; // Memoization

//     // binary search
//     int findNext(vector<vector<int>>& intervals, int endPoint) {
//         int left = 0, right = n - 1;
//         int result = n;

//         while(left <= right) {
//             int mid = left + (right - left) / 2;
//             if(intervals[mid][0] > endPoint) {
//                 result = mid;
//                 right = mid - 1;
//             } else left = mid + 1;
//         }

//         return result;
//     }

//     Node solve(vector<vector<int>>& intervals, int i, int k) {
//         // if 4 intervals choosen or i >= n
//         if(k == 0 || i >= n) return Node();

//         if(dp[i][k].weight != -1) return dp[i][k];

//         // skip current
//         Node skip = solve(intervals, i + 1, k);

//         int wt = intervals[i][2]; // weight
//         int idx = intervals[i][3]; // original index
//         int j = nextIdx[i]; // next non-overlapping index

//         // take = current interval + solve(j, k - 1)
//         Node take = solve(intervals, j, k - 1); // solve(j, k - 1)
//         // current interval
//         take.weight += wt;
//         take.idxs.push_back(idx);
//         sort(take.idxs.begin(), take.idxs.end()); // sort to make lexicographically smallest

//         Node result;
//         if(skip.weight > take.weight) result = skip;
//         else if (skip.weight < take.weight) result = take;
//         else result = (skip.idxs < take.idxs) ? skip : take;

//         return dp[i][k] = result;
//     }

// public:
//     vector<int> maximumWeight(vector<vector<int>>& intervals) {
//         n = intervals.size();

//         // store the indexes in intervals before sorting
//         for(int i = 0; i < n; i++) intervals[i].push_back(i);
        
//         // sort in ascending order to efficiently check the end points
//         sort(intervals.begin(), intervals.end());

//         // preprocessing the end point
//         nextIdx.resize(n);
//         for(int i = 0; i < n; i++) nextIdx[i] = findNext(intervals, intervals[i][1]); // intervals[i][1] = endPoint

//         int k = 4; // max non-overlapping intervals allowed
//         dp.assign(n + 1, vector<Node>(k + 1)); // memoization
//         return solve(intervals, 0, k).idxs; // solve(intervals, startIndex, maxIntervalsAllowed)
//     }
// };

/*
LeetCode 3414. Maximum Weight

Approach:
---------

We need to select at most 4 non-overlapping intervals such that:

    1. The total weight is maximum.
    2. If multiple selections have the same maximum weight,
       return the lexicographically smallest list of original indexes.

The main idea is:

    Sorting + Binary Search + Dynamic Programming

We sort the intervals by their start time. This allows us to
efficiently find the next interval that can be selected after
choosing the current interval.

------------------------------------------------------------

Step 1: Store Original Index
----------------------------

Before sorting, we append the original index to every interval:

    for(int i = 0; i < n; i++)
        intervals[i].push_back(i);

Initially:

    [start, end, weight]

becomes:

    [start, end, weight, originalIndex]

For example:

    intervals = [
        [1, 3, 5],
        [2, 5, 10]
    ]

becomes:

    [1, 3, 5, 0]
    [2, 5, 10, 1]

This is necessary because after sorting, the position of an
interval in the vector is no longer its original index.

------------------------------------------------------------

Step 2: Sort Intervals
----------------------

    sort(intervals.begin(), intervals.end());

We sort primarily by:

    start time

This is useful because once the intervals are sorted, all intervals
after a certain position have start times >= the current position.

That allows us to use binary search to find the next compatible
interval.

------------------------------------------------------------

Step 3: Find the Next Non-Overlapping Interval
----------------------------------------------

For every interval i, we calculate:

    nextIdx[i]

which represents the first interval whose start time is strictly
greater than the current interval's end time.

The condition is:

    intervals[mid][0] > endPoint

Notice the STRICTLY greater than condition.

If the current interval is:

    [1, 3]

then the next interval must start at:

    4 or greater

An interval starting at 3 would overlap because the problem requires
the next interval's start to be greater than the current end.

------------------------------------------------------------

Binary Search
-------------

    int left = 0, right = n - 1;
    int result = n;

We search for the first position satisfying:

    intervals[mid][0] > endPoint

If the condition is satisfied:

    result = mid;

But there might be an even earlier valid interval, so continue
searching on the left:

    right = mid - 1;

Otherwise, if:

    intervals[mid][0] <= endPoint

the interval overlaps with the current interval, so we need to
search to the right:

    left = mid + 1;

If no valid interval exists, we return:

    n

which acts as the end of the array.

------------------------------------------------------------

Step 4: DP State
----------------

The DP state is:

    dp[i][k]

where:

    i = current interval index
    k = number of intervals we are still allowed to choose

Each DP state stores a Node:

    struct Node {
        long long weight;
        vector<int> idxs;
    };

So each state remembers:

    weight -> maximum total weight
    idxs   -> indexes that achieve that weight

This is important because we do not only need the maximum weight.

If two choices have the same weight, we must return the
lexicographically smaller list of indexes.

------------------------------------------------------------

Why is weight initialized to -1?
---------------------------------

    long long weight = -1;

A weight of -1 means that this DP state has not been calculated yet.

Therefore:

    if(dp[i][k].weight != -1)
        return dp[i][k];

means:

    "This state has already been calculated, so return the
     memoized answer."

The base case uses:

    Node()

which has:

    weight = -1
    idxs = {}

This represents that there are no more intervals to choose.

------------------------------------------------------------

Step 5: Recursive DP
--------------------

The function:

    solve(intervals, i, k)

means:

    Starting from interval i, choose at most k non-overlapping
    intervals to maximize the total weight.

There are two choices for every interval:

    1. Skip the current interval.
    2. Take the current interval.

------------------------------------------------------------

Choice 1: Skip Current Interval
--------------------------------

    Node skip = solve(intervals, i + 1, k);

We simply ignore interval i and continue with:

    i + 1

while keeping the same number of intervals available:

    k

------------------------------------------------------------

Choice 2: Take Current Interval
-------------------------------

Suppose the current interval is:

    [start, end, weight, originalIndex]

We retrieve:

    int wt = intervals[i][2];
    int idx = intervals[i][3];

Then:

    int j = nextIdx[i];

gives us the first interval that does not overlap with the
current interval.

We solve the remaining problem:

    solve(intervals, j, k - 1)

because choosing the current interval uses one of our allowed
intervals.

Then we add the current interval's weight:

    take.weight += wt;

and its original index:

    take.idxs.push_back(idx);

------------------------------------------------------------

Why Do We Sort take.idxs?
--------------------------

    sort(take.idxs.begin(), take.idxs.end());

The final answer must be lexicographically smallest by the
ORIGINAL indexes.

Because intervals are processed in sorted order of their start
times, the indexes we collect are not necessarily in increasing
order.

For example, we could get:

    [7, 2, 5]

But for lexicographical comparison, we need:

    [2, 5, 7]

Therefore, we sort the selected original indexes before comparing
two solutions.

------------------------------------------------------------

Comparing Skip and Take
-----------------------

After calculating both possibilities:

    skip
    take

we first compare their total weights.

If:

    skip.weight > take.weight

then skipping is better.

If:

    skip.weight < take.weight

then taking is better.

The important case is when:

    skip.weight == take.weight

In that case, both choices produce the same maximum weight.

Therefore, we use the required tie-breaker:

    result = (skip.idxs < take.idxs) ? skip : take;

C++ compares vectors lexicographically.

For example:

    [1, 4, 7]
    [1, 5, 6]

Both start with 1.

Then:

    4 < 5

so:

    [1, 4, 7]

is lexicographically smaller.

------------------------------------------------------------

Example of Tie-Breaking
------------------------

Suppose two possible answers have:

    Weight = 20

but their indexes are:

    [1, 5]
    [2, 3]

Since both have the same weight, we compare the index vectors.

At the first position:

    1 < 2

Therefore:

    [1, 5]

is chosen.

This is exactly why the DP stores both:

    maximum weight
    corresponding indexes

instead of storing only an integer.

------------------------------------------------------------

Base Cases
----------

    if(k == 0 || i >= n)
        return Node();

There are two situations where we cannot choose anything more.

1. We have already selected the maximum allowed number of
   intervals:

       k == 0

2. We have reached the end of the sorted intervals:

       i >= n

In both cases, there is nothing more to add.

------------------------------------------------------------

Why k = 4?
-----------

The problem allows selecting at most 4 non-overlapping intervals.

Therefore:

    int k = 4;

and the initial DP call is:

    solve(intervals, 0, k)

meaning:

    Start from the first sorted interval and select at most
    4 intervals.

------------------------------------------------------------

Complete DP Decision
--------------------

For every interval:

                    Current Interval
                          |
                 +--------+--------+
                 |                 |
               SKIP              TAKE
                 |                 |
              i + 1          current weight
                 |                 +
                 |            solve(nextIdx, k - 1)
                 |                 |
                 +--------+--------+
                          |
                     Compare
                          |
                 +--------+--------+
                 |                 |
             Higher weight     Same weight
                 |                 |
              Choose it       Lexicographically
                              smaller indexes

------------------------------------------------------------

Example:
---------

Suppose we have:

    [1, 2, 5]
    [3, 4, 10]
    [5, 6, 7]

After sorting, if we choose:

    [1, 2, 5]

then the next interval must have:

    start > 2

So:

    [3, 4, 10]

is compatible.

Its next compatible interval can then be found using
nextIdx again.

The DP therefore avoids checking every possible combination
manually.

------------------------------------------------------------

Why Binary Search?
------------------

Without binary search, for every interval we would scan forward
to find the next non-overlapping interval.

That could take:

    O(n)

for every interval.

Instead, because the intervals are sorted by start time, we use
binary search.

Therefore finding nextIdx takes:

    O(log n)

for each interval.

For all intervals:

    O(n log n)

------------------------------------------------------------

Why Memoization?
----------------

Without DP, every interval could branch into:

    skip
    take

which would lead to an exponential number of possibilities.

The state is completely determined by:

    i
    k

So once:

    solve(i, k)

has been calculated, we store it in:

    dp[i][k]

and reuse it whenever the same state appears again.

------------------------------------------------------------

Algorithm:
----------

    1. Store the original index of every interval.

    2. Sort all intervals by start time.

    3. For every interval, use binary search to find the first
       non-overlapping interval.

    4. Use DP:

           solve(i, k)

       where i is the current interval and k is the number of
       intervals we can still choose.

    5. At every interval, consider:

           Skip:
               solve(i + 1, k)

           Take:
               current weight +
               solve(nextIdx[i], k - 1)

    6. Choose the option with larger total weight.

    7. If weights are equal, choose the lexicographically smaller
       list of original indexes.

    8. Return the selected original indexes.

------------------------------------------------------------

Time Complexity:
----------------

Sorting:

    O(n log n)

Finding nextIdx for every interval:

    O(n log n)

DP states:

    O(n * 4)

Since k is fixed at 4:

    O(n)

However, each state may perform vector copying and sorting of at
most 4 indexes, which is bounded by a constant.

Therefore, the overall complexity is effectively:

    O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

nextIdx:

    O(n)

DP:

    O(n * 4) = O(n)

Recursion stack:

    O(n)

Therefore:

    O(n)

excluding the input and output arrays.

------------------------------------------------------------

Core Idea:
----------

Sort intervals so that we can find the next compatible interval
using binary search.

Then use DP on:

    (current interval, intervals remaining)

with two choices:

    Skip current interval
            OR
    Take current interval

For each state, store:

    maximum weight
    + corresponding original indexes

Finally:

    Higher weight -> choose it
    Same weight   -> lexicographically smaller indexes

This gives both the maximum total weight and the required
lexicographically smallest answer.
*/


// Version 2: Bottom-Up
class Solution {
    private:     
        struct Node {
            long long weight = -1; // total weight
            vector<int> idxs; // indexes used
        };
    
        int n;
        vector<int> nextIdx; // non-overlapping next index to current i
        vector<vector<Node>> dp; // Memoization
    
        // binary search
        int findNext(vector<vector<int>>& intervals, int endPoint) {
            int left = 0, right = n - 1;
            int result = n;
    
            while(left <= right) {
                int mid = left + (right - left) / 2;
                if(intervals[mid][0] > endPoint) {
                    result = mid;
                    right = mid - 1;
                } else left = mid + 1;
            }
    
            return result;
        }
    
    public:
        vector<int> maximumWeight(vector<vector<int>>& intervals) {
            n = intervals.size();
    
            // store the indexes in intervals before sorting
            for(int i = 0; i < n; i++) intervals[i].push_back(i);
            
            // sort in ascending order to efficiently check the end points
            sort(intervals.begin(), intervals.end());
    
            // preprocessing the end point
            nextIdx.resize(n);
            for(int i = 0; i < n; i++) nextIdx[i] = findNext(intervals, intervals[i][1]); // intervals[i][1] = endPoint
    
            int K = 4; // max non-overlapping intervals allowed
            dp.assign(n + 1, vector<Node>(K + 1)); // 
            
            for(int i = n - 1; i >= 0; i--) {
                int wt = intervals[i][2]; // weight
                int idx = intervals[i][3]; // original index
                int j = nextIdx[i]; // next non-overlapping index
    
                for(int k = 1; k <= K; k++) {
                    // skip current
                    Node skip = dp[i + 1][k]; // solve(intervals, i + 1, k);
    
                    // take = current interval + solve(j, k - 1)
                    Node take = dp[j][k - 1]; // solve(intervals, j, k - 1);
                    // current interval
                    take.weight += wt;
                    take.idxs.push_back(idx);
                    sort(take.idxs.begin(), take.idxs.end()); // sort to make lexicographically smallest
    
                    Node result;
                    if(skip.weight > take.weight) result = skip;
                    else if (skip.weight < take.weight) result = take;
                    else result = (skip.idxs < take.idxs) ? skip : take;
    
                    dp[i][k] = result;
                }
            }
            return dp[0][K].idxs; // solve(intervals, 0, K)
        }
    };

/*
LeetCode 3414. Maximum Weight

Approach:
---------

We need to select at most 4 non-overlapping intervals such that:

    1. The total weight is maximum.
    2. If multiple selections have the same maximum weight,
       return the lexicographically smallest list of original indexes.

The main idea is:

    Sorting + Binary Search + Dynamic Programming

We sort the intervals by their start time. This allows us to
efficiently find the next interval that can be selected after
choosing the current interval.

------------------------------------------------------------

Step 1: Store Original Index
----------------------------

Before sorting, we append the original index to every interval:

    for(int i = 0; i < n; i++)
        intervals[i].push_back(i);

Initially:

    [start, end, weight]

becomes:

    [start, end, weight, originalIndex]

For example:

    intervals = [
        [1, 3, 5],
        [2, 5, 10]
    ]

becomes:

    [1, 3, 5, 0]
    [2, 5, 10, 1]

This is necessary because after sorting, the position of an
interval in the vector is no longer its original index.

------------------------------------------------------------

Step 2: Sort Intervals
----------------------

    sort(intervals.begin(), intervals.end());

We sort primarily by:

    start time

This is useful because once the intervals are sorted, all intervals
after a certain position have start times >= the current position.

That allows us to use binary search to find the next compatible
interval.

------------------------------------------------------------

Step 3: Find the Next Non-Overlapping Interval
----------------------------------------------

For every interval i, we calculate:

    nextIdx[i]

which represents the first interval whose start time is strictly
greater than the current interval's end time.

The condition is:

    intervals[mid][0] > endPoint

Notice the STRICTLY greater than condition.

If the current interval is:

    [1, 3]

then the next interval must start at:

    4 or greater

An interval starting at 3 would overlap because the problem requires
the next interval's start to be greater than the current end.

------------------------------------------------------------

Binary Search
-------------

    int left = 0, right = n - 1;
    int result = n;

We search for the first position satisfying:

    intervals[mid][0] > endPoint

If the condition is satisfied:

    result = mid;

But there might be an even earlier valid interval, so continue
searching on the left:

    right = mid - 1;

Otherwise, if:

    intervals[mid][0] <= endPoint

the interval overlaps with the current interval, so we need to
search to the right:

    left = mid + 1;

If no valid interval exists, we return:

    n

which acts as the end of the array.

------------------------------------------------------------

Step 4: DP State
----------------

The DP state is:

    dp[i][k]

where:

    i = current interval index
    k = number of intervals we are still allowed to choose

Each DP state stores a Node:

    struct Node {
        long long weight;
        vector<int> idxs;
    };

So each state remembers:

    weight -> maximum total weight
    idxs   -> indexes that achieve that weight

This is important because we do not only need the maximum weight.

If two choices have the same weight, we must return the
lexicographically smaller list of indexes.

------------------------------------------------------------

Why is weight initialized to -1?
---------------------------------

    long long weight = -1;

A weight of -1 means that this DP state has not been calculated yet.

Therefore:

    if(dp[i][k].weight != -1)
        return dp[i][k];

means:

    "This state has already been calculated, so return the
     memoized answer."

The base case uses:

    Node()

which has:

    weight = -1
    idxs = {}

This represents that there are no more intervals to choose.

------------------------------------------------------------

Step 5: Recursive DP
--------------------

The function:

    solve(intervals, i, k)

means:

    Starting from interval i, choose at most k non-overlapping
    intervals to maximize the total weight.

There are two choices for every interval:

    1. Skip the current interval.
    2. Take the current interval.

------------------------------------------------------------

Choice 1: Skip Current Interval
--------------------------------

    Node skip = solve(intervals, i + 1, k);

We simply ignore interval i and continue with:

    i + 1

while keeping the same number of intervals available:

    k

------------------------------------------------------------

Choice 2: Take Current Interval
-------------------------------

Suppose the current interval is:

    [start, end, weight, originalIndex]

We retrieve:

    int wt = intervals[i][2];
    int idx = intervals[i][3];

Then:

    int j = nextIdx[i];

gives us the first interval that does not overlap with the
current interval.

We solve the remaining problem:

    solve(intervals, j, k - 1)

because choosing the current interval uses one of our allowed
intervals.

Then we add the current interval's weight:

    take.weight += wt;

and its original index:

    take.idxs.push_back(idx);

------------------------------------------------------------

Why Do We Sort take.idxs?
--------------------------

    sort(take.idxs.begin(), take.idxs.end());

The final answer must be lexicographically smallest by the
ORIGINAL indexes.

Because intervals are processed in sorted order of their start
times, the indexes we collect are not necessarily in increasing
order.

For example, we could get:

    [7, 2, 5]

But for lexicographical comparison, we need:

    [2, 5, 7]

Therefore, we sort the selected original indexes before comparing
two solutions.

------------------------------------------------------------

Comparing Skip and Take
-----------------------

After calculating both possibilities:

    skip
    take

we first compare their total weights.

If:

    skip.weight > take.weight

then skipping is better.

If:

    skip.weight < take.weight

then taking is better.

The important case is when:

    skip.weight == take.weight

In that case, both choices produce the same maximum weight.

Therefore, we use the required tie-breaker:

    result = (skip.idxs < take.idxs) ? skip : take;

C++ compares vectors lexicographically.

For example:

    [1, 4, 7]
    [1, 5, 6]

Both start with 1.

Then:

    4 < 5

so:

    [1, 4, 7]

is lexicographically smaller.

------------------------------------------------------------

Example of Tie-Breaking
------------------------

Suppose two possible answers have:

    Weight = 20

but their indexes are:

    [1, 5]
    [2, 3]

Since both have the same weight, we compare the index vectors.

At the first position:

    1 < 2

Therefore:

    [1, 5]

is chosen.

This is exactly why the DP stores both:

    maximum weight
    corresponding indexes

instead of storing only an integer.

------------------------------------------------------------

Base Cases
----------

    if(k == 0 || i >= n)
        return Node();

There are two situations where we cannot choose anything more.

1. We have already selected the maximum allowed number of
   intervals:

       k == 0

2. We have reached the end of the sorted intervals:

       i >= n

In both cases, there is nothing more to add.

------------------------------------------------------------

Why k = 4?
-----------

The problem allows selecting at most 4 non-overlapping intervals.

Therefore:

    int k = 4;

and the initial DP call is:

    solve(intervals, 0, k)

meaning:

    Start from the first sorted interval and select at most
    4 intervals.

------------------------------------------------------------

Complete DP Decision
--------------------

For every interval:

                    Current Interval
                          |
                 +--------+--------+
                 |                 |
               SKIP              TAKE
                 |                 |
              i + 1          current weight
                 |                 +
                 |            solve(nextIdx, k - 1)
                 |                 |
                 +--------+--------+
                          |
                     Compare
                          |
                 +--------+--------+
                 |                 |
             Higher weight     Same weight
                 |                 |
              Choose it       Lexicographically
                              smaller indexes

------------------------------------------------------------

Example:
---------

Suppose we have:

    [1, 2, 5]
    [3, 4, 10]
    [5, 6, 7]

After sorting, if we choose:

    [1, 2, 5]

then the next interval must have:

    start > 2

So:

    [3, 4, 10]

is compatible.

Its next compatible interval can then be found using
nextIdx again.

The DP therefore avoids checking every possible combination
manually.

------------------------------------------------------------

Why Binary Search?
------------------

Without binary search, for every interval we would scan forward
to find the next non-overlapping interval.

That could take:

    O(n)

for every interval.

Instead, because the intervals are sorted by start time, we use
binary search.

Therefore finding nextIdx takes:

    O(log n)

for each interval.

For all intervals:

    O(n log n)

------------------------------------------------------------

Why Memoization?
----------------

Without DP, every interval could branch into:

    skip
    take

which would lead to an exponential number of possibilities.

The state is completely determined by:

    i
    k

So once:

    solve(i, k)

has been calculated, we store it in:

    dp[i][k]

and reuse it whenever the same state appears again.

------------------------------------------------------------

Algorithm:
----------

    1. Store the original index of every interval.

    2. Sort all intervals by start time.

    3. For every interval, use binary search to find the first
       non-overlapping interval.

    4. Use DP:

           solve(i, k)

       where i is the current interval and k is the number of
       intervals we can still choose.

    5. At every interval, consider:

           Skip:
               solve(i + 1, k)

           Take:
               current weight +
               solve(nextIdx[i], k - 1)

    6. Choose the option with larger total weight.

    7. If weights are equal, choose the lexicographically smaller
       list of original indexes.

    8. Return the selected original indexes.

------------------------------------------------------------

Time Complexity:
----------------

Sorting:

    O(n log n)

Finding nextIdx for every interval:

    O(n log n)

DP states:

    O(n * 4)

Since k is fixed at 4:

    O(n)

However, each state may perform vector copying and sorting of at
most 4 indexes, which is bounded by a constant.

Therefore, the overall complexity is effectively:

    O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

nextIdx:

    O(n)

DP:

    O(n * 4) = O(n)

Recursion stack:

    O(n)

Therefore:

    O(n)

excluding the input and output arrays.

------------------------------------------------------------

Core Idea:
----------

Sort intervals so that we can find the next compatible interval
using binary search.

Then use DP on:

    (current interval, intervals remaining)

with two choices:

    Skip current interval
            OR
    Take current interval

For each state, store:

    maximum weight
    + corresponding original indexes

Finally:

    Higher weight -> choose it
    Same weight   -> lexicographically smaller indexes

This gives both the maximum total weight and the required
lexicographically smallest answer.
*/