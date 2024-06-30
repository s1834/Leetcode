class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<char> q;
        int n = senate.size(), rCount = 0, dCount = 0;
        for(int i = 0; i < n; i++){
            q.push(senate[i]);
            if(senate[i] == 'R') rCount++;
            else dCount++;
        } 
        
        int r = 0, d = 0;
        while(rCount && dCount) {
            if(q.front() == 'R') {
                if(d) {
                    d--;
                    rCount--;
                } else {
                    q.push('R');
                    r++;
                }
            } else {
                if(r) {
                    r--;
                    dCount--;
                } else {
                    q.push('D');
                    d++;
                }
                
            }
            q.pop();
        }
        return rCount ? "Radiant" : "Dire";
    }
};