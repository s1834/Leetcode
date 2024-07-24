class Solution {
private:
    bool isPalindrome(string word) {
        int n = word.size(), first = 0, last = n - 1;
        while(first < last) {
            if(word[first] != word[last]) return false;
            first++;
            last--;
        }
        return true;
    }

public:
    string firstPalindrome(vector<string>& words) {
        int n = words.size();
        for(int i = 0; i < n; i++) {
            if(isPalindrome(words[i])) return words[i];
        }
        return "";
    }
};