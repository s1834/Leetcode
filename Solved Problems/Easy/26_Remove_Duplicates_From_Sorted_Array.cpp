class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size(), count = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == nums[i + 1]) {
                nums.erase(nums.begin() + i);
                nums.push_back('_');
                i--;
                n--;
            } else {
                count++;
            }
        }
        return count;
    }
};