class Solution {
public:
    vector<int> ans = {-1, -1};

    vector<int> findSum(vector<int>& nums, int target, int left, int right) {
        if(left >= right) {
            return ans;
        }
        cout<< nums[left] << " " << nums[right] << endl;
        if(nums[left] + nums[right] == target) {
            ans[0] = left + 1;
            ans[1] = right + 1;
            return ans;
        } else if(nums[left] + nums[right] > target) {
            findSum(nums, target, left, right - 1);
        } else {
            findSum(nums, target, left + 1, right);
        }
        return ans;
    }

    vector<int> twoSum(vector<int>& numbers, int target) { 
        return findSum(numbers, target, 0, numbers.size() - 1);
    }
};