class CountIntervals {
private:
    map<int, int> mp;

public:
    CountIntervals() {}

    void add(int left, int right) {
        for (int i = left; i <= right; i++) mp[i] = 1;
    }

    int count() {
        return mp.size();
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */