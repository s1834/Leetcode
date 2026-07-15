class Solution {
    public:
        int gcdOfOddEvenSums(int n) {
            int sumOdd = 0, sumEven = 0, i = 1, temp = n;
            while(temp--) {
                sumOdd += i;
                i += 2;
            }
    
            temp = n;
            i = 2;
            while(temp--) {
                sumEven += i;
                i += 2;
            }
    
            return __gcd(sumOdd, sumEven);
        }
    };