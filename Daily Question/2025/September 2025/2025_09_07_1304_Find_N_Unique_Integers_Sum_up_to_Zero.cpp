class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> v;
        if(n % 2) {
            v.push_back(0);
            n--;
        }
        n /= 2;
        for(int i = 1; i <= n; i++) {
            v.push_back(i);
            v.push_back(-i);
        }
        return v;
    }
};

/*
1) The sumZero function generates a list of n unique integers that sum up to zero.
2) If n is odd, it includes 0 in the list and reduces n by 1.
3) It then adds pairs of positive and negative integers (i and -i) to the list until it reaches the desired count of n integers.
4) Finally, it returns the list of integers.
*/