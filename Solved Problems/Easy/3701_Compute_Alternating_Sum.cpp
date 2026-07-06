class Solution {
    public:
        int alternatingSum(vector<int>& nums) {
            int ans = 0, flag = 1;
            for(int x : nums) {
                if(flag) {
                    ans += x;
                    flag = 0;
                } else {
                    ans -= x;
                    flag = 1;
                }
            }
            return ans;
        }
    };