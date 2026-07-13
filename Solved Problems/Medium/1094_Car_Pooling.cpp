class Solution {
    public:
        bool carPooling(vector<vector<int>>& trips, int capacity) {
            priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> from;
            priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> to;
            
            for(auto x : trips) from.push({x[1], x[2], x[0]});
            
            while(!from.empty()) {
                auto [a, b, c] = from.top();
                from.pop();
    
                while(!to.empty()) {
                    auto [x, y] = to.top();
                    if(a >= x) {
                        capacity += y;
                        to.pop();
                    } else break;
                }
    
                to.push({b, c});
                capacity -= c;
                if(capacity < 0) return false; 
            }
    
            return true;
        }
    };

/*

Idea:
------
Use two Min Heaps.

1.

From Heap

Stores all trips sorted by their pickup location.

Each element stores

(pickup location, drop location, passengers)

This helps process trips in the order passengers
enter the car.

------------------------------------------------------------

2.

To Heap

Stores all ongoing trips sorted by their drop location.

Each element stores

(drop location, passengers)

This helps determine which passengers leave the
car before the next pickup.

------------------------------------------------------------

Algorithm:
----------

1.

Push every trip into the From Heap.

The heap automatically processes trips in increasing
pickup location.

------------------------------------------------------------

2.

For every trip,

before picking up new passengers,

remove every trip from the To Heap whose

drop location <= current pickup location.

These passengers have already left the car, so their
seats become available again.

Increase the remaining capacity accordingly.

------------------------------------------------------------

3.

Pick up the current passengers.

Decrease the available capacity.

Store this trip in the To Heap so its passengers can
be removed when their destination is reached.

------------------------------------------------------------

4.

If the available capacity ever becomes negative,

the car cannot accommodate all passengers.

Return false.

------------------------------------------------------------

Example:
--------

capacity = 4

Trips:

[2,1,5]

[3,3,7]

------------------------------------------------------------

From Heap

(1,5,2)

(3,7,3)

------------------------------------------------------------

Pickup at 1

Current passengers:

2

Remaining capacity:

2

To Heap:

(5,2)

------------------------------------------------------------

Pickup at 3

No passengers have reached their destination yet.

Current passengers:

2 + 3 = 5

Remaining capacity:

-1

Capacity becomes negative.

Return false.

------------------------------------------------------------

Time Complexity:
----------------

Building the From Heap:

O(n log n)

Each trip is inserted and removed exactly once
from both heaps.

Overall:

O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

Both heaps together store at most n trips.

*/