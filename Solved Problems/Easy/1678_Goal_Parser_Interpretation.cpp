class Solution {
public:
    string interpret(string command) {
        int n = command.size();
        string s = "";
        for (int i = 0; i < n; i++) {
            if (command[i] == 'G') {
                s += 'G';
            } else if (command[i] == '(' && command[i + 1] == ')') {
                s += 'o';
                i++;
            } else {
                s += "al";
                i += 3;
            }
        }
        return s;
    }
};