class Solution {
public:
    int maximumGain(string s, int x, int y) {
        stack<char> st;
        string more = "ab", less = "ba";
        int ans = 0;

        if(y > x) {
            more = "ba";
            less = "ab";
            swap(x, y);
        }
        
        for(char c : s) {
            if(!st.empty() && c == more[1] && st.top() == more[0]) {
                ans += x;
                st.pop();
            } else {
                st.push(c);
            }
        }
        
        stack<char> st1;
        while(!st.empty()) {
            if(!st1.empty() && st.top() == less[1] && st1.top() == less[0]) {
                ans += y;
                st1.pop();
            } else {
                if(st1.empty()) {
                    st1.push(st.top());
                    st.pop();
                    if(st1.top() == less[1] && st.top() == less[0]) {
                        ans += y;
                        st1.pop();
                    }
                }
                st1.push(st.top());
            }
            cout << st1.top();
            st.pop();
        }

        return ans;
    }
};