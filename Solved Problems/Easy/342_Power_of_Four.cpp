class Solution {
public:
    bool isPowerOfFour(int n) {
        if (n == 1) {
            return true;
        }

        while (n >= 4) {
            if (n == 4) {
                return true;
            }

            if (n % 4 != 0) {
                return false;
            }
            n /= 4;
        }
        return false;
    }
};