class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        vector<int> leftSum, rightSum, rev = nums, answer;
        reverse(rev.begin(), rev.end());
        int n = nums.size();
        
        leftSum.push_back(0);
        rightSum.push_back(0);
        for (int i = 0; i < n - 1; i++) {
            leftSum.push_back(nums[i] + leftSum[i]);
            rightSum.push_back(rev[i] + rightSum[i]);
        }
        reverse(rightSum.begin(), rightSum.end());
        
        for (int i = 0; i < n; i++) {
            answer.push_back(abs(leftSum[i] - rightSum[i]));
        }
        
        return answer;
    }
};