class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> indices(2);
        
        for (int i = 0; i < numbers.size(); i++) {
            for (int j = i + 1; j < numbers.size(); j++) {
                if(numbers[i] + numbers[j] == target) {
                    indices[0] = i + 1;
                    indices[1] = j + 1;
                    i = numbers.size();
                    break;
                }
            }
        }
        return indices;
    }
};