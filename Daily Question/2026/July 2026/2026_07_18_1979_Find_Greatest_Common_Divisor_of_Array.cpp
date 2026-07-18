class Solution {
    public:
        int findGCD(vector<int>& nums) {
            int largest = INT_MIN, smallest = INT_MAX;
            for(auto x : nums) {
                if(x > largest) largest = x;
                if(x < smallest) smallest = x;
            }
            return __gcd(largest, smallest);
        }
    };