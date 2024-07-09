class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        int waitingTime = customers[0][0] + customers[0][1], n = customers.size();
        double averageWaitingTime = customers[0][1];
        for(int i = 1; i < n; i++) {
            waitingTime += customers[i][1];
            averageWaitingTime += customers[i][0] > waitingTime ? customers[i][1] : waitingTime - customers[i][0];
        }
        return averageWaitingTime / n; 
    }
};