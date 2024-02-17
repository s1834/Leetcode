class Solution {
public:
    string lastNonEmptyString(string s) {
        map<char,int> mp;
        int n = s.size();
        
        for (int i = 0; i < n; i++) {
            mp[s[i]]++;
        }
    
        int max = 0;
        for (auto i : mp) {
            if(i.second > max) {
                max = i.second;
            }
        }
        
        reverse(s.begin(), s.end());
        map<int, char> mp1;
        for (auto i : mp) {
            if(i.second == max) {
                mp1.insert({s.find(i.first), i.first});
            }
        }
        
        string ans = "";
        for(auto i : mp1) {
            ans += i.second;
        }
        reverse(ans.begin(), ans.end());
        
        return ans;
    }
};