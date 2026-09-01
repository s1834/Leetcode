class Solution {
    public:
        int elevatorRequests(int n, vector<int>& requests) {
            int time = 0, start = 0;
            for(auto &x :requests) {
                time += abs(start - x);
                start = x;
            }
            return time;
        }
    };