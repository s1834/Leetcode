class Solution {
    public:
        vector<int> replaceElements(vector<int>& arr) {
            int n = arr.size(), mx = -1;
            vector<int> ans(n, - 1);
            for(int i = n - 1; i > -1; i--) {
                ans[i] = mx;
                if(arr[i] > mx) mx = arr[i];
            }
            return ans;
        }
    };

/*

Idea:
------
Traverse the array from right to left because each element needs the
greatest element on its right.

Instead of actually reversing the array, simply iterate in reverse.

Thought Process:
----------------
Example:

arr = [17,18,5,4,6,1]

Imagine reading it from the end:

1, 6, 4, 5, 18, 17

Initially, there are no elements to the right of the last element.

So:

mx = -1

For every element:
1. Store the current maximum (mx) as its answer.
2. Update mx if the current element is larger.

Dry Run:
--------

Current = 1

Answer:
[-1]

Update:
mx = 1

------------------------

Current = 6

Answer:
[-1, 1]

Update:
mx = 6

------------------------

Current = 4

Answer:
[-1, 1, 6]

mx remains 6.

------------------------

Current = 5

Answer:
[-1, 1, 6, 6]

mx remains 6.

------------------------

Current = 18

Answer:
[-1, 1, 6, 6, 6]

Update:
mx = 18

------------------------

Current = 17

Answer:
[-1, 1, 6, 6, 6, 18]

Reverse the answer:

[18, 6, 6, 6, 1, -1]

Instead of explicitly reversing the answer at the end, this solution
directly writes each value into its correct position while traversing
from right to left.

Algorithm:
----------
1. Initialize:
      mx = -1
2. Traverse the array from right to left.
3. Store the current maximum in the answer.
4. Update the maximum using the current element.
5. Return the answer.

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(n)

Note:
-----
The solution can be optimized to O(1) extra space by modifying the
original array instead of creating a separate answer vector.

*/