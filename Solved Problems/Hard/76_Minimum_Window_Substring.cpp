// class Solution {
// public:
//     string minWindow(string s, string t) {
//         map<char, int> mp1, mp2;
//         for (auto x : t) mp1[x]++;
        
//         int n = s.size(), l = 0, r = 0, mn = INT_MAX, minL = -1, minR = -1;
//         int have = 0, need = mp1.size();
//         while(r < n) {
//             if(mp1[s[r]]) mp2[s[r]]++;

//             if(mp1[s[r]] && mp1[s[r]] == mp2[s[r]]) have++;

//             while(have == need) {
//                 if(r - l + 1 < mn) {
//                     minL = l;
//                     minR = r;
//                     mn = r - l + 1;
//                 }

//                 mp2[s[l]]--;
//                 if(mp1[s[l]] && mp2[s[l]] < mp1[s[l]]) have--;
//                 l++;
//             }
//             r++;
//         }

//         string ans = "";
//         for(int i = minL; i <= minR && mn != INT_MAX; i++) ans += s[i];
//         return ans;
//     }
// };

class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        if (n < m) return "";

        unordered_map<char, int> mp1, mp2;
        for (char c : t) mp1[c]++;

        int l = 0, r = 0, have = 0, need = mp1.size(), first = 0, last = INT_MAX;

        while (r < n) {
            mp2[s[r]]++;

            if (mp1[s[r]] && mp2[s[r]] == mp1[s[r]]) have++;

            while (have == need) {
                if (r - l + 1 < last) {
                    last = r - l + 1;
                    first = l;
                }

                mp2[s[l]]--;
                if (mp1[s[l]] && mp2[s[l]] < mp1[s[l]]) have--;
                l++;
            }
            r++;
        }

        if (last == INT_MAX) return "";
        return s.substr(first, last);
    }
};


/*
Explanation of commented code:
1) map all the charaters of t in mp1
2) use two pointers l and r to traverse the string s
3) use mp2 to keep track of the characters in the current window
4) if the character at s[r] is in mp1, increment its count in mp2
5) if the count of s[r] in mp2 is equal to its count in mp1, increment have
6) while have is equal to need, check if the current window is smaller than the minimum window found so far
7) if it is, update minL, minR, and mn
8) decrement the count of s[l] in mp2
9) if the count of s[l] in mp2 is less than its count in mp1, decrement have
10) increment l
11) increment r
12) return the substring from minL to minR if mn is not INT_MAX, otherwise return an empty string

before i was trying almost the same approach but was not taking into account all the edge cases and was not going for generalised solution, was more focused on what testcases were failing and make it correct for that specific case
*/