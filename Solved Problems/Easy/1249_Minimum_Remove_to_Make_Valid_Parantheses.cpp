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
        cout << temp;
        string ans = "";
        if(!st.empty()) {
            for (int i = n - 1; i >= 0; i--) {
                if(!st.empty() && temp[i] == st.top()) {
                    st.pop();
                } else {
                    if(temp[i]) {
                        ans += temp[i];
                    }
                }
            }
            reverse(ans.begin(), ans.end());
        } else {
            ans = temp;
        }

        return ans;
    }
};