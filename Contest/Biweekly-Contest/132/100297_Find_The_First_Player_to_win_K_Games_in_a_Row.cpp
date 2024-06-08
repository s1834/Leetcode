class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k) {
        int temp = 0, n = skills.size(), curWinner = skills[0], re = 0, prev;
        vector<int> skillsTemp;
        skillsTemp = skills;
        for (int i = 1; i < n; i++) {
            if(curWinner > skillsTemp[i]) {
                temp++;
                if(temp >= k) {
                    return find(skills.begin(), skills.end(), curWinner) - skills.begin();
                }
            } else {
                temp = 1;
                curWinner = skillsTemp[i];
            }
            
            if(i == n - 1) {
                i = -1;
                if(re > 0 && curWinner == prev) {
                    break;
                }
                prev = curWinner;
                re++;
            }
        }
        return find(skills.begin(), skills.end(), curWinner) - skills.begin();
    }
};