class Solution {
    public:
        int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
            int i = 0, j = 0, n = players.size(), m = trainers.size(), count = 0;
            while(i < n && j < m) {
                if(players[i] <= trainers[j]) {
                    count++;
                    i++;
                    j++;
                } else j++;
            }
            return count;
        }
    };