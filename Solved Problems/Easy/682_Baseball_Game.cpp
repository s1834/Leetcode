class Solution {
public:
    int calPoints(vector<string>& operations) {
        stack<int> st;
        int n = operations.size();
        for (int i = 0; i < n; i++) {
            if(operations[i] == "+") {
                int temp1 = st.top();
                st.pop();
                int temp2 = st.top();
                st.push(temp1);
                st.push(temp1 + temp2);
            } else if(operations[i] == "D") {
                int temp = st.top() * 2;
                st.push(temp);
            } else if (operations[i] == "C") st.pop();
            else st.push(stoi(operations[i]));
        }
        int sum = 0;
        while(!st.empty()) {
            sum += st.top();
            st.pop();
        }
        return sum;
    }
};