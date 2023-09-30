class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        vector<int> vec;
        int n = nums.size(), count = 0, temp;
        for (int i = n; i > 0; i--) {
            temp = k;
            vec.push_back(nums[i - 1]);
            nums.pop_back();
            count++;
            sort(vec.begin(), vec.end(), greater<int>());
            for (int j = 0; j < vec.size(); j++) {
                if(vec[j] == temp) {
                    temp--;
                }
                if (!temp) {
                    return count;
                }
            }
        }
        return count;
    }
};