class Solution {
    public:
        int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            int n = profits.size();
            for(int i = 0; i < n; i++) pq.push({capital[i], profits[i]});
            
            priority_queue<int> maxProfits;
            while(k--) {
                while(!pq.empty() && pq.top().first <= w) {
                    maxProfits.push(pq.top().second);
                    pq.pop();
                }
    
                if(maxProfits.empty()) return w;
    
                w += maxProfits.top();
                maxProfits.pop();
            }
    
            return w;
        }
    };

/*

Idea:
------
Use two Priority Queues.

1.

Capital Heap

Stores all projects sorted by the minimum capital
required to start them.

This helps determine which projects become available
as the current capital increases.

------------------------------------------------------------

2.

Profit Heap

Stores the profits of all currently affordable
projects.

Always choose the project with the maximum profit
to maximize the available capital for future projects.

------------------------------------------------------------

Algorithm:
----------

1.

Push every project into the Capital Heap as

(required capital, profit)

so projects are processed in increasing order of
required capital.

------------------------------------------------------------

2.

Repeat at most

k

times.

------------------------------------------------------------

3.

Move every project whose

required capital <= current capital

from the Capital Heap into the Profit Heap.

These are all the projects that can currently be
started.

------------------------------------------------------------

4.

If the Profit Heap is empty,

no affordable project is available.

Since the current capital can no longer increase,

return the current capital immediately.

------------------------------------------------------------

5.

Otherwise,

select the project with the maximum profit.

Increase the current capital by its profit.

Remove it from the Profit Heap.

------------------------------------------------------------

Example:
--------

k = 2

Initial Capital = 0

Capital:

[0, 1, 1]

Profit:

[1, 2, 3]

------------------------------------------------------------

Capital Heap

(0,1)

(1,2)

(1,3)

------------------------------------------------------------

Iteration 1

Affordable projects:

(0,1)

Profit Heap:

1

Choose profit:

1

Current Capital:

1

------------------------------------------------------------

Iteration 2

New affordable projects:

(1,2)

(1,3)

Profit Heap:

3

2

Choose profit:

3

Current Capital:

4

Answer:

4

------------------------------------------------------------

Time Complexity:
----------------

Building the Capital Heap:

O(n log n)

Each project is inserted and removed exactly once
from both heaps.

Overall:

O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

The two heaps together store at most n projects.

*/