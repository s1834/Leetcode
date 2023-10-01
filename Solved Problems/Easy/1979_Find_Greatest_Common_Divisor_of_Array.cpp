class Solution {
public:
    int findGCD(vector<int>& nums) {
        int n = nums.size(), max = 0, min = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (max < nums[i]) {
                max = nums[i];
            }
            if (min > nums[i]) {
                min = nums[i];
            }
        }

        int gcd = 1;
        for (int i = 2; i < min + 1; i++) {
            if (max % i == 0 && min % i == 0) {
                gcd = i;
            }
        }

        return gcd;
    }
};