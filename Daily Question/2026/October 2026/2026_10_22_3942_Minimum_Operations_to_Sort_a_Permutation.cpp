class Solution {
    public:
        int minOperations(vector<int>& nums) {
            int n = nums.size();
    
            int asc_count = 0;
            int dsc_count = 0;
    
            for(int i = 1; i < n; i++) {
                asc_count += (nums[i] == (nums[i - 1] + 1) % n);
                dsc_count += (nums[i - 1] == (nums[i] + 1) % n);
            }
    
            //0, 1, 2, .... n-1 already sorted
            if(asc_count == n-1 && nums[0] == 0) return 0;
    
            // if exsiting in ascending order
            if(asc_count == n-1) {
                int leftRot  = n - nums[0];
                int rightRot = 1 + (nums.back() + 1) + 1;
                return min(leftRot, rightRot);
            }
    
            // if existing in descending order
            if(dsc_count == n-1) {
                //Mandatory 1 Reverse
                int leftRot = n-nums.back() + 1;
    
                //x Left Rot + 1 Reverse
                int rightRot = (nums[0]+1)%n + 1;
    
                return min(leftRot, rightRot);
            }
    
            return -1;
        }
    };

/*
Problem: LeetCode 3942 - Find Minimum Operations to Sort a Circular Array

Approach: Adjacent Relationship Counting + Greedy Case Analysis

Intuition:
----------
The array is a permutation of values from 0 to n - 1, and the goal
is to determine the minimum operations needed to sort it using the
allowed rotation and reversal operations.

This solution checks whether the array is already sorted, follows
ascending circular order, or follows descending circular order.

The key observation is that adjacent elements in ascending circular
order satisfy:

nums[i] == (nums[i - 1] + 1) % n

Similarly, adjacent elements in descending circular order satisfy:

nums[i - 1] == (nums[i] + 1) % n

The modulo operation handles the circular transition between n - 1
and 0.

--------------------------------------------------
1. Initialize Variables
--------------------------------------------------

int n = nums.size();

Store the length of the array.

int asc_count = 0;
int dsc_count = 0;

- asc_count counts adjacent pairs that follow ascending circular order.
- dsc_count counts adjacent pairs that follow descending circular order.

There are n - 1 adjacent pairs in the array.

If either counter equals n - 1, every adjacent pair follows the
corresponding circular ordering.

--------------------------------------------------
2. Count Ascending and Descending Adjacent Pairs
--------------------------------------------------

for(int i = 1; i < n; i++) {
    asc_count += (nums[i] == (nums[i - 1] + 1) % n);
    dsc_count += (nums[i - 1] == (nums[i] + 1) % n);
}

Ascending circular order:
-------------------------

nums[i] == (nums[i - 1] + 1) % n

The current element must be the next value after the previous
element in circular order.

For example:
... 2, 3, 4, 0, 1 ...

The transition from n - 1 to 0 is handled by modulo n.

If this condition holds for every adjacent pair, asc_count becomes
n - 1.

Descending circular order:
--------------------------

nums[i - 1] == (nums[i] + 1) % n

The previous element must be the next value after the current
element in circular order.

For example:
... 3, 2, 1, 0, n - 1 ...

If this condition holds for every adjacent pair, dsc_count becomes
n - 1.

In C++, each Boolean expression evaluates to 1 when true and 0
when false, so adding these expressions counts matching pairs.

--------------------------------------------------
3. Case 1: Already Sorted
--------------------------------------------------

if(asc_count == n-1 && nums[0] == 0) return 0;

If all adjacent pairs follow ascending circular order and the first
element is 0, the array is already:

[0, 1, 2, ..., n - 1]

No operations are required, so return 0.

The nums[0] == 0 condition distinguishes the normally sorted array
from an ascending circular rotation that begins at another value.

--------------------------------------------------
4. Case 2: Ascending Circular Order
--------------------------------------------------

if(asc_count == n-1) {

If every adjacent pair follows ascending circular order, the array
is an ascending rotation of the sorted sequence.

Two possible rotation counts are calculated, and the smaller one
is returned.

Option 1: Left Rotation
-----------------------

int leftRot = n - nums[0];

The code calculates the number of left rotations required using
the first element's value.

Option 2: Right Rotation
------------------------

int rightRot = 1 + (nums.back() + 1) + 1;

The code calculates an alternative operation count using the last
element of the array, including the additional operations represented
by the two added 1s.

Choose the Minimum
------------------

return min(leftRot, rightRot);

Return whichever of the two calculated counts is smaller.

--------------------------------------------------
5. Case 3: Descending Circular Order
--------------------------------------------------

if(dsc_count == n-1) {

If every adjacent pair follows descending circular order, the array
follows a descending circular sequence.

The solution calculates two possible operation counts.

Option 1: Mandatory Reversal
----------------------------

int leftRot = n-nums.back() + 1;

This expression calculates the candidate count for the approach
commented as requiring one mandatory reversal, together with the
rotation count derived from the last element.

Option 2: Left Rotations + Reversal
-----------------------------------

int rightRot = (nums[0]+1)%n + 1;

This expression calculates the alternative candidate count using
the first element, modulo n, and one additional operation.

Choose the Minimum
------------------

return min(leftRot, rightRot);

Return the smaller of the two candidate operation counts.

--------------------------------------------------
6. Case 4: Neither Circular Order Matches
--------------------------------------------------

return -1;

If the array is neither in ascending circular order nor in
descending circular order, this implementation returns -1.

This represents the case where neither of the two recognized
patterns applies.

--------------------------------------------------
7. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

The loop checks each adjacent pair once, and all subsequent
conditions and calculations take O(1) time.

Space Complexity: O(1)

Only a fixed number of integer variables are used. The array is
not copied or modified.

Core Idea:
----------
Count adjacent pairs that follow ascending and descending circular
order. If the array is already sorted, return 0; otherwise, use the
corresponding case's candidate operation counts and return their
minimum, or -1 if neither pattern matches.

Note:
This comment explains the logic implemented in the provided code.
The exact formulas for the rotation and reversal cases depend on the
operation definitions in the original problem statement.
*/