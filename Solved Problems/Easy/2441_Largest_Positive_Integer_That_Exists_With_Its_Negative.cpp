class Solution {
public:
    bool found(vector<int>& nums, int pos, int neg) {
        int n = nums.size();
        bool positive = false, negative = false;
        for(int i = 0; i < n; i++) {
            if(!positive && nums[i] == pos) {
                positive = true;
            } else if (!negative && nums[i] == neg) {
                negative = true;
            }
        }
        return positive && negative;
    }

    int findMaxK(vector<int>& nums) {
        map<int, int> mp;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            mp[abs(nums[i])]++;
        }

        int max = -1;
        for(auto x : mp) {
            if(x.second > 1 && x.first > max) {
                if(found(nums, x.first, x.first - x.first - x.first)) {
                    max = x.first;
                }
            }
        }

        return max;
    }
};