class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int cheap = prices[0], size = prices.size(), max = 0;

        for (int i = 0; i < size; i++) {
            if (max < prices[i] - cheap) {
                max = prices[i] - cheap;
            }

            if (prices[i] < cheap) {
                cheap = prices[i];
            }
        }

        return max;
    }
};