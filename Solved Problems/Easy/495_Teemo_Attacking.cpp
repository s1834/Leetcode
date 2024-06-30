class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int n = timeSeries.size();
        vector<int> poisoned(timeSeries[n - 1] + duration , 0);
        for(int i = 0; i < n; i++) {
            for(int j = timeSeries[i]; j < timeSeries[i] + duration; j++) {
                if(!poisoned[j]) poisoned[j] = 1;
            }
        }

        int count = 0;
        n = poisoned.size();
        for(int i = 1; i < n; i++) {
            if(poisoned[i]) count++;
        }
        return count;
    }
};