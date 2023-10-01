class Solution {
public:
    int countTriples(int n) {
        if (n < 5) {
            return 0;
        }

        int count = 0;
        for (int i = 1; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n + 1; k++) {
                    if (i * i + j * j == k * k) {
                        count++;
                    }
                }
            }
        }
        return count * 2;
    }
};