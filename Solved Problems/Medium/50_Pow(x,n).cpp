class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) {
            return 1;
        }
        double halfPow = myPow(x, n / 2);

        if(n % 2) {
            return n < 0 ? 1/x * halfPow * halfPow : x * halfPow * halfPow;
        } else {
            return halfPow * halfPow;
        }
    }
};