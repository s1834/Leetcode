class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> vect;
        int size = nums.size(), count = 1, miss = 0, flag = 2;

        for (int i = 1; i < size; i++) {
            if (!flag) {
                break;
            }
            if (nums[i - 1] != i) {
                miss = i;
                flag--;
            }
            count++;
            if (nums[i] != nums[i - 1] || i == size - 1) {
                if (count > 2 || (size == 2 && count == 2)) {
                    vect.push_back(nums[i - 1]);
                    flag--;
                }
                count = 1;
            }
        }
        if (flag) {
            miss = nums[size - 1] + 1;
        }
        vect.push_back(miss);
        return vect;
    }
};