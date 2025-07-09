class Solution {
public:
    int findMin(vector<int>& nums) {
        int ans = nums[0], l = 0, r = nums.size() - 1, m;
        while(l < r && nums[l] == nums[r]) r--;
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
// 153. Find Minimum In Rotated Sorted Array 
[3, 4, 5, 1, 2]
 l     m     r
 since nums[m] >= nums[l]:
    right search
 else:
    left search
[3, 4, 5, 1, 2]
 l     m     r
 since nums[m] >= nums[l]:
    right search
 else:
    left search

[3, 4, 5, 1, 2]
 l        m  r
 lets say for some case 1 was middle, thats why we checked the min after calculating result also, so that we can return the minimum element in case if middle is smallest

// 154. Find Minimum In Rotated Sorted Array II
[10, 1, 10, 10]
here we need to handle duplicates, so we will first check if the left and right elements are equal, if they are then we can safely decrement the right pointer
so we will do that until we find a different element
[10, 1, 10, 10]
 l   r
 then we perform teh same logic as above

 if in any other testcase there were muliple duplicates in the middle too, we handle them normally with the min logic as we already now have different left and right elements so it can easily help us handle that case
 [10,11,11,1,1,2,2,10,10,10]
 
*/