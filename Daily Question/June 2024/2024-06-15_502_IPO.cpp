class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        map<int,int> mp;
        int n = profits.size();
        if (n <= k) {
            for (int i = 0; i < n; i++) {
                if (capital[i] <= w) {
                    w += profits[i];
                }
            }
            return w;
        }
        for(int i = 0; i < n; i++) {
            if(mp[capital[i]]) {
                if(mp[capital[i]] < profits[i]) {
                    mp[capital[i]] = profits[i];
                }
            } else {
                mp[capital[i]] = profits[i];
            }
        }

        vector<int> cap;
        for (auto x : mp) {
            cap.push_back(x.first);
        }

        while(k) {
            int maxW = 0, maxInd = 0;
            for(int i = 0; i < cap.size(); i++) {
                if (cap[i] > w) {
                    break;
                }

                if(mp[cap[i]] > maxW) {
                    maxW = mp[cap[i]];
                    maxInd = i; 
                }

                w += maxW;
                cap.erase(cap.begin() + maxInd);
                k--;
            }
        }

        return w;
    }
};