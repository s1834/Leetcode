class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        long long int missing = 1;
        int patches = 0, ind = 0;
        while (missing <= n) {
            if (ind < nums.size() && nums[ind] <= missing) {
                missing += nums[ind];
                ind++;
            } else {
                missing += missing;
                patches++;
            }
        }

        return patches;
    }
};