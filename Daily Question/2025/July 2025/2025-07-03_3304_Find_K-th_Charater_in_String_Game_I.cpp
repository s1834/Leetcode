class Solution {
public:
    char kthCharacter(int k) {
        string word = "a";
        while(word.size() < k) {
            string temp = "";
            for(auto x : word) temp += x + 1;
            word += temp;
        }
        return word[k - 1];
    }
};

/*
1. keep checking the size of string and add chars until it is at least k
2. then return the k-1 th character

the error in last submission was i was directly increasing the size of the word, and as word was already in x, it gave runtime error
*/