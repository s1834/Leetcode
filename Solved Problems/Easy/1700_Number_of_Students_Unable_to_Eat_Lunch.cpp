class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        stack<int> st;
        queue<int> q;
        reverse(sandwiches.begin(), sandwiches.end());
        int n = students.size();
        for (int i = 0; i < n; i++) {
            st.push(sandwiches[i]);
            q.push(students[i]);
        }

        int mark = 0;
        while(mark < n) {
            if(st.top() == q.front()) {
                st.pop();
                q.pop();
                mark = 0;
                n--;
            } else {
                q.push(q.front());
                q.pop();
                mark++;
            }
        }
        return n;
    }
};