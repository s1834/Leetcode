class Solution {
public:
    int maxVowels(string s, int k) {
        int n = s.size(), count = 0, mx = 0;
        for (int i = 0; i < n - k + 1; i++) {
            for(int j = i; j < i + k; j++) {
                if(s[j] == 'a' || s[j] == 'e' || s[j] == 'i' || s[j] == 'o' || s[j] == 'u') {
                    count++;
                }
            }
            if(count > mx) {
                mx = count;
            }
            count = 0;
        }

        return mx;
    }
};