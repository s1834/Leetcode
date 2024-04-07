class Solution {
public:
    bool canBeValid(string s, string locked) {
        stack<int> st1, st2;
        int n = s.size();
        if(n < 2) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if(s[i] == '(') {
                st1.push(i);
            }

            if(locked[i] = '0') {
                st2.push(i);
            }

            if(s[i] == ')') {
                if(!st1.empty()) {
                    st1.pop();
                } else if (!st2.empty()) {
                    st2.pop();
                } else {
                    return false;
                }
            }
        }

        while(!st1.empty() && !st2.empty()) {
            if (st1.top() >= st2.top()) {
                return false;
            }
            st1.pop();
            st2.pop();
        }

        if(st1.empty()) {
            return true;
        }
        return false;
    }
};