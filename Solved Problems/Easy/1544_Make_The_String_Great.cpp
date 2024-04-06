class Solution {
public:
    string makeGood(string s) {
        stack<int> st;
        int n = s.size();
        st.push(s[0]);
        for(int i = 1; i < n; i++) {
            if(!st.empty() && (s[i] == st.top() + 32 || s[i] == st.top() - 32)) {
                st.pop();
            } else {
                st.push(s[i]);
            }
        }

        string ans = "";
        while(!st.empty()) {
            ans += st.top();
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};