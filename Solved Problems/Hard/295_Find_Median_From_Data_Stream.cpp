class MedianFinder {
    private:
        priority_queue<int> maxPQ;
        priority_queue<int, vector<int>, greater<int>> minPQ;
    public:
        MedianFinder() {
            
        }
        
        void addNum(int num) {
            if(maxPQ.empty() || num <= maxPQ.top()) maxPQ.push(num);
            else minPQ.push(num);
    
            if(maxPQ.size() > minPQ.size() + 1) {
                minPQ.push(maxPQ.top());
                maxPQ.pop();
            } else if(minPQ.size() > maxPQ.size() + 1) {
                maxPQ.push(minPQ.top());
                minPQ.pop();
            }
        }
        
        double findMedian() {
            // even
            if(minPQ.size() == maxPQ.size()) return ((minPQ.top() + maxPQ.top()) / 2.0);
    
            // odd
            if(maxPQ.size() > minPQ.size()) return maxPQ.top();
            else return minPQ.top();
        }
    };
    
    /**
     * Your MedianFinder object will be instantiated and called as such:
     * MedianFinder* obj = new MedianFinder();
     * obj->addNum(num);
     * double param_2 = obj->findMedian();
     */

/*

Idea:
------
Maintain the data stream using two heaps.

1.

Max Heap

Stores the smaller half of all numbers.

The largest element of the smaller half is always
available at the top.

------------------------------------------------------------

2.

Min Heap

Stores the larger half of all numbers.

The smallest element of the larger half is always
available at the top.

------------------------------------------------------------

Invariant:
----------

1.

The size difference between both heaps is at most 1.

2.

Every element in the Max Heap is less than or equal
to every element in the Min Heap.

These two conditions are maintained after every insertion.

------------------------------------------------------------

Algorithm:
----------

Adding a Number

1.

If the number is smaller than or equal to the largest
element of the smaller half (Max Heap),

insert it into the Max Heap.

Otherwise,

insert it into the Min Heap.

------------------------------------------------------------

2.

If one heap becomes larger than the other by more than
one element,

move the top element from the larger heap to the smaller
heap to restore balance.

------------------------------------------------------------

Finding the Median

If both heaps contain the same number of elements,

the median is the average of the two middle elements,
which are the tops of both heaps.

Otherwise,

the heap containing one extra element has the median
at its top.

------------------------------------------------------------

Example:
--------

Insert:

1

Max Heap:

1

Min Heap:

Median = 1

------------------------------------------------------------

Insert:

2

Max Heap:

1

Min Heap:

2

Median = (1 + 2) / 2 = 1.5

------------------------------------------------------------

Insert:

3

Max Heap:

1

Min Heap:

2 3

Median = 2

------------------------------------------------------------

Insert:

4

After insertion,

Max Heap:

1

Min Heap:

2 3 4

Min Heap becomes larger by 2 elements.

Move 2 to the Max Heap.

Max Heap:

2 1

Min Heap:

3 4

Median = (2 + 3) / 2 = 2.5

------------------------------------------------------------

Time Complexity:
----------------

addNum()

O(log n)

Insertion into a heap and possible rebalancing.

findMedian()

O(1)

Only the heap tops are accessed.

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

All inserted numbers are stored across the two heaps.

*/