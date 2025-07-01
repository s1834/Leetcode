class Solution {
public:
    string minWindow(string s, string t) {
        map<char, int> mp1, mp2;
        for (auto x : t) mp1[x]++;
        
        int n = s.size(), l = 0, r = 0, mn = INT_MAX, minL = 0, minR = 0;
        while(r < n) {
            if(mp1[s[r]]) mp2[s[r]]++;

            while(l <= r && !mp1[s[l]] || mp2[s[l]] > mp1[s[l]]) {
                if(mp1[s[l]]) mp2[s[l]]--;
                l++;
            }
            
            if(r - l + 1 >= t.size() && r - l + 1 < mn) {
                int temp = 1;
                for(auto x : mp1) if(x.second != mp2[x.first]) temp = 0;
                if(temp) {
                    mn = r - l + 1;
                    minL = l;
                    minR = r;
                }
            }
            r++;
        }

        for(auto x : mp1) if(x.second > mp2[x.first]) return "";
    
        string ans = "";
        if(r - l + 1 >= t.size() && r - l + 1 < mn) {
                minL = l;
                minR = r - 1;
            }
        for(int i = minL; i <= minR; i++) ans += s[i];
        return ans;
    }
};