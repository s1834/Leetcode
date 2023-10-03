class MinStack {
private: 
    vector<int> st;
    int n;
public:
    MinStack() {
        n = 0;
    }
    
    void push(int val) {
        st.push_back(val);
        n++;
    }
    
    void pop() {
        st.pop_back();
        n--;
    }
    
    int top() {
        return st[n - 1];
    }
    
    int getMin() {
        int mn = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (mn > st[i]) {
                mn = st[i];
            }
        }
        return mn;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */