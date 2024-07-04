class RangeModule {
private:
    map<int, int> mp;

public:
    RangeModule() {}

    void addRange(int left, int right) {
        for (int i = left; i < right; i++) mp[i] = 1;
    }

    bool queryRange(int left, int right) {
        for (int i = left; i < right; i++) {
            if (!mp[i]) return false;
        }
        return true;
    }

    void removeRange(int left, int right) {
        for (int i = left; i < right; i++) mp[i] = 0;
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */