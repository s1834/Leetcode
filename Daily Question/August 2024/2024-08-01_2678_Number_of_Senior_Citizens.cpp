class Solution {
public:
    int countSeniors(vector<string>& details) {
        int count = 0, n = details.size();
        for(int i = 0; i < n; i++) {
            if(stoi(details[i].substr(11,2)) > 60) count++;
        }
        return count;
    }
};