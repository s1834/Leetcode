class Solution {
    public:
        int digitFrequencyScore(int n) {
            map<int, int> mp;
            while(n) {
                mp[n % 10]++;
                n /= 10;
            }
    
            int sum = 0;
            for(auto x : mp) sum += x.first * x.second;
            
            return sum;
        }
    };

    /*

Idea:
------
The digit frequency score is calculated by summing:

    digit × (frequency of that digit)

Approach:
---------
1. Traverse the digits of the number one by one using modulo (%) and
   division (/).
2. Store the frequency of each digit in a map.
3. Iterate through the map and compute:
      digit × frequency
4. Return the total score.

Example:
--------
n = 22153

Extract digits:

3, 5, 1, 2, 2

Frequency Map:

1 -> 1
2 -> 2
3 -> 1
5 -> 1

Score:

1 × 1 = 1
2 × 2 = 4
3 × 1 = 3
5 × 1 = 5

Total Score:

1 + 4 + 3 + 5 = 13

Time Complexity:
----------------
O(d)
where d is the number of digits in n.

Space Complexity:
-----------------
O(1)

Since there are only 10 possible digits (0–9), the map stores at most
10 entries.

*/