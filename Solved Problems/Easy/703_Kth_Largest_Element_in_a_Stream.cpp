class KthLargest {
    private:
        int maxSize;
        priority_queue<int, vector<int>, greater<int>> pq;
    
    public:
        KthLargest(int k, vector<int>& nums) {
            maxSize = k;
            for(auto x : nums) {
                pq.push(x);
                if(pq.size() > maxSize) pq.pop();
            }
        }
        
        int add(int val) {
            pq.push(val);
            if(pq.size() > maxSize) pq.pop();
            return pq.top();
        }
    };
    
    /**
     * Your KthLargest object will be instantiated and called as such:
     * KthLargest* obj = new KthLargest(k, nums);
     * int param_1 = obj->add(val);
     */

/*

Idea:
------
Maintain a Min Heap containing only the k largest elements
seen so far.

The smallest element in this heap is always the kth largest
element of the entire stream.

------------------------------------------------------------

Why a Min Heap?
---------------

Suppose

k = 3

Numbers seen so far:

2 4 5 8 10

The 3 largest elements are

5 8 10

If we store only these three elements in a Min Heap,

        5
       / \
      8  10

The top of the heap is

5

which is exactly the 3rd largest element.

------------------------------------------------------------

Constructor:
------------

Insert every element from the initial array into the heap.

If the heap size exceeds k,

remove the smallest element.

This ensures the heap always stores only the k largest
elements seen so far.

Example:

k = 3

nums =

4 5 8 2

Insert:

4

Heap:

4

----------------

Insert:

5

Heap:

4 5

----------------

Insert:

8

Heap:

4 5 8

----------------

Insert:

2

Heap:

2 4 5 8

Size becomes 4 > 3.

Remove the smallest element.

Heap:

4 5 8

Now the heap contains exactly the
3 largest elements.

------------------------------------------------------------

add(val):
---------

Insert the new value into the heap.

If the heap size exceeds k,

remove the smallest element.

Again, only the k largest elements remain.

Since the heap is a Min Heap,

its top is always the smallest among these k elements,
which is exactly the kth largest element overall.

Return:

pq.top()

------------------------------------------------------------

Example:
--------

k = 3

Initial Heap:

4 5 8

Current answer:

4

----------------

add(10)

Heap:

4 5 8 10

Remove smallest:

5 8 10

Return:

5

----------------

add(9)

Heap:

5 8 10 9

Remove smallest:

8 9 10

Return:

8

------------------------------------------------------------

Time Complexity:
----------------

Constructor:

O(n log k)

Each insertion/removal takes O(log k).

------------------------------------------------------------

add():

O(log k)

One insertion and at most one removal.

------------------------------------------------------------

Space Complexity:
-----------------

O(k)

The heap never stores more than k elements.

*/