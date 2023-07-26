class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int> vec;
        int n = nums.size(), count;

        for (int i = 0; i < n; i++) {
            count = 0;
            for (int j = 0; j < n; j++) {
                if (j != i && nums[j] < nums[i]) {
                    count++;
                }
            }
            vec.push_back(count);
        }

        return vec;
    }
};