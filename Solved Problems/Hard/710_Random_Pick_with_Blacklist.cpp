class Solution {
private:
    vector<int> v;

public:
    Solution(int n, vector<int>& blacklist) {
        sort(blacklist.begin(), blacklist.end());
        int ind = 0, siz = blacklist.size();
        for(int i = 0; i < n; i++) {
            if(!siz || (ind < siz && i != blacklist[ind])) v.push_back(i);
            else if (ind >= siz) v.push_back(i);
            else ind++;
        }    
    }
    
    int pick() {
        return v[rand() % v.size()];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */