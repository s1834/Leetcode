class Solution {
    private:
        int countDigits(int num) {
            int count = 0;
            while(num) {
                count++;
                num /= 10;
            }
            return count;
        }
    
    public:
        int findNumbers(vector<int>& nums) {
            int count = 0;
            for(auto &num : nums) {
                if(countDigits(num) % 2 == 0) count++;
            }
            
            return count;
        }
    };