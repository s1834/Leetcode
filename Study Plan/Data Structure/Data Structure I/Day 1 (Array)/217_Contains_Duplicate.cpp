class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int size = nums.size(), count = 1;
        for (int i = 1; i < size; i++) {
            if (nums[i] != nums[i-1]) {
                if (count > 1) {
                    return true;
                }
                count = 0;
            }
            count++;
        }

        if (count > 1) {
            return true;
        }
        return false;   
    }
};