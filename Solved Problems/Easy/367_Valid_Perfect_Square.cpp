class Solution {
public:
    bool square(int num, long long int l, long long int r) {
        if(l > r) {
            return false;
        }
        
        long long int x = (l + r) / 2;
        if(x * x == num) {
            return true;
        }
        if(x * x < num) {
            return square(num, l + 1, r);
        } else {
            return square(num, l, r - 1);
        }
    }

    bool isPerfectSquare(int num) {
        return square(num, 1, num);
    }
};