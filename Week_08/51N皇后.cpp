// 位运算版本
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> plane(n, string(n, '.'));

        backtrack(n ,0, 0, 0, 0, plane, ans);

        return ans;
    }

    void backtrack(int& n, int rowIndex, int col, int ld, int rd, vector<string>& plane, vector<vector<string>>& ans){
        if (rowIndex == n) {
            ans.push_back(plane);
            return ;
        }

        int bits = (~(col | ld | rd)) & ((1 << n) - 1); // bits 中为 1 的位置是可以放皇后的位置
        while (bits) {
            int index = __builtin_ctz(bits);
            int p = bits & -bits;
            plane[rowIndex][index] = 'Q';
            bits = bits & (bits - 1);
            backtrack(n, rowIndex + 1, col | p, (ld | p) >> 1, (rd | p) << 1, plane, ans);
            plane[rowIndex][index] = '.';
        }
    }
};
/*
•int __builtin_ffs (unsigned int x)
返回x的最后一位1的是从后向前第几位，比如7368（1110011001000）返回4。
•int __builtin_clz (unsigned int x)
返回前导的0的个数。
•int __builtin_ctz (unsigned int x)
返回后面的0的个数，和__builtin_clz相对。
•int __builtin_popcount (unsigned int x)
返回二进制表示中1的个数。
•int __builtin_parity (unsigned int x)
返回x的奇偶校验位，也就是x的1的个数模2的结果。

此外，这些函数都有相应的usigned long和usigned long long版本，只需要在函数名后面加上l或ll就可以了，比如int __builtin_clzll。
 */