class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size(), max = 0, maxInd = 0;
        for (int i = 0; i < n - minutes + 1; i++) {
            int temp = 0;
            bool grump = false;
            for (int j = 0; j < minutes; j++) {
                temp += customers[i + j];
                if(!grump && grumpy[i] == 1) {
                    grump = true;
                }
            }
            
            if(grump && temp > max) {
                max = temp;
                maxInd = i;
            }
        }

        max = 0;
        for (int i = 0; i < n; i++) {
            if(grumpy[i] != 1 || (i >= maxInd && i < maxInd + minutes)) {
                max += customers[i];
            }
        }
        
        return max;
    }
};