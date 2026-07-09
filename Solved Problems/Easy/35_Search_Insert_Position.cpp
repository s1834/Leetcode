class Solution {
    private:
        int binarySearch(vector<int>& nums, int target, int left, int right) {
            if(left > right) return left;
    
            int mid = left + (right - left) / 2;
            if(nums[mid] == target) return mid;
            else if (nums[mid] < target) return binarySearch(nums, target, mid + 1, right);
            else return binarySearch(nums, target, left, mid - 1);
        }
    
    public:
        int searchInsert(vector<int>& nums, int target) {
            return binarySearch(nums, target, 0, nums.size() - 1);
        }
    };