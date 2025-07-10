class Solution {
public:
    int search(vector<int>& nums, int target) {
        int  l = 0, r = nums.size() - 1, m;
        while(l <= r) {
            m = l + (r - l) / 2;
            if(nums[m] == target) return m;
            if(nums[l] <= nums[m]) {
                if(target > nums[m] || target < nums[l]) l = m + 1;
                else r = m - 1;
            } else {
                if(target < nums[m] || target > nums[r]) r = m - 1;
                else l = m + 1;
            }
        }
        return -1;
    }
};

/*
1) The function searches for a target value in a rotated sorted array.
2) It uses a modified binary search algorithm to find the target efficiently.
    a) The algorithm checks the middle element and determines whether we are in the left or right sorted half of the array.
    b) if nums[l] <= nums[m], it means the left half is sorted.
        i) If the target is in the left half (between nums[l] and nums[m]), it narrows down the search space to that half.
        ii) If the target is not in the left half, it narrows down the search space to the right half.
    c) If nums[l] > nums[m], it means the right half is sorted.
        i) If the target is in the right half (between nums[m] and nums[r]), it narrows down the search space to that half.
        ii) If the target is not in the right half, it narrows down the search space to the left half.
3) The search continues until the target is found or the search space is exhausted.
4) If the target is found, it returns the index of the target; otherwise, it  returns -1.

[4, 5, 6, 7, 0, 1, 2]

The time complexity of this algorithm is O(log n), where n is the number of elements in the array.
*/