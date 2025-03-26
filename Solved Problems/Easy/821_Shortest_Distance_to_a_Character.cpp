class Solution {
    public:
        vector<int> shortestToChar(string s, char c) {
            vector<int> answer;
            int i = 0, j = 0, n = s.size();
            bool occurance = true;
            while(i < n) {
                if(occurance && s[j] == c) occurance = false;
                if(occurance) {
                    j++;
                    continue;
                }
                if(s[i] == c) {
                    int temp = j + 1;
                    j = i;
                    while(temp < j) {
                        answer[temp] = min(answer[temp], abs(j - temp));
                        temp++;
                    } 
                }
                answer.push_back(abs(j - i));
                i++;
            }
            return answer;
        }
    };