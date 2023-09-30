class Solution {
public:
    bool isPerfectSquare(int num) {
        int n = num / 2, temp;
        for (int i = 1; i < n; i++) {
            temp = i * i;
            if (temp == num) {
                return true;
            }
            if (temp > num) {
                return false;
            }
        }
        return false;
    }
};