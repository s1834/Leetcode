class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size(), count = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == val) {
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