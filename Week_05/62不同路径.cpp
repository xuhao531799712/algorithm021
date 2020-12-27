// 暴力递归，分解子问题，超时
// 时间复杂度 指数级别 
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 1 || n == 1) return 1;
        return uniquePaths(m - 1, n) + uniquePaths(m , n - 1); 
    }
};

// 递归加上记忆化缓存，使用哈希表做缓存
// 时间复杂度 O(mn),空间复杂度 O(mn)
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 1 || n == 1) return 1;
        string key = to_string(m) + "_" + to_string(n);
        if (!memo.count(key)) memo[key] = uniquePaths(m - 1, n) + uniquePaths(m , n - 1);
        return memo[key]; 
    }
private:
    unordered_map<string, int> memo;
};

// 动态规划，二维数组版本
// 时间复杂度 O(mn),空间复杂度 O(mn)
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 1 || n == 1) return 1;
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1]; 
    }
};

// 动态规划，内存优化，一维数组版本
// 时间复杂度 O(mn),空间复杂度 O(n)
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 1 || n == 1) return 1;
        vector<int> dp(n, 1);
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[j] = dp[j] + dp[j - 1];
            }
        }
        return dp[n - 1]; 
    }
};

// 动态规划，内存再优化（针对 n>>m 情况），一维数组版本
// 时间复杂度 O(mn),空间复杂度 O(min(n,m))
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 1 || n == 1) return 1;
        if (n > m) swap(n, m);
        vector<int> dp(n, 1);
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[j] = dp[j] + dp[j - 1];
            }
        }
        return dp[n - 1]; 
    }
};