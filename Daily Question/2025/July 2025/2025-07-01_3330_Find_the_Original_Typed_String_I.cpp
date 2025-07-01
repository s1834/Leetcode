class Solution {
public:
    int possibleStringCount(string word) {
        int n = word.size(), ans = 1;
        for(int i = 1; i < n; i++) if(word[i] == word[i - 1]) ans++;
        return ans;
    }
};

// class Solution {
// public:
//     int possibleStringCount(string word) {
//         int count = 0, n = word.size(), ans = 0;
//         for(int i = 1; i < n; i++) {
//             if(word[i] != word[i - 1]) {
//                 if(count > 0) ans += count;
//                 count = 0;
//             } else count++;
//         }
//         return ans + count + 1;
//     }
// };