class Solution {
public:
    int findMin(vector<int>& nums) {
        int ans = nums[0], l = 0, r = nums.size() - 1, m;
        while(l <= r) {
            if(nums[l] < nums[r]) {
                ans = min(ans, nums[l]);
                break;
            }
            
            m = l + (r - l) / 2;
            ans = min(ans, nums[m]);
            if(nums[m] >= nums[l]) l = m + 1;
            else r = m - 1;
        }
        return ans;
    }
};

/*
[3, 4, 5, 1, 2]
 l     m     r
 since nums[m] >= nums[l]:
    right search
 else:
    left search

[3, 4, 5, 1, 2]
 l        m  r
 lets say for some case 1 was middle, thats why we checked the min after calculating result also, so that we can return the minimum element in case if middle is smallest
*/