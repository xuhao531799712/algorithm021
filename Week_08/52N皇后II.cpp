class Solution {
public:
    int totalNQueens(int n) {
        int ans = 0;
        backtrack(n ,0, 0, 0, 0, ans);
        return ans;
    }

    void backtrack(int& n, int rowIndex, int col, int ld, int rd, int& ans) {
        if (rowIndex == n) {
            ++ans;
            return ;
        }

        int bits = (~(col | ld | rd)) & ((1 << n) - 1); // bits 中为 1 的位置是可以放皇后的位置
        while (bits) {
            int p = bits & -bits;
            bits = bits & (bits - 1);
            backtrack(n, rowIndex + 1, col | p, (ld | p) >> 1, (rd | p) << 1, ans);
        }
    }
};