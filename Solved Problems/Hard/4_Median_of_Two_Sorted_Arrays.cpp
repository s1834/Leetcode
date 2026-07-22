class Solution {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            // we need nums1 size to be smaller
            if(nums2.size() < nums1.size()) return findMedianSortedArrays(nums2, nums1);
           
            int n = nums1.size(), m = nums2.size();
            int left = 0, right = n, total = n + m, half = (total + 1) / 2; 
    
            while(left <= right) {
                int mid1 = left + (right - left) / 2; // nums1
                int mid2 = half - mid1; // nums2
    
                // nums1
                int nums1Left = (mid1 == 0) ? INT_MIN : nums1[mid1 - 1];
                int nums1Right = (mid1 == n) ? INT_MAX : nums1[mid1];
    
                // nums2
                int nums2Left = (mid2 == 0) ? INT_MIN : nums2[mid2 - 1];
                int nums2Right = (mid2 == m) ? INT_MAX : nums2[mid2];
    
                // if partition correct
                if(nums1Left <= nums2Right && nums2Left <= nums1Right) {
                    if(total % 2) return max(nums1Left, nums2Left); // odd
                    else return (max(nums1Left, nums2Left) + min(nums1Right, nums2Right)) / 2.0; // even
                } else if(nums1Left > nums2Right) right = mid1 - 1;
                else left = mid1 + 1;
            }
    
            return 0.0;
        }
    };

/*

Idea:
------
We need to find the median of two sorted arrays without
merging them.

Instead of searching for the median directly,

we search for the correct partition of the two arrays.

A valid partition divides both arrays into two halves
such that

• Every element on the left half is less than or equal to
  every element on the right half.

• The left half contains exactly half of the total
  elements (or one extra element when the total size is
  odd).

Once such a partition is found,

the median can be computed immediately.

------------------------------------------------------------

Why Binary Search on the Smaller Array?
---------------------------------------

Binary Search is performed only on

nums1.

To guarantee

O(log(min(n, m)))

complexity,

we always choose the smaller array.

This also prevents the calculated partition in

nums2

from going outside its valid range.

------------------------------------------------------------

Partition Concept:
------------------

Suppose

nums1

is partitioned after

mid1

elements.

Then,

to keep exactly

half

elements on the left,

the partition in

nums2

must be

mid2 = half - mid1

Example

nums1

1 3 8 | 9

nums2

2 7 | 10 11

Left Half

1 2 3 7 8

Right Half

9 10 11

------------------------------------------------------------

Elements Around the Partition:
------------------------------

For every partition,

only four elements determine whether it is valid.

nums1Left

=

last element on the left of

nums1

nums1Right

=

first element on the right of

nums1

nums2Left

=

last element on the left of

nums2

nums2Right

=

first element on the right of

nums2

When the partition is at the beginning or end of an
array,

INT_MIN

and

INT_MAX

are used so that comparisons remain valid without special
cases.

------------------------------------------------------------

Condition for a Valid Partition:
--------------------------------

The partition is correct if

nums1Left ≤ nums2Right

AND

nums2Left ≤ nums1Right

Mathematically,

Largest element in Left Half

≤

Smallest element in Right Half

If this condition holds,

every element on the left side is less than or equal to
every element on the right side,

which is exactly what we need for the median.

------------------------------------------------------------

How to Move the Binary Search?
------------------------------

Case 1

nums1Left > nums2Right

The partition in

nums1

is too far to the right.

Too many elements from

nums1

have been placed in the left half.

Move left.

right = mid1 - 1

------------------------------------------------------------

Case 2

nums2Left > nums1Right

The partition in

nums1

is too far to the left.

Too few elements from

nums1

are in the left half.

Move right.

left = mid1 + 1

------------------------------------------------------------

Finding the Median:
-------------------

If the total number of elements is odd,

the left half contains one extra element.

Therefore,

Median = max(nums1Left, nums2Left)

--------------------------------

If the total number of elements is even,

the median is the average of

Largest element in Left Half

and

Smallest element in Right Half

Median

=

(max(nums1Left, nums2Left)
+
min(nums1Right, nums2Right))

/ 2

------------------------------------------------------------

Example:
--------

nums1

[1,3]

nums2

[2]

Swap arrays because Binary Search is performed on the
smaller array.

nums1

[2]

nums2

[1,3]

Total = 3

Half = 2

--------------------------------

Partition

nums1

[2 | ]

nums2

[1 | 3]

nums1Left = 2

nums1Right = +∞

nums2Left = 1

nums2Right = 3

Check

2 ≤ 3 ✔

1 ≤ +∞ ✔

Valid Partition.

Total is odd.

Median

max(2,1)

=

2

------------------------------------------------------------

Example:
--------

nums1

[1,2]

nums2

[3,4]

Total = 4

Half = 2

--------------------------------

Partition

[1,2 | ]

[ | 3,4]

nums1Left = 2

nums1Right = +∞

nums2Left = -∞

nums2Right = 3

Valid Partition.

Median

(2 + 3) / 2

=

2.5

------------------------------------------------------------

Why Does This Work?
-------------------

Binary Search finds the unique partition where

all left-half elements

≤

all right-half elements.

Since the left half contains exactly half of the total
elements,

the median must lie on the boundary between these two
halves.

Thus,

only the four boundary elements are needed to compute
the answer.

------------------------------------------------------------

Time Complexity:
----------------

Binary Search is performed only on the smaller array.

O(log(min(n, m)))

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

Only a few variables are used.

*/