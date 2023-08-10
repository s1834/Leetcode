class Solution {
public:
    bool isPrime(int n) {
        for (int i = 2; i <= n / 2; i++) {
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }

    bool isUgly(int n) {
        if (n <= 0) {
            return false;
        }

        for (int i = 2; i <= n; i++) {
            if (n % i == 0 && (i != 2 && i != 3 && i != 5)) {
                if (isPrime(i)) {
                    return false;
                }
            }
        }

        return true;
    }
};