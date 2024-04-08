class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int n = tickets.size(), time = 0;
        if(tickets[k] == 1) {
            return k;
        }
        for(int i = 0; i < n; i++) {
            if(i != k) {
                time += tickets[i] < tickets[k] ? tickets[i] : tickets[k];
            }
        }

        return time + tickets[k];
    }
};