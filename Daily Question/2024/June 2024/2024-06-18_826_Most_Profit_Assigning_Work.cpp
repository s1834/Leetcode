class Solution {
public:
    int maxProfit(vector<pair<int, int>> v, int worker, int l, int r) {
        if (l > r) {
            return 0;
        }
        int mid = (l + r) / 2;
        if (v[mid].second <= worker) {
            return max(v[mid].first, maxProfit(v, worker, l, mid - 1));
        } else {
            return maxProfit(v, worker, mid + 1, r);
        }
    }

    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit,
                            vector<int>& worker) {
        vector<pair<int, int>> v;
        int n = difficulty.size();
        for (int i = 0; i < n; i++) {
            v.push_back(make_pair(profit[i], difficulty[i]));
        }

        sort(v.begin(), v.end(), greater<pair<int, int>>());
        for (int i = 0; i < n - 1; i++) {
            v[i + 1].second = min(v[i].second, v[i + 1].second);
        }
        int netProfit = 0, l = 0, r = n - 1;
        n = worker.size();
        for (int i = 0; i < n; i++) {
            netProfit += maxProfit(v, worker[i], l, r);
        }

        return netProfit;
    }
};