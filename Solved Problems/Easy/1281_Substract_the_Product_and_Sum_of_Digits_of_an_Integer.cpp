class Solution {
public:
    int subtractProductAndSum(int n) {
        int sum = 0, pro = 1, temp;
        while (n) {
            temp = n % 10;
            sum += temp;
            pro *= temp;
            n /= 10;
        }

        return pro - sum;
    }
};