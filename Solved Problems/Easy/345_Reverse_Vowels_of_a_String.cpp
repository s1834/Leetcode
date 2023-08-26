class Solution {
public:
    string reverseVowels(string s) {
        int n = s.size();
        stack<int> st;
        string ans = "";
    
        for (int i = 0; i < n; i++) {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U') {
                st.push(s[i]);
                ans.push_back(' ');
            } else {
                ans.push_back(s[i]);
            }
        }

        for (int i = 0; i < n; i++) {
            if (ans[i] == ' ') {
                ans[i] = st.top();
                st.pop();
            }
        }

        return ans;
    }
};