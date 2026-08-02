class Solution {
    public:
        int maxFreqSum(string s) {
            unordered_map<char, int> mp;
            for(auto x : s) mp[x]++;
    
            int vowels = 0, consonants = 0;
            for(auto x : mp) {
                if(x.first == 'a' || x.first == 'e' || x.first == 'i' || x.first == 'o' || x.first == 'u') vowels = max(vowels, x.second);
                else consonants = max(consonants, x.second);
            }
    
            return vowels + consonants;
        }
    };