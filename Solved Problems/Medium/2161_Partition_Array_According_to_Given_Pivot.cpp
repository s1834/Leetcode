class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        // create three vector before, current , after and then push them accordingly
        vector<int> before, current, after;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] < pivot) {
                before.push_back(nums[i]);
            } else if (nums[i] > pivot) {
                after.push_back(nums[i]);
            } else {
                current.push_back(nums[i]);
            }
        }

        n = current.size();
        for (int i = 0; i < n; i++) {
            before.push_back(current[i]);
        }

        n = after.size();
        for (int i = 0; i < n; i++) {
            before.push_back(after[i]);
        }

        return before;
    }
};