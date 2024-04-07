class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size(), max = INT_MIN, amount = 0;;
        for(int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                amount = (j - i) * (height[i] < height[j] ? height[i] : height[j]);
                if(amount > max) {
                    max = amount;
                }
            }
        }
        return max;
    }
};