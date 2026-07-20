class Solution {
    public:
        vector<int> findClosestElements(vector<int>& arr, int k, int x) {
            int n = arr.size(), left = 0, right = n - 1;
            while(right - left + 1 > k) {
                if(abs(arr[left] - x) > abs(arr[right] - x)) left++;
                else right--;
            }
    
            vector<int> ans;
            for(int i = left; i <= right; i++) ans.push_back(arr[i]);
    
            return ans;
        }
    };
    
/*

Idea:
------
We need to find

k

elements that are closest to

x.

Since the array is already sorted,

the final answer will always form one continuous
subarray.

Instead of selecting the closest elements one by one,

we start with the entire array and repeatedly remove the
element that is farther from

x.

Continue shrinking the window until only

k

elements remain.

The remaining window is the required answer.

------------------------------------------------------------

Why Does This Greedy Approach Work?
----------------------------------

Initially,

every element is a candidate.

At each step,

only the two boundary elements

arr[left]

and

arr[right]

can be removed.

If one boundary is farther from

x

than the other,

it can never be part of the optimal answer because every
element inside the window is closer (or equally close)
than that boundary.

Therefore,

removing the farther boundary never removes an element
that should belong to the final answer.

------------------------------------------------------------

Tie Breaking:
-------------

If

|arr[left] - x|

=

|arr[right] - x|

the problem states that the smaller element should be
preferred.

Since the array is sorted,

arr[left]

is always smaller.

Therefore,

remove

arr[right]

and keep

arr[left].

This is exactly what the code does.

------------------------------------------------------------

Algorithm:
----------

1.

Initialize two pointers.

left = 0

right = n - 1

The current window contains the entire array.

------------------------------------------------------------

2.

While the window size is greater than

k,

compare the distances

|arr[left] - x|

and

|arr[right] - x|.

------------------------------------------------------------

3.

If

arr[left]

is farther from

x,

remove it by moving

left

forward.

------------------------------------------------------------

4.

Otherwise,

remove

arr[right]

by moving

right

backward.

This also correctly handles the tie case by keeping the
smaller element.

------------------------------------------------------------

5.

When the window size becomes exactly

k,

copy all elements inside the window into the answer.

------------------------------------------------------------

Why Is the Remaining Window Correct?
------------------------------------

Suppose the current window is

[left ... right]

If

arr[left]

is farther from

x

than

arr[right],

then

arr[left]

is the worst candidate among all elements currently
inside the window.

Removing it cannot improve any future solution because
every remaining element is at least as close to

x.

By repeatedly removing the worst boundary element,

only the

k

closest elements remain.

------------------------------------------------------------

Example:
--------

arr =

[1,2,3,4,5]

k = 4

x = 3

Initially

Window

[1,2,3,4,5]

--------------------------------

Distance from x

1 → 2

5 → 2

Tie.

Keep the smaller element

1

Remove

5

--------------------------------

Remaining Window

[1,2,3,4]

Window size = 4

Stop.

Answer

[1,2,3,4]

------------------------------------------------------------

Example:

arr =

[1,2,3,4,5]

k = 4

x = -1

Window

[1,2,3,4,5]

--------------------------------

Distances

1 → 2

5 → 6

Remove

5

--------------------------------

Window

[1,2,3,4]

Stop.

Answer

[1,2,3,4]

------------------------------------------------------------

Time Complexity:
----------------

The window shrinks

n - k

times.

Each iteration performs constant work.

Overall:

O(n)

Copying the final answer requires

O(k).

Total:

O(n)

------------------------------------------------------------

Space Complexity:
-----------------

O(k)

for storing the answer.

The algorithm itself uses only constant extra space.

*/