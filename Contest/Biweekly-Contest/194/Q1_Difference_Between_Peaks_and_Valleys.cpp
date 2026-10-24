class Solution {
    public:
        int peakValleyDifference(vector<int>& nums) {
            int peaks = 0, valleys = 0;
            int n = nums.size();
            for(int i = 1; i < n - 1; i++) {
                if(nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) peaks += nums[i];
                if(nums[i] < nums[i - 1] && nums[i] < nums[i + 1]) valleys += nums[i];
            }
    
            return peaks - valleys;
        }
    };

/*
Approach: Single Pass + Peak and Valley Detection

Intuition:
----------
A peak is an element that is strictly greater than both its neighbors.
A valley is an element that is strictly smaller than both its neighbors.

We need to calculate:

Answer = Sum of Peak Values - Sum of Valley Values

Instead of storing the peak and valley indices separately, we traverse
the array once and directly add each qualifying element to its respective
sum.

1. Initialize Variables
-----------------------
int peaks = 0, valleys = 0;
int n = nums.size();

- peaks stores the sum of all peak values.
- valleys stores the sum of all valley values.
- n represents the length of the array.

Both sums start at zero because initially no peaks or valleys have
been processed.

2. Traverse the Array
---------------------
for(int i = 1; i < n - 1; i++)

We start at index 1 and stop at index n - 2 because the first and last
elements cannot be peaks or valleys.

Both conditions require an element to have a left neighbor and a
right neighbor.

3. Identify Peaks
-----------------
if(nums[i] > nums[i - 1] && nums[i] > nums[i + 1])
    peaks += nums[i];

An element is a peak if it is strictly greater than both adjacent
elements.

For example:
nums = [1, 5, 2]

At index 1:
nums[1] = 5
Left neighbor = 1
Right neighbor = 2

Since 5 > 1 and 5 > 2, the element is a peak.

Therefore, peaks = 5.

Strict inequalities are important: if the current element equals
either neighbor, it is not a peak.

4. Identify Valleys
-------------------
if(nums[i] < nums[i - 1] && nums[i] < nums[i + 1])
    valleys += nums[i];

An element is a valley if it is strictly smaller than both adjacent
elements.

For example:
nums = [5, 2, 4]

At index 1:
nums[1] = 2
Left neighbor = 5
Right neighbor = 4

Since 2 < 5 and 2 < 4, the element is a valley.

Therefore, valleys = 2.

The peak and valley checks are independent, so both conditions are
evaluated for each index.

5. Calculate the Final Difference
---------------------------------
return peaks - valleys;

After processing all interior indices, subtract the sum of valley
values from the sum of peak values.

The result can be positive, negative, or zero.

6. Example Walkthrough
---------------------
nums = [1, 5, 2, 4, 1, 3, 0]

Initially:
peaks = 0
valleys = 0

i = 1:
5 > 1 and 5 > 2
Peak found: peaks = 5

i = 2:
2 < 5 and 2 < 4
Valley found: valleys = 2

i = 3:
4 > 2 and 4 > 1
Peak found: peaks = 9

i = 4:
1 < 4 and 1 < 3
Valley found: valleys = 3

i = 5:
3 > 1 and 3 > 0
Peak found: peaks = 12

Final calculation:
peaks - valleys = 12 - 3 = 9

Output: 9

7. Complexity Analysis
----------------------
Time Complexity: O(n)
- We visit each interior element exactly once.
- Each iteration performs a constant number of comparisons.

Space Complexity: O(1)
- Only a few integer variables are used.
- No additional data structure proportional to n is required.

Core Idea:
----------
Traverse only the interior elements, add strict local maxima to the
peak sum, add strict local minima to the valley sum, and return the
difference between the two sums.
*/