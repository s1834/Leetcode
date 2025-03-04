class Solution {
    public:
        bool checkPowersOfThree(int n) {
            int power = 0, temp = n;
            while(temp >= 3) {
                temp /=3;
                power++;
            }
            temp = pow(3, power);
            while(power >= 0) {
                power--;
                if(temp + pow(3, power) == n) return true;
                else if(temp + pow(3, power) < n) temp += pow(3, power);
            }
            return false;
        }
    };