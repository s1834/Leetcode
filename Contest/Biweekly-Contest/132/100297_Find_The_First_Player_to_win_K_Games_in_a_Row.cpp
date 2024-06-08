class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k) {
        int temp = 0, n = skills.size(), curWinner = skills[0];
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
            }
        }
        return 0;
    }
};