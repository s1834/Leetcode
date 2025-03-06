class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        vector<string> words;
        int n = sentence.size();
        string word = "";
        for (int i = 0; i < n; i++) {
            if(sentence[i] == ' ' || i == n - 1) {
                words.push_back(i != n - 1 ? word : word + sentence[i]);
                word = "";
                continue;
            }
            word += sentence[i];
        }

        n = words.size();
        sentence = "";
        int dictSize = dictionary.size();
        bool appended;
        for (int i = 0; i < n; i++) {
            appended = false;
            for (int j = 0; j < dictSize; j++) {
                if(words[i].size() >= dictionary[j].size()) {
                    for (int k = 0; k < dictionary[j].size(); k++) {
                        if(dictionary[j][k] != words[i][k]) {
                            appended = false;
                            break;
                        }
                        appended = true;
                    }
                    if(appended && words[i] > dictionary[j]) {
                        words[i] = dictionary[j];
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            sentence += i != n - 1 ? words[i] + ' ' : words[i];
        }
        return sentence;
    }
};