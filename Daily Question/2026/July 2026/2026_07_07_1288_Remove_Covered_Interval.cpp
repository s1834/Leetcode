class Solution {
    private:
        static bool cmp(vector<int>& a, vector<int>& b) {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        }
    
    public:
        int removeCoveredIntervals(vector<vector<int>>& intervals) {
            sort(intervals.begin(), intervals.end(), cmp);
            int right = intervals[0][1], n = intervals.size(), count = 0;
            for (int i = 1; i < n; i++) {
                if(intervals[i][1] <= right) count++;
                else right = intervals[i][1];
            }
            return n - count;
        }
    };

/*

Idea:
------
An interval [a, b] is covered if there exists another interval [c, d]
such that:

    c <= a  and  b <= d

The key observation is that after sorting the intervals in a specific
order, we only need to keep track of the largest right endpoint seen so far.

Sorting Order:
--------------
1. Sort by starting point (left endpoint) in ascending order.
2. If two intervals have the same starting point, sort by ending point
   (right endpoint) in descending order.

Why sort this way?
------------------
Suppose we have:

[1,4]
[1,3]

If we sort the smaller interval first:

[1,3]
[1,4]

we would miss that [1,3] is covered.

Instead, sorting as

[1,4]
[1,3]

ensures the larger interval is processed first, making it easy to
identify covered intervals.

Algorithm:
----------
1. Sort the intervals using the custom comparator.
2. Initialize:
      right = ending point of the first interval.
3. Traverse the remaining intervals.
4. If the current interval's ending point is less than or equal to
   'right', it is covered.
5. Otherwise, update 'right' since we found an interval extending
   farther to the right.
6. Return:
      total intervals - covered intervals.

Example:
--------
Input:

[1,4]
[1,3]
[2,5]
[3,4]

After Sorting:

[1,4]
[1,3]
[2,5]
[3,4]

Initially:

right = 4

--------------------------------

Current: [1,3]

3 <= 4

Covered

count = 1

--------------------------------

Current: [2,5]

5 > 4

Update:

right = 5

--------------------------------

Current: [3,4]

4 <= 5

Covered

count = 2

Answer:

4 - 2 = 2

Time Complexity:
----------------
Sorting: O(n log n)
Traversal: O(n)

Overall:
O(n log n)

Space Complexity:
-----------------
O(1)
(ignoring the space used by the sorting algorithm)

*/