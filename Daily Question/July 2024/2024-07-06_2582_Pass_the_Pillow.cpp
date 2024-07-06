class Solution {
public:
    int passThePillow(int n, int time) {
        if(n > time) return time + 1;
        if((time / n) % 2 && time % n) return n - time / n - 1;
        if((time / n) % 2) return n - time / n;
        return time - n - 1;
    }
};