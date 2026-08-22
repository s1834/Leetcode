class Solution {
    public:
        bool checkDivisibility(int n) {
            long long sum = 0, mul = 1;
            int temp = n;
            while(temp) {
                sum += temp % 10;
                mul *= temp % 10;
                temp /= 10;
            }
    
            if(n % (sum + mul)) return false;
            return true;
        }
    };