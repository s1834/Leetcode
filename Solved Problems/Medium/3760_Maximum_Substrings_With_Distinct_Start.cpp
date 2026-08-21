class Solution {
    public:
        int maxDistinct(string s) {
            set<char> st;
            for(auto &x : s) st.insert(x);
            return st.size();
        }
    };