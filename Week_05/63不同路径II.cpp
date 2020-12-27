// 动态规划，二维数组版本
// 时间复杂度 O(mn),空间复杂度 O(mn)
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();

        // 特殊情况判定，起点或终点处有障碍物，直接返回 0 
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) return 0;

        vector<vector<int>> dp(m, vector<int>(n, 1));

        // 设定初始值
        for (int i = 1; i < m; ++i) {
            if (obstacleGrid[i][0] == 1) dp[i][0] = 0;
            else dp[i][0] = dp[i - 1][0];
        }
        for (int j = 1; j < n; ++j) {
            if (obstacleGrid[0][j] == 1) dp[0][j] = 0;
            else dp[0][j] = dp[0][j - 1];
        }

        // 开始递推
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) dp[i][j] = 0;
                else dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1]; 
    }
};

// 自动向下动态规划，内存优化，一维数组版本
// 时间复杂度 O(mn),空间复杂度 O(n)
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) return 0;
        vector<int> dp(n, 1); // 将 dp[0] 赋值为 1

        // 初始化
        for (int j = 1; j < n; ++j) {
            if (obstacleGrid[0][j] == 1) dp[j] = 0;
            else dp[j] = dp[j - 1];
        }
        
        // 开始递推
        for (int i = 1; i < m; ++i) {
            if (obstacleGrid[i][0] == 1) dp[0] = 0;
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) dp[j] = 0;
                else dp[j] = dp[j] + dp[j - 1];
            }
        }
        return dp[n - 1]; 
    }
};

// 动态规划，内存再优化（针对 n>>m 情况），一维数组版本
// 时间复杂度 O(mn),空间复杂度 O(min(n,m))
// 通过设定 bool 类型 transpose 标志位，判断是否对数组进行了转置
// 若转置，则在每次读取 obstacleGrid 内容时对索引值进行交换
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) return 0;

        bool transpose = false;
        if (n > m) {
            swap(n, m);
            transpose = true;
        }
        vector<int> dp(n, 1); // 将 dp[0] 赋值为 1

        // 初始化
        for (int j = 1; j < n; ++j) {
            if (!transpose && obstacleGrid[0][j] == 1 || transpose && obstacleGrid[j][0] == 1) dp[j] = 0;
            else dp[j] = dp[j - 1];
        }
        
        // 开始递推
        for (int i = 1; i < m; ++i) {
            if (!transpose && obstacleGrid[i][0] == 1 || transpose && obstacleGrid[0][i] == 1) dp[0] = 0;
            for (int j = 1; j < n; ++j) {
                if (!transpose && obstacleGrid[i][j] == 1 || transpose && obstacleGrid[j][i] == 1) dp[j] = 0;
                else dp[j] = dp[j] + dp[j - 1];
            }
        }
        return dp[n - 1]; 
    }
};