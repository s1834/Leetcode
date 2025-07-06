class FindSumPairs {
private:
    map<int, int> mp1, mp2;
    vector<int> nums;

public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        for(auto x : nums1) mp1[x]++;
        for(auto x : nums2) mp2[x]++;
        nums = nums2;
    }
    
    void add(int index, int val) {
        mp2[nums[index]]--;
        nums[index] += val;
        mp2[nums[index]]++;
    }
    
    int count(int tot) {
        int count = 0;
        for(auto x : mp1) if(mp2[tot - x.first]) count += x.second * mp2[tot - x.first];
        return count;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */

/*
FindSumPairs():
    1) We create two maps, mp1 and mp2, to store the frequency of elements in nums1 and nums2 respectively.
    2) The constructor initializes these maps and stores nums2 in a vector for later use.

Add():
    1) We decrement the count of the element at the given index in mp2.
    2) We update the value at that index in nums2.
    3) We increment the count of the new value in mp2.

Count():
    1) We iterate through mp1 and for each key, we check if the complement (tot - key) exists in mp2.
    2) If it does, we multiply the frequency of the key in mp1 with the frequency of the complement in mp2 and add it to the count.
    3) Finally, we return the total count of pairs that sum up to the given total.
*/