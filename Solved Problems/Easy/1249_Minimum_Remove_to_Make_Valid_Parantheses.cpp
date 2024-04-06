class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<char> st;
        int n = s.size();
        string temp = "";
        for(int i = 0; i < n; i++) {
            if(s[i] == '(') {
                st.push('(');
                temp += '(';
            } else if (s[i] == ')') {
                if(st.empty()) {
                    continue;
                } else {
                    temp += ')';
                    st.pop();
                }
            } else {
                temp += s[i];
            }
        }

        string ans = "";
        if(!st.empty()) {
            for (int i = 0; i < n; i++) {
                if(st.empty()) {
                    break;
                }
                if(temp[i] == st.top()) {
                    st.pop();
                    continue;
                }
                ans += temp[i];
            }
        } else {
            ans = temp;
        }

        return ans;
    }
};