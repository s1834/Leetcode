class Solution {
public:
    string reverseParentheses(string s) {
        stack<vector<char>> st;
        vector<char> v;
        for (auto c : s) {
            if(c == '(') {
                st.push(v);
                v.clear();
            } else if (c == ')') {
                reverse(v.begin(), v.end());
                vector<char> top = st.top();
                st.pop();
                top.insert(top.end(), v.begin(), v.end());
                v = top;
                for(auto x : v) cout << x << " ";
                cout << endl;
            } else v.push_back(c);
        }
        return string(v.begin(), v.end());;
    }
};