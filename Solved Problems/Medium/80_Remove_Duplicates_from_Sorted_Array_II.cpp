class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size(), count = 1, dub = 0;
        if (n == 1) {
            return 1;
        }
        for (int i = 1; i < n; i++) {
            if (nums[i] != nums[i - 1]) {
                nums[count] = nums[i];
                count++;
                dub = 0;
            } else {
                dub++;
                if(dub < 2) {
                    nums[count] = nums[i];
                    count++;
                }
            }
        }
        
        return count;
    }
};