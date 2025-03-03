class Solution {
    public:
        vector<int> pivotArray(vector<int>& nums, int pivot) {
            vector<int> before, after, middle;
            for(auto num : nums) {
                if(num < pivot) before.push_back(num);
                else if(num > pivot) after.push_back(num);
                else middle.push_back(num);
            }
            before.insert(before.end(), middle.begin(), middle.end());
            if(after.size()) before.insert(before.end(), after.begin(), after.end());
            return before;
        }
    };