class Solution {
    public:
        int minimumRecolors(string blocks, int k) {
            int n = blocks.size(), recolor, recolorMin = INT_MAX;
            for(int i = 0; i < n - k; i++) {
                recolor = 0;
                for(int j = i; j < i + k; j++) {
                    if(blocks[j] == 'W') recolor++;
                }
                if(recolorMin > recolor) recolorMin = recolor;
            }
            return recolorMin;
        }
    };