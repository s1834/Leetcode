class Solution {
    public:
        long long sumAndMultiply(int n) {
            int x = 0, sum = 0, mul = 1;
            while(n) {
                int temp = n % 10;
                if(temp > 0) {
                    sum += temp;
                    x += temp * mul;
                    mul *= 10;
                }
                n /= 10;
            }
            return (long long) x * sum;
        }
    };

/*
Approach:
1. Traverse the digits of n from right to left.
2. Ignore all zero digits.
3. Reconstruct the number containing only non-zero digits
   while preserving their original order.
4. Simultaneously compute the sum of the non-zero digits.
5. Return the reconstructed number multiplied by the digit sum.

Time Complexity: O(d), where d is the number of digits in n.
Space Complexity: O(1).
*/