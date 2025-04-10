class Solution {
    public:
        int lastRemaining(int n) {
            int head = 1, step = 1, left = 1;
            while(n > 1) {
                if(left || n % 2) head += step;
                step *= 2;
                n /= 2;
                left = !left;
            }
            return head;
        }
    };