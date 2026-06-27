class Solution {
private:
    long long int checkSquare(long long int x, map<int, int>& mp) {
        if(!mp[x] || x > 1e9) return 0;
        if(mp[x] == 1) return 1;
        return 2 + checkSquare(x * x, mp);
    }

public:
    int maximumLength(vector<int>& nums) {
        map<int, int> mp;
        for(auto x : nums) mp[x]++;

        int mx = 1;
        for (auto x : mp) {
            int temp = x.first == 1 ? x.second : checkSquare(x.first, mp);
            mx = mx > temp ? mx : temp;
        }

        return mx % 2 ? mx : mx - 1;
    }
};

/*

Idea:
------
A valid sequence has the form:

x, x^2, x^4, ..., peak, ..., x^4, x^2, x

Every intermediate value must appear at least twice
(one copy on the left and one on the right), while the
last/peak value only needs one occurrence.

Algorithm:
----------
1. Count the frequency of every number using a map.
2. For every unique number, try to build the longest chain
   using checkSquare().

checkSquare(x):
---------------
- If x doesn't exist (or exceeds 1e9), return 0.
- If x appears exactly once, it must be the last element,
  so return 1.
- Otherwise, use two copies of x and continue with x*x:
      return 2 + checkSquare(x*x)

Special Case:
-------------
1 is handled separately because:
    1^2 = 1
which would cause infinite recursion.
Hence, its maximum chain length is simply its frequency.

Finally:
--------
Keep the maximum chain length among all starting numbers.
The answer must always be odd (symmetric sequence), so if
the maximum is even, return mx - 1.

Time Complexity:
----------------
Building frequency map : O(n log n)
Each recursive chain   : O(log log 1e9) ≈ constant
Overall                : O(n log n)

Space Complexity:
-----------------
O(n)

*/