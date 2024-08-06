class Solution {
public:
    int minimumPushes(string word) {
        map<char, int> mp;
        for (auto x : word) mp[x]++;
        vector<int> v;
        for(auto x : mp) v.push_back(x.second);
        sort(v.begin(), v.end(), greater<int>());
        int mul = 1, n = v.size(), ans = 0;
        for(int i = 0; i < n; i++) {
            ans += v[i] * mul;
            if(!((i + 1) % 8)) mul++;
        }
        return ans;
    }
};