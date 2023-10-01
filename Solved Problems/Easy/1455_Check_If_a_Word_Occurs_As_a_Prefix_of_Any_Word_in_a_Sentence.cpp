class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        int n = sentence.size(), n1 = searchWord.size(), count = 0, flag;
        for (int i = 0; i < n; i++) {
            flag = 1;
            if (i == 0 || sentence[i] == ' ') {
                for (int j = 0; j < n1; j++) {
                    if(i == 0) {
                        if(sentence[i + j] != searchWord[j]) {
                            flag = 0;
                            break;
                        }
                        continue;
                    }
                    if (sentence[i + j + 1] == ' ' || sentence[i + j + 1] != searchWord[j]) {
                        flag = 0;
                        break;
                    }
                }
                count++;
                if(flag) {
                    return count;
                }
            }
        }
        return -1;
    }
};