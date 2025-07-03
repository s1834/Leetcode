class Solution {
public:
    char kthCharacter(int k) {
        string word = "a";
        while(word.size() < k) for(auto x : word) word += x + 1;
        return word[k - 1];
    }
};