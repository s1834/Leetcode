class Solution {
    public:
        vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
            priority_queue<pair<double, int>> pq;
            int n = points.size();
            for(int i = 0; i < n; i++) {
                pq.push({sqrt((points[i][0] * points[i][0]) + (points[i][1] * points[i][1])), i});
                if(pq.size() > k) pq.pop();
            }
    
            vector<vector<int>> ans;
            while(!pq.empty()) {
                ans.push_back(points[pq.top().second]);
                pq.pop();
            }
            return ans;
        }
    };

/*

Idea:
------
Maintain a Max Heap of size k containing the k closest
points to the origin.

The top of the Max Heap always stores the farthest point
among the current k closest points.

Whenever a new point is closer than the current farthest,
remove the farthest point and insert the new one.

------------------------------------------------------------

Distance Calculation:
---------------------

The Euclidean distance of a point (x, y) from the origin is

sqrt(x² + y²)

For every point, compute its distance and store

(distance, index)

in the Max Heap.

The index is stored so that the original point can
be retrieved later.

------------------------------------------------------------

Algorithm:
----------

For every point:

1.

Compute its distance from the origin.

2.

Push

(distance, index)

into the Max Heap.

3.

If the heap size becomes greater than k,

remove the top element.

Since this is a Max Heap,

the farthest point among the current k + 1 points
is removed.

After processing all points,

the heap contains exactly the k closest points.

------------------------------------------------------------

Example:
--------

points =

(1,3)
(-2,2)
(5,8)

k = 2

Distances:

(1,3)   -> √10
(-2,2)  -> √8
(5,8)   -> √89

----------------

Insert √10

Heap:

√10

----------------

Insert √8

Heap:

√10
√8

----------------

Insert √89

Heap:

√89
√8
√10

Size becomes 3 > 2.

Remove the farthest point.

Heap:

√10
√8

The heap now stores the two closest points.

------------------------------------------------------------

Building the Answer:
--------------------

Each heap element stores the index of a point.

Traverse the heap and use the stored index to
retrieve the original coordinates.

The order of the returned points does not matter,
so they can be extracted directly from the heap.

------------------------------------------------------------

Time Complexity:
----------------

O(n log k)

For each point,

Insertion:

O(log k)

Removal (if required):

O(log k)

------------------------------------------------------------

Space Complexity:
-----------------

O(k)

The heap never stores more than k elements.

*/