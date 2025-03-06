class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vector<pair<int, int>> project;
        int n = profits.size();
        for (int i = 0; i < n; i++) {
            project.push_back(make_pair(capital[i], profits[i]));
        }
        sort(project.begin(), project.end());

        priority_queue<int> pq;
        int ind = 0;
        while(k--) {
            while(ind < n && project[ind].first <= w) {
                pq.push(project[ind].second);
                ind++;
            }
            if(pq.empty()) {
                break;
            } 
            w += pq.top();
            pq.pop();
        }
        return w;
    }
};