class Solution {
private:
    vector<int> v;
    void validIndex(vector<int>& valid, int& target) {
        int n = v.size();
        for(int i = 0; i < n; i++) {
            if(v[i] == target) valid.push_back(i);
        }
    }

public:
    Solution(vector<int>& nums) {
        v = nums;
    }
    
    int pick(int target) {
        vector<int> valid;
        validIndex(valid, target);
        return valid[rand() % valid.size()];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */