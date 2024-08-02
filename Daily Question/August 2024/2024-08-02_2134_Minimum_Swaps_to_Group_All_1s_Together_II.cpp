class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int ones = 0, n = nums.size();
        for(auto x : nums) {
            if(x) ones++;
        }

        int zeroes = 0;
        for(int i = 0; i < ones; i++) {
            if(!nums[i]) zeroes++;
        }

        int swaps = zeroes;
        for(int i = ones; i < n + ones; i++) {
            if(!nums[(i - ones) % n]) zeroes--;
            if(!nums[i % n]) zeroes++;
            swaps = min(swaps, zeroes);
        }
        return swaps;
    }
};