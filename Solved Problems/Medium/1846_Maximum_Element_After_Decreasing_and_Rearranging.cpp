class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int prev = 0;
        for(auto x : arr) prev = min(prev + 1, x);
        return prev;
    }
};

/*

Idea:
------
To maximize the final maximum element, first sort the array.
After sorting, greedily assign each element the largest possible
value while ensuring:

1. The first element becomes 1.
2. Adjacent elements differ by at most 1.
3. We can only decrement elements (never increase them).

Algorithm:
----------
1. Sort the array in non-decreasing order.
2. Maintain 'prev', the maximum valid value assigned so far.
3. For each element x:
      prev = min(prev + 1, x);
   - If x is large enough, increase by exactly 1.
   - Otherwise, keep it as x (since it cannot be increased).
4. After processing all elements, 'prev' is the maximum possible
   value in the rearranged array.

Why Greedy Works:
-----------------
Sorting ensures smaller numbers are placed first.
For every element, assigning the largest valid value
(min(prev + 1, x)) leaves maximum room for future elements,
thereby maximizing the final answer.

Example:
--------
arr = [2, 2, 1, 2, 1]

After sorting:
[1, 1, 2, 2, 2]

prev = 0

1 -> min(1,1) = 1
1 -> min(2,1) = 1
2 -> min(2,2) = 2
2 -> min(3,2) = 2
2 -> min(3,2) = 2

Answer = 2

Time Complexity:
----------------
O(n log n)   // Sorting

Space Complexity:
-----------------
O(1)         // Ignoring the space used by sorting

*/ 