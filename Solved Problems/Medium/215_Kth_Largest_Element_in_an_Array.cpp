class Solution {
    public:
        int findKthLargest(vector<int>& nums, int k) {
            priority_queue<int, vector<int>, greater<int>> pq;
            for(auto x : nums) {
                pq.push(x);
                if(pq.size() > k) pq.pop();
            }
            return pq.top();
        }
    };

/*

Idea:
------
Maintain a Min Heap of size k containing the k largest
elements seen so far.

The smallest element in this heap is always the kth largest
element in the entire array.

------------------------------------------------------------

Why a Min Heap?
---------------

Suppose

nums =

3 2 1 5 6 4

k = 2

We only need to keep track of the 2 largest elements.

After processing all elements,

Heap:

5 6

The top of the Min Heap is

5

which is exactly the 2nd largest element.

------------------------------------------------------------

Algorithm:
----------

Traverse every element in the array.

1.

Insert the current element into the Min Heap.

2.

If the heap size becomes greater than k,

remove the smallest element.

This ensures the heap always stores only the
k largest elements encountered so far.

------------------------------------------------------------

Example:
--------

nums =

3 2 1 5 6 4

k = 2

Insert:

3

Heap:

3

----------------

Insert:

2

Heap:

2 3

----------------

Insert:

1

Heap:

1 2 3

Size becomes 3 > 2.

Remove the smallest element.

Heap:

2 3

----------------

Insert:

5

Heap:

2 3 5

Remove 2.

Heap:

3 5

----------------

Insert:

6

Heap:

3 5 6

Remove 3.

Heap:

5 6

----------------

Insert:

4

Heap:

4 5 6

Remove 4.

Heap:

5 6

The heap now contains the 2 largest elements.

The top is

5

which is the answer.

------------------------------------------------------------

Why are duplicates not removed?
-------------------------------

The problem asks for the kth largest element,
NOT the kth distinct largest element.

Therefore,

duplicate values are treated as separate elements
and are inserted into the heap normally.

------------------------------------------------------------

Time Complexity:
----------------

O(n log k)

Each insertion/removal takes O(log k).

------------------------------------------------------------

Space Complexity:
-----------------

O(k)

The heap never stores more than k elements.

*/