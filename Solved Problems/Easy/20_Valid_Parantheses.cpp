class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if(s[i] == '(') {
                st.push('(');
            } else if(s[i] == '[') {
                st.push('[');
            } else if(s[i] == '{') {
                st.push('{');
            } else if(s[i] == ')') {
                if(st.top() == '(') {
                    st.pop();
                } else {
                    return false;
                }
            } else if(s[i] == ']') {
                if (st.top() == '[') {
                    st.pop();
                } else {
                    return false;
                }
            } else {
                if (st.top() == '{') {
                    st.pop();
                } else {
                    return false;
                }
            }
        }

        if (st.empty()) {
            return true;
        }
        return false;
    }
};