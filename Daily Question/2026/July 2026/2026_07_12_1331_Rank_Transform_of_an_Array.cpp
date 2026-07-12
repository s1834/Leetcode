class Solution {
    public:
        vector<int> arrayRankTransform(vector<int>& arr) {
            map<int, int> mp;
            for(auto x : arr) mp[x] = 1;
            
            int i = 1;
            for(auto &x : mp) {
                x.second = i;
                i++;
            }
    
            int n = arr.size();
            for(int i = 0; i < n; i++) arr[i] = mp[arr[i]];
    
            return arr;
        }
    };

/*

Idea:
------
Every distinct element should receive a unique rank based on
its sorted order.

Equal elements must have the same rank.

A map is useful because it automatically stores keys
(elements) in sorted order.

------------------------------------------------------------

Algorithm:
----------

Step 1:

Insert every element into the map.

Since a map stores only unique keys,

duplicate elements are inserted only once.

Example:

arr =

40 10 20 30 20 10

Map after insertion:

10
20
30
40

------------------------------------------------------------

Step 2:

Traverse the map in sorted order and assign ranks.

Since the map is already sorted,

the smallest element gets rank 1,
the second smallest gets rank 2,
and so on.

Example:

10 -> 1

20 -> 2

30 -> 3

40 -> 4

------------------------------------------------------------

Step 3:

Traverse the original array.

Replace every element with its assigned rank
using the map.

Example:

Original:

40 10 20 30

Map:

10 -> 1
20 -> 2
30 -> 3
40 -> 4

Result:

4 1 2 3

------------------------------------------------------------

Example:
--------

Input:

37 12 28 9 100 56 80 5 12

Unique sorted elements:

5
9
12
28
37
56
80
100

Assigned ranks:

5   -> 1
9   -> 2
12  -> 3
28  -> 4
37  -> 5
56  -> 6
80  -> 7
100 -> 8

Replace every element using the map:

37 12 28 9 100 56 80 5 12

↓

5 3 4 2 8 6 7 1 3

------------------------------------------------------------

Why use a map?
--------------

1. It automatically removes duplicates.

2. It stores elements in sorted order.

3. It allows O(log n) lookup while replacing
each element with its rank.

------------------------------------------------------------

Time Complexity:
----------------

Building the map:

O(n log n)

Assigning ranks:

O(n)

Replacing elements:

O(n log n)

Overall:

O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

The map stores every distinct element.

*/