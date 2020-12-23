// 深度优先搜索
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        if (board[click[0]][click[1]] == 'M') {
            board[click[0]][click[1]] = 'X';
            return board;
        }
        dfs(board, click[0], click[1]);
        return board;
    }

    void dfs(vector<vector<char>>& board, int row, int col) {
        if (!(row >=0 && row < board.size() && col >= 0 && col < board[0].size()) || board[row][col] != 'E') return;
        int cc = count(board, row, col);
        if (cc != 0) {
            board[row][col] = cc + '0';
            return ;
        }
        board[row][col] = 'B';
        for (int i = 0; i < 8; ++i) {
            int new_row = row + dir_x[i], new_col = col + dir_y[i];
            dfs(board, new_row, new_col);
        }
    }

    int count(vector<vector<char>>& board, int row, int col) {
        int countV = 0;
        for (int i = 0; i < 8; ++i) {
            int new_row = row + dir_x[i], new_col = col + dir_y[i];
            if (new_row >=0 && new_row < board.size() && new_col >= 0 && new_col < board[0].size() && board[new_row][new_col] == 'M') 
                ++countV;
        }
        return countV;
    }

    vector<int> dir_x = {0, 1, 0, -1, 1, 1, -1, -1};
    vector<int> dir_y = {1, 0, -1, 0, 1, -1, 1, -1};
};

// 广度优先搜索
// 注意，广度优先搜索会将待处理的节点加入到队列中，但没办法直接判断某些节点是否已经被加入到队列中会造成队列中加入重复的节点
// 需要加一个 visited 数组来记录访问过的节点
// 深度优先搜索不用，可以直接根据当前节点是否为 'E' 直接判断
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        if (board[click[0]][click[1]] == 'M') {
            board[click[0]][click[1]] = 'X';
            return board;
        }
        
        queue<pair<int, int>> que;
        que.push(make_pair(click[0], click[1]));
        vector<vector<int>> visited(board.size(), vector<int>(board[0].size(), 0));

        while (!que.empty()) {
            int row = que.front().first, col = que.front().second;
            que.pop();
            int cc = count(board, row, col);
            if (cc != 0) board[row][col] = cc + '0';
            else {
                board[row][col] = 'B';
                for (int i = 0; i < 8; ++i) {
                    int new_row = row + dir_x[i], new_col = col + dir_y[i];
                    if (new_row >=0 && new_row < board.size() && new_col >= 0 && new_col < board[0].size() && board[new_row][new_col] == 'E' && !visited[new_row][new_col]) {
                        que.push(make_pair(new_row, new_col));
                        visited[new_row][new_col] = 1;
                    }   
                }
            }
        }

        return board;
    }

    int count(vector<vector<char>>& board, int row, int col) {
        int countV = 0;
        for (int i = 0; i < 8; ++i) {
            int new_row = row + dir_x[i], new_col = col + dir_y[i];
            if (new_row >=0 && new_row < board.size() && new_col >= 0 && new_col < board[0].size() && board[new_row][new_col] == 'M') 
                ++countV;
        }
        return countV;
    }

    vector<int> dir_x = {0, 1, 0, -1, 1, 1, -1, -1};
    vector<int> dir_y = {1, 0, -1, 0, 1, -1, 1, -1};
};