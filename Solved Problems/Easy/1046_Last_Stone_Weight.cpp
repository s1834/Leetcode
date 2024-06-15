class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq;
        int n = stones.size();
        for(int i = 0; i < n; i++) {
            pq.push(stones[i]);
        }

        while(pq.size() > 1) {
            int x, y;
            y = pq.top();
            pq.pop();
            x = pq.top();
            pq.pop();
            if(x != y) {
                pq.push(y - x);
            }
        }

        if(pq.size()) {
            return pq.top();
        }
        return 0;
    }
};