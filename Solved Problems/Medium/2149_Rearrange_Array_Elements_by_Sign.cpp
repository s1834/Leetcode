class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> pos, neg;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if(nums[i] < 0) {
                neg.push_back(nums[i]);
            } else {
                pos.push_back(nums[i]);
            }
        }

        int flag = 0, ind = 0;
        for (int i = 0; i < n; i++) {
            if (flag) {
                nums[i] = neg[ind];
                flag = 0;
                ind++;
            } else {
                nums[i] = pos[ind];
                flag = 1;
            }
        }
        return nums;
    }
};