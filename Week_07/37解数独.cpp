class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        scanBoard(board);
        dfs(board, 0);
    }

    void dfs(vector<vector<char>>& board, int index) {
        if (index == pos.size()) {
            valid = true;
            return;
        }

        int i = pos[index].first, j = pos[index].second;
        for (int k = '1'; k <= '9' && !valid; ++k) {
            board[i][j] = k;
            if (!isValidSudoku(board, i, j)) continue;
            int val = k - '1';
            int boxIndex = i / 3 * 3 + j / 3;
            row[i][val] = col[j][val] = box[boxIndex][val] = 1;
            dfs(board, index + 1);
            row[i][val] = col[j][val] = box[boxIndex][val] = 0;
        }
    }

    void scanBoard(vector<vector<char>>& board) {
        // 遍历棋盘，初始化数组，以及记录待填充位置
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') pos.push_back(make_pair(i, j));
                else {
                    int val = board[i][j] - '1';
                    int boxIndex = i / 3 * 3 + j / 3;
                    row[i][val] = col[j][val] = box[boxIndex][val] = 1;
                }
            }
        }
    }

    bool isValidSudoku(vector<vector<char>>& board, int& i, int& j) {
        // 判断 i j 处放的新值是否符合标准
        // box 0~8 i/3 * 3 + j / 3
        int val = board[i][j] - '1';
        int boxIndex = i / 3 * 3 + j / 3;
        if(row[i][val] || col[j][val] || box[boxIndex][val]) return false;
        else return true;
    }

    vector<vector<int>> row = vector<vector<int>>(9, vector<int>(9, 0));
    vector<vector<int>> col = vector<vector<int>>(9, vector<int>(9, 0));
    vector<vector<int>> box = vector<vector<int>>(9, vector<int>(9, 0));
    vector<pair<int, int>> pos;
    bool valid = false;
};