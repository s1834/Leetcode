class Solution {
public:
    bool checkRows(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
        map<char, int> mp;
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    mp[board[i][j]]++;
                    if (mp[board[i][j]] > 1) {
                        return false;
                    }
                }
            }
            mp.clear();
        }

        return true;
    }

    bool checkColumns(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
        map<char,int> mp;
            for (int j = 0; j < 9; j++) {
                if (board[j][i] != '.') {
                    mp[board[j][i]]++;
                    if (mp[board[j][i]] > 1) {
                        return false;
                    }
                }
            }
            mp.clear();
        }
        
        return true;
    }

    bool checkBlock(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i += 3) {
        map<char,int> mp;
            for(int j = i; j < 9; j += 3) {
                for (int m = 0; m < 3; m++) {
                    for (int n = 0; n < 3; n++) {
                        if (board[i + m][j + n] != '.') {
                            mp[board[i + m][j + n]]++;
                            if (mp[board[i + m][j + n]] > 1) {
                                return false;
                            }
                        }
                    }
                    mp.clear();
                }
            }
        }

        return true;
    }

    bool isValidSudoku(vector<vector<char>>& board) {
        return checkRows(board) && checkColumns(board) && checkBlock(board);
    }
};