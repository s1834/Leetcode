class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        int waitingTime = customers[0][0] + customers[0][1], n = customers.size();
        double averageWaitingTime = customers[0][1];
        for(int i = 1; i < n; i++) {
           if(waitingTime > customers[i][0]) {
                waitingTime += customers[i][1];
                averageWaitingTime += waitingTime - customers[i][0];
            } else {
                waitingTime = customers[i][0] + customers[i][1];
                averageWaitingTime += customers[i][1];
            }
        }
        return averageWaitingTime / n; 
    }
};