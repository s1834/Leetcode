class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<string> st;
        int n = tokens.size(), one, two, ans;
        if (n == 1) {
            return stoi(tokens[0]);
        }
        for (int i = 0; i < n; i++) {
            if (tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "*" && tokens[i] != "/") {
                st.push(tokens[i]);
            } else {
                one = stoi(st.top());
                st.pop();
                two = stoi(st.top());
                st.pop();
                if (tokens[i] == "+") {
                    ans = one + two;
                    st.push(to_string(ans));
                } else if (tokens[i] == "-") {
                    ans = two - one;
                    st.push(to_string(ans));
                } else if (tokens[i] == "*") {
                    ans = one * two;
                    st.push(to_string(ans));
                } else {
                    ans = two / one;
                    st.push(to_string(ans));
                }
            }
        }
        return ans;
    }
};