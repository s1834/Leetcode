class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) {
            return 1;
        }
        if (n == INT_MIN) {
            x = 1 / x;
            n = INT_MAX;
        } 
        if(n < 0) {
            x = 1 / x;
            n = -n;
        }
        double halfPow = myPow(x, n / 2);

        if(n % 2) {
            return x * halfPow * halfPow;
        } else {
            return halfPow * halfPow;
        }
    }
};