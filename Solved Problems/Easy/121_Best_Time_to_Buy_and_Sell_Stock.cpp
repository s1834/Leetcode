class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max = 0, count = 0, size = prices.size(), temp;
        while (count != size - 1) {
            for (int i = count + 1; i < size; i++) {
                temp = prices[i] - prices[count];
                if (temp > max) {
                    max = temp;
                }
            }
            count++;
        }

        return max;
    }
};