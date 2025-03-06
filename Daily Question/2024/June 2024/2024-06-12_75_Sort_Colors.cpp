class Solution {
public:
    void sortColors(vector<int>& nums) {
        vector<int> v(3, 0);
        int n = nums.size();
        for(int i = 0; i < n; i++) { 
            v[nums[i]]++;
        }

        int ind = 0;
        while(v[0]--) {
            nums[ind++] = 0;
        }
        while(v[1]--) {
            nums[ind++] = 1;
        }
        while(v[2]--) {
            nums[ind++] = 2;
        }
    }
};