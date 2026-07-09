class FreqStack {
    private:
        int maxFreq = 0;
        unordered_map<int, int> freq;
        unordered_map<int, stack<int>> group;
    
    public:
        FreqStack() {
            
        }
        
        void push(int val) {
            freq[val]++;
            maxFreq = max(maxFreq, freq[val]);
            group[freq[val]].push(val);
        }
        
        int pop() {
            int ans = group[maxFreq].top();
            group[maxFreq].pop();
            freq[ans]--;
            if (group[maxFreq].empty()) maxFreq--;
            return ans;
        }
    };
    
    /**
     * Your FreqStack object will be instantiated and called as such:
     * FreqStack* obj = new FreqStack();
     * obj->push(val);
     * int param_2 = obj->pop();
     */