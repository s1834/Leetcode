class Solution {
public:
    int smallestEvenMultiple(int n) {
        int flag = 1, ans = n, mul = 2;
        while (flag) {
            if (ans % 2 == 0 && ans % n == 0) {
                break;
            }
            ans = n * mul;
            mul++;
        }

        return ans;
    }
};