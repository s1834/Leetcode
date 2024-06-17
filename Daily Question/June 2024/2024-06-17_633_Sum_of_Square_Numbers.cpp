class Solution {
public:
    bool check(long long start, long long end, int c) {
        if(start > end) {
            return false;
        }

        long long int a = start * start, b = end * end;
        if(a + b == c) {
            return true;
        }

        if(a + b > c) {
            return check(start, end - 1, c);
        } else {
            return check(start + 1, end, c);
        }

        return false;
    }

    bool judgeSquareSum(int c) {
        long long start = 0, end = round(sqrt(c));
        cout << end;
        return check(start, end, c);

    }
};