class Solution {
public:
    string reverseWords(string s) {
        stack<string> st;
        int n = s.size(), spaces = 0, flag = 0;
        string temp = "";
        for (int i = 0; i < n; i++) {
            if (s[i] != ' ') {
                temp += s[i];
                flag = 1;
            } else {
                if (flag && temp != "") {
                    st.push(temp);
                    st.push(" ");
                    temp = "";
                }
            }
        }

        if (flag) {
            st.push(temp);
            temp = "";
        }
        
        if (st.top() == "") {
            st.pop();
            st.pop();
        }

        while (!st.empty()) {
            temp += st.top();
            st.pop();
        }

        return temp;
    }
};