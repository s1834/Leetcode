class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) {
            return 1;
        }
        if(n < 0) {
            return x * myPow(1 / x, abs(n - 1));
        }
        return x * myPow(x, n - 1);
    }
};