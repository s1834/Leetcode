class Solution {
    public:
        string removeOuterParentheses(string s) {
            deque<char> dq;
            string ans = "";
            int balance = 0;
            int n = s.size();
            for(int i = 0; i < n; i++) {
                if(s[i] == '('){
                    dq.push_back('(');
                    balance++;
                }
                else {
                    dq.push_back(')');
                    balance--;
                    if (balance == 0) {
                        dq.pop_front();
                        dq.pop_back();
                        while(!dq.empty()) {
                            ans += dq.front();
                            dq.pop_front();
                        }
                    }
                }
            }
            
            return ans;
        }
    };