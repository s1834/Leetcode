class Solution {
    public:
        bool canAliceWin(vector<int>& nums) {
            int singleDigit = 0, doubleDigit = 0;
            for(auto &num : nums) {
                if(num < 10) singleDigit += num;
                else doubleDigit += num;
            }
    
            if(singleDigit == doubleDigit) return false;
            return true;
        }
    };