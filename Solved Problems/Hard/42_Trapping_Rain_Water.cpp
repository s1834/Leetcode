class Solution {
    public:
        int trap(vector<int>& height) {
            int l = 0, r = height.size() - 1, leftMax = height[0], rightMax = height[r], water = 0;
            while(l < r) {
                if(leftMax <= rightMax) {
                    l++;
                    leftMax = max(leftMax, height[l]);
                    water += leftMax - height[l];
                } else {
                    r--;
                    rightMax = max(rightMax, height[r]);
                    water += rightMax - height[r];
                }
            }
            return water;
        }
    };

/*

Idea:
------
For every index, the amount of water that can be trapped is:

    min(max height on the left, max height on the right) - current height

Instead of precomputing the maximum height on both sides for every
index, we can use two pointers and maintain these values while
traversing the array.

Key Observation:
----------------
Water trapped at an index depends on the smaller of:

    leftMax
    rightMax

If:

    leftMax <= rightMax

then the left side becomes the limiting boundary.

This means the water trapped at the left pointer is completely
determined by leftMax, regardless of how much taller the right side
becomes later.

Similarly, if:

    rightMax < leftMax

then the right side is the limiting boundary, so we can safely
calculate the water at the right pointer.

Algorithm:
----------
1. Initialize:
      l = 0
      r = n - 1
      leftMax = height[0]
      rightMax = height[n - 1]

2. While l < r:
   - If leftMax <= rightMax:
       • Move the left pointer.
       • Update leftMax.
       • Water trapped at this position is:
             leftMax - height[l]

   - Otherwise:
       • Move the right pointer.
       • Update rightMax.
       • Water trapped at this position is:
             rightMax - height[r]

3. Return the total trapped water.

Why does this work?
-------------------
Suppose:

leftMax = 5
rightMax = 8

The water level on the left can never exceed 5 because the shorter
boundary always limits the water.

Even if the right boundary later becomes 10 or 100, the trapped water
on the left is still determined by 5.

Therefore, when:

    leftMax <= rightMax

we already know enough information to calculate the water at the left
pointer.

The same idea applies symmetrically for the right pointer.

Example:
--------
height = [4,2,0,3,2,5]

Initially:

l = 0
r = 5

leftMax = 4
rightMax = 5

--------------------------------

leftMax <= rightMax

Move left:

l = 1

leftMax = 4

Water += 4 - 2 = 2

--------------------------------

Move left:

l = 2

leftMax = 4

Water += 4 - 0 = 4

Total = 6

--------------------------------

Move left:

l = 3

leftMax = 4

Water += 4 - 3 = 1

Total = 7

--------------------------------

Move left:

l = 4

leftMax = 4

Water += 4 - 2 = 2

Total = 9

--------------------------------

Move left:

l = 5

leftMax = 5

Water += 5 - 5 = 0

Total = 9

Answer:

9

Time Complexity:
----------------
O(n)

Each pointer moves at most n times.

Space Complexity:
-----------------
O(1)

Only a few variables are used.

*/