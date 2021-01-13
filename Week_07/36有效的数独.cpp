class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<int>> row(9, vector<int>(9, 0));
        vector<vector<int>> col(9, vector<int>(9, 0));
        vector<vector<int>> box(9, vector<int>(9, 0));
        // box 0~8 i/3 * 3 + j / 3
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') continue;
                int val = board[i][j] - '1';
                int boxIndex = i / 3 * 3 + j / 3;
                if(row[i][val] || col[j][val] || box[boxIndex][val]) return false;
                row[i][val] = col[j][val] = box[boxIndex][val] = 1;
            }
        }
        return true;
    }
};