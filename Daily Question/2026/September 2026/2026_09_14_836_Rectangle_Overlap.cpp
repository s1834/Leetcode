class Solution {
    public:
        bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
            return (max(rec1[0], rec2[0]) < min(rec1[2], rec2[2])) && (max(rec1[1], rec2[1]) < min(rec1[3], rec2[3]));
        }
    };

/*
LeetCode 836. Rectangle Overlap

Approach:
---------

We need to check whether two rectangles have a positive-area
overlap.

Each rectangle is represented as:

    [x1, y1, x2, y2]

where:

    (x1, y1) = bottom-left corner
    (x2, y2) = top-right corner

For two rectangles to overlap with positive area, they must overlap
on BOTH:

    1. The x-axis
    2. The y-axis

So we independently check the overlap of their x-ranges and
y-ranges.

------------------------------------------------------------

Understanding the X-Axis
------------------------

For rec1:

    x-range = [rec1[0], rec1[2]]

For rec2:

    x-range = [rec2[0], rec2[2]]

The overlapping x-range is:

    left  = max(rec1[0], rec2[0])
    right = min(rec1[2], rec2[2])

For a positive-width overlap, we need:

    left < right

which is:

    max(rec1[0], rec2[0]) < min(rec1[2], rec2[2])

------------------------------------------------------------

Understanding the Y-Axis
------------------------

Similarly, for the y-axis:

For rec1:

    y-range = [rec1[1], rec1[3]]

For rec2:

    y-range = [rec2[1], rec2[3]]

The overlapping y-range is:

    bottom = max(rec1[1], rec2[1])
    top    = min(rec1[3], rec2[3])

For a positive-height overlap:

    bottom < top

which is:

    max(rec1[1], rec2[1]) < min(rec1[3], rec2[3])

------------------------------------------------------------

Final Condition
---------------

Therefore, both conditions must be true:

    x-overlap > 0
    &&
    y-overlap > 0

So the final condition is:

    return (max(rec1[0], rec2[0]) < min(rec1[2], rec2[2]))
        &&
           (max(rec1[1], rec2[1]) < min(rec1[3], rec2[3]));

If both are true, the rectangles overlap with positive area.

------------------------------------------------------------

Why Do We Use max() for the Left/Bottom?
-----------------------------------------

Consider the x-ranges:

    rec1: [1, 5]
    rec2: [3, 7]

The common portion starts at:

    max(1, 3) = 3

and ends at:

    min(5, 7) = 5

Therefore:

    overlap = [3, 5]

Since:

    3 < 5

there is a positive-width overlap.

------------------------------------------------------------

Why Do We Use min() for the Right/Top?
---------------------------------------

The right boundary of the overlap cannot go beyond the smaller
right boundary.

For:

    [1, 5]
    [3, 7]

the common portion ends at:

    min(5, 7) = 5

Similarly, for the y-axis, the common portion ends at the smaller
top boundary.

------------------------------------------------------------

Important: Why Strictly '<'?
----------------------------

We need the rectangles to overlap by a POSITIVE AREA.

Suppose:

    rec1 x-range = [1, 3]
    rec2 x-range = [3, 5]

Then:

    max(1, 3) = 3
    min(3, 5) = 3

So:

    3 < 3

is false.

The rectangles only touch at their boundary.

There is no positive-width overlap, so they do NOT overlap.

This is why we use:

    <

instead of:

    <=

------------------------------------------------------------

Example 1:
----------

    rec1 = [0, 0, 2, 2]
    rec2 = [1, 1, 3, 3]

X-axis:

    max(0, 1) = 1
    min(2, 3) = 2

    1 < 2 -> true

Y-axis:

    max(0, 1) = 1
    min(2, 3) = 2

    1 < 2 -> true

Both conditions are true.

Therefore:

    return true

The overlapping region has positive width and height.

------------------------------------------------------------

Example 2: Touching Edges
--------------------------

    rec1 = [0, 0, 2, 2]
    rec2 = [2, 0, 4, 2]

X-axis:

    max(0, 2) = 2
    min(2, 4) = 2

    2 < 2 -> false

The rectangles only touch at the vertical boundary x = 2.

Therefore:

    return false

------------------------------------------------------------

Example 3: One Rectangle Completely Inside Another
---------------------------------------------------

    rec1 = [0, 0, 10, 10]
    rec2 = [2, 2, 5, 5]

X-axis:

    max(0, 2) = 2
    min(10, 5) = 5

    2 < 5 -> true

Y-axis:

    max(0, 2) = 2
    min(10, 5) = 5

    2 < 5 -> true

Therefore:

    return true

The second rectangle is completely inside the first one, so
they clearly have positive-area overlap.

------------------------------------------------------------

Example 4: No Overlap
----------------------

    rec1 = [0, 0, 2, 2]
    rec2 = [3, 3, 5, 5]

X-axis:

    max(0, 3) = 3
    min(2, 5) = 2

    3 < 2 -> false

Since there is no x-axis overlap, the rectangles cannot overlap.

The second condition does not matter because we already know the
answer is false.

------------------------------------------------------------

Geometric Idea:
---------------

Think of the rectangles as overlapping only if their projections
on both axes overlap:

             X-axis overlap
                   &&
             Y-axis overlap
                   |
                   v
          Positive-area overlap

If either axis has no positive overlap:

    X overlap = 0
          OR
    Y overlap = 0

then:

    Rectangle overlap = false

------------------------------------------------------------

Algorithm:
----------

    1. Find the overlapping range on the x-axis:

           max(left boundaries)
           <
           min(right boundaries)

    2. Find the overlapping range on the y-axis:

           max(bottom boundaries)
           <
           min(top boundaries)

    3. Return true only if both conditions are satisfied.

------------------------------------------------------------

Time Complexity:
----------------

Only a constant number of operations are performed.

Therefore:

    O(1)

------------------------------------------------------------

Space Complexity:
-----------------

Only a few temporary values are used.

Therefore:

    O(1)

------------------------------------------------------------

Core Idea:
----------

Two rectangles have positive-area overlap if and only if they
overlap with POSITIVE length on both axes.

    X-axis:
        max(x1) < min(x2)

    Y-axis:
        max(y1) < min(y2)

Therefore:

    x-overlap && y-overlap

The strict '<' is important because merely touching at an edge
or corner does not count as an overlap.
*/