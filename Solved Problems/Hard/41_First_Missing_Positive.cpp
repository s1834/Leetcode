// Solution 1 (not recommended): 
// class Solution {
// public:
//     int firstMissingPositive(vector<int>& nums) {
//         int n = nums.size();
//         bool one = false;
//         for(int i = 0; i < n; i++) {
//             if(nums[i] == 1) one = true;
//             if(nums[i] <= 0 || nums[i] > n) nums[i] = 1;
//         }
//         if(!one) return 1;

//         for (int i = 0; i < n; i++) {
//             int value = abs(nums[i]);
//             if(value == n) {
//                 nums[0] = -abs(nums[0]);
//             } else {
//                 nums[value] = -abs(nums[value]);
//             }
//         }

//         for(int i = 1; i < n; i++) {
//             if(nums[i] > 0) return i;
//         }
//         if(nums[0] > 0) return n;
//         return n + 1;
//     }
// };

class Solution {
    public:
        int firstMissingPositive(vector<int>& nums) {
            int n = nums.size();
            for(int i = 0; i < n; i++) {
                while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
                    swap(nums[i], nums[nums[i] - 1]);
                }
            }
    
            for(int i = 0; i < n; i++) {
                if(nums[i] != i + 1) return i + 1;
            }
            return n + 1;
        }
    };

/*

Idea:
------
We only care about positive numbers in the range:

    1 ... n

where n is the size of the array.

Why?
----
Suppose the array has n elements.

If every number from 1 to n is present, then the smallest missing
positive must be:

    n + 1

Example:

n = 5

[1,2,3,4,5]

Answer = 6

So numbers:
    <= 0
    > n

can never affect the answer and can be ignored.

--------------------------------------------------------------------

Key Observation:
----------------
Every valid number has one unique "correct" position.

Number      Correct Index
------      -------------
1               0
2               1
3               2
4               3
...
x             x - 1

So instead of using a HashSet, we use the array itself as the hash table.

The goal is to place every valid number x at index (x - 1).

--------------------------------------------------------------------

Algorithm:
----------
Phase 1:
Place every valid number in its correct position.

For every index:

while(current number can still be placed correctly)
    swap it with the element at its correct position.

Why use a while loop?
---------------------
After every swap, a new value comes to the current index.

That new value might also belong somewhere else.

So we must continue fixing the same index until:

• the correct number is present,
• the number is invalid (<=0 or >n),
• or a duplicate already exists in its correct position.

--------------------------------------------------------------------

Swap Condition:
---------------

while (

    nums[i] > 0

    &&

    nums[i] <= n

    &&

    nums[i] != nums[nums[i] - 1]

)

Explanation:

1.

nums[i] > 0

Ignore:
    0
    negative numbers

because they can never be the first missing positive.

--------------------------------

2.

nums[i] <= n

Ignore numbers larger than n.

Example:

n = 4

[8,2,1,3]

8 cannot be placed because there is no index 7.

--------------------------------

3.

nums[i] != nums[nums[i] - 1]

Avoid infinite swapping when duplicates exist.

Example:

[1,1]

The second 1 also wants to go to index 0.

Without this condition we'd keep swapping

1 <-> 1

forever.

--------------------------------------------------------------------

Dry Run:
--------

nums = [3,4,-1,1]

Initially

Index:
0 1 2 3

Value:
3 4 -1 1

------------------------------------------------

i = 0

Current value = 3

3 belongs at index 2.

Swap:

[-1,4,3,1]

Stay at i = 0.

Current value = -1

Invalid.

Move to next index.

------------------------------------------------

i = 1

Current value = 4

4 belongs at index 3.

Swap:

[-1,1,3,4]

Stay at i = 1.

Current value = 1

1 belongs at index 0.

Swap:

[1,-1,3,4]

Stay at i = 1.

Current value = -1

Invalid.

Move on.

------------------------------------------------

i = 2

3 is already at index 2.

Nothing to do.

------------------------------------------------

i = 3

4 is already at index 3.

Nothing to do.

------------------------------------------------

Array after rearranging:

[1,-1,3,4]

--------------------------------------------------------------------

Phase 2:
--------

Scan from left to right.

Every index i should contain:

    i + 1

Index 0 -> should contain 1 ✓

Index 1 -> should contain 2 ✗

Found -1

Therefore,

Answer = 2

--------------------------------------------------------------------

Why does this work?
-------------------
After Phase 1, every valid positive number has been moved to its
correct position.

So the first index where

    nums[i] != i + 1

immediately tells us that

    i + 1

is missing.

If every position is correct, then

1 ... n

are all present.

Therefore the answer is

    n + 1

--------------------------------------------------------------------

Time Complexity:
----------------
O(n)

Although there is a while loop, every swap places at least one number
into its correct position.

A number can only be moved a limited number of times, so the total
number of swaps across the entire algorithm is at most O(n).

--------------------------------------------------------------------

Space Complexity:
-----------------
O(1)

No extra data structures are used.

The input array itself acts as the hash table.

*/