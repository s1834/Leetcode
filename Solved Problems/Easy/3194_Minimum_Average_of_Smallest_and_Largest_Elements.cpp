class Solution {
    public:
        double minimumAverage(vector<int>& nums) {
            sort(nums.begin(), nums.end());
            int high = nums.size() - 1, low = 0;
            vector<double> averages;
            while(low < high) {
                averages.push_back((nums[low] + nums[high]) * 1.0 / 2);
                low++;
                high--;
            }
            return *min_element(averages.begin(), averages.end());
        }
    };