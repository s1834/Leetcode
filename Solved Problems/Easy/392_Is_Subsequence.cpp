class Solution {
public:
    bool isSubsequence(string s, string t) {
        stack<char> st1, st2;
        int n1 = t.size();
        for (int i = 0; i < n1; i++) {
          st1.push(t[i]);
        }
        int n2 = s.size();
        for (int i = 0; i < n2; i++) {
          st2.push(s[i]);
        }

        while (!st1.empty() && !st2.empty()) {
          if (st1.top() == st2.top()) {
            st1.pop();
            st2.pop();
          } else {
            st1.pop();
          }
        }

        if (st2.empty()) {
          return true;
        }

        return false;
    }
};