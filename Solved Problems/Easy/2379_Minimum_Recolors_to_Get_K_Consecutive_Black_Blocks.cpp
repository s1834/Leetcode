class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int n = blocks.size(), count = 0, mn = 0;
        for (int i = 0; i < k; i++) {
            if(blocks[i] == 'W') {
                count++;
            }
        }
        mn = count;
        for(int i = k; i < n - k; i++) {
            if(blocks[i - k] == 'W') {
                count--;
            }
            if(blocks[i] == 'W') {
                count++;
            }
            mn = min(mn, count);
        }
        return mn;
    }
};