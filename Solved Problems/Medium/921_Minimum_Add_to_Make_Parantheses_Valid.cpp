class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<char> st;
        int n = s.size(), count = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                st.push(s[i]);
            } else {
                if (!st.empty() && st.top() == '(') {
                    st.pop();
                } else {
                    st.push(s[i]);
                }
            }
        }

        while(!st.empty()) {
            st.pop();
            count++;
        }

        return count;
    }
};