class Solution {
public:
    vector<vector<string>> ans;

    vector<vector<string>> solveNQueens(int n) {
        vector<int> col(n, 0); // 列统计
        vector<int> pie(2 * n - 1, 0); // 反对角线统计 col - row 范围 -(n-1) ~ (n-1) 需要加上(n-1)来归正
        vector<int> na(2 * n - 1, 0); // 正对角线统计 col + row, 范围 0 ~ 2*n-2

        vector<string> plane(n, string(n, '.')); // 构建棋盘
        backtrack(plane, 0, col, pie, na);

        return ans;
    }

    void backtrack(vector<string>& plane, int row, vector<int>& col, vector<int>& pie, vector<int>& na) {
        int n = plane.size();
        if (row == n) {
            ans.push_back(plane);
            return ;
        }

        for (int i = 0; i < n; ++i) {
            if (isValid(row, i, col, pie, na)) {
                // 更新状态
                plane[row][i] = 'Q';
                col[i] = 1;
                pie[row - i + n - 1] = 1;
                na[row + i] = 1;

                // 向下递归
                backtrack(plane, row + 1, col, pie, na);

                // 回退状态
                plane[row][i] = '.';
                col[i] = 0;
                pie[row - i + n - 1] = 0;
                na[row + i] = 0;
            }
        }
    }

    bool isValid(int rowIndex, 
        int colIndex, 
        vector<int>& col,
        vector<int>& pie,
        vector<int>& na) {
            if (col[colIndex] || pie[rowIndex - colIndex + col.size() - 1] || na[rowIndex + colIndex]) return false;
            return true;
        }
};