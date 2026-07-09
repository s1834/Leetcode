class Solution {
    public:
        int largestRectangleArea(vector<int>& heights) {
            stack<pair<int,int>> st;
            int n = heights.size(), mx = 0;
            for(int i = 0; i < n; i++) {
                int start = i;
                while(!st.empty() && st.top().first > heights[i]) {
                    int area = st.top().first * (i - st.top().second);
                    mx = max(mx, area);
                    start = st.top().second;
                    st.pop();
                }
                st.push({heights[i], start});
            }
            while(!st.empty()) {
                int area = st.top().first * (n - st.top().second);
                mx = max(mx, area);
                st.pop();
            }
            return mx;
        }
    };

/*

Idea:
------
For every bar, assume it is the shortest bar of a rectangle.

The only thing we need to know is:

    "How far can this height extend to the left and right?"

Instead of storing the original index, the stack stores:

    {height, leftMostIndex}

where leftMostIndex is the earliest position from which this height
can start forming a rectangle.

The stack is maintained in increasing order of heights.

------------------------------------------------------------

Algorithm:
----------

1. Traverse the histogram from left to right.

2. For every bar:

      start = current index

3. While the current bar is shorter than the top of the stack:

      • The taller bar has just found its right boundary.

      • Compute its largest possible rectangle.

            height = popped height

            width = current index - leftMostIndex

            area = height × width

      • Update the maximum area.

      • The current shorter bar can extend as far left as the popped bar
        could, so inherit its leftMostIndex.

4. Push the current bar along with its updated leftMostIndex.

5. After processing all bars, the remaining bars never found a smaller
   bar on the right.

   Therefore, each of them extends until the end of the histogram.

------------------------------------------------------------

Example:
--------

Histogram:

[2,1,5,6,2,3]

Process:

2

Stack:
[(2,0)]

----------------

1

2 is taller.

Area = 2 × (1-0) = 2

Current bar inherits start = 0

Push:

[(1,0)]

----------------

5

[(1,0),(5,2)]

----------------

6

[(1,0),(5,2),(6,3)]

----------------

2

6 is taller.

Area = 6 × (4-3) = 6

Current start becomes 3.

5 is taller.

Area = 5 × (4-2) = 10

Current start becomes 2.

Push:

[(1,0),(2,2)]

Current maximum = 10

----------------

3

[(1,0),(2,2),(3,5)]

----------------

End of array

Remaining bars extend till index 5.

Areas:

3 × (6-5) = 3

2 × (6-2) = 8

1 × (6-0) = 6

Maximum remains 10.

------------------------------------------------------------

Why inherit leftMostIndex?
--------------------------

Suppose we have:

[2,4,2]

When the last 2 arrives:

• Pop 4.

• The new 2 can extend wherever 4 could extend.

• Therefore it inherits the leftMostIndex of the popped bar.

This allows every bar to remember the furthest left position
where a rectangle of its height can begin.

------------------------------------------------------------

Time Complexity:
----------------
O(n)

Each bar is pushed into the stack once and popped at most once.

------------------------------------------------------------

Space Complexity:
-----------------
O(n)

In the worst case (strictly increasing heights), every bar remains
in the stack.

*/