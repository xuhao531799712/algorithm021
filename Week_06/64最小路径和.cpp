// 动态规划
// 状态定义， dp[i][j] 为从起点 [0,0] 到 [i,j] 位置的最小路径和
// 递推方程， dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];

// 下面是偷懒直接在原数组原位修改
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (!grid.size() || !grid[0].size()) return 0;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;
                if (i == 0) grid[i][j] += grid[i][j - 1];
                else if (j == 0) grid[i][j] += grid[i - 1][j];
                else grid[i][j] += min(grid[i - 1][j], grid[i][j -1]);
            }
        }
        return grid[m - 1][n - 1];
    }
};

// 当然因为修改原数组并不合适，另建 dp 数组更好
// 使用 dp 数组的话，因为每次更新值只与上一个值和右一个值相关，可以只建一个一维数组，进行内存优化
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (!grid.size() || !grid[0].size()) return 0;
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n, 0);
        dp[0] = grid[0][0];
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;
                if (i == 0) dp[j] = dp[j - 1] + grid[i][j];
                else if (j == 0) dp[j] += grid[i][j];
                else dp[j] = min(dp[j], dp[j -1]) + grid[i][j];
            }
        }
        return dp[n - 1];
    }
};

// 同时，可以根据 m 和 n 的大小，取小的值来建立一维 dp 数组，来减小空间使用