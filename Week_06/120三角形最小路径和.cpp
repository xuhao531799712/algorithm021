// 1. 暴力解法，dfs，时间复杂度O(n^n) , 空间复杂度 O(n)
// 2. 动态规划, 时间复杂度 O(n^2) , 空间复杂度 O(n)

// 自顶向下
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();

        // 定义dp数组
        vector<int> dp(n, 0);

        // 初始化
        dp[0] = triangle[0][0];

        // 递推;
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i - 1] + triangle[i][i];
            for (int j = i - 1; j > 0; --j) {
                dp[j] = min(dp[j], dp[j - 1]) + triangle[i][j];
            }
            dp[0] = dp[0] + triangle[i][0];
        }

        return *min_element(dp.begin(), dp.end());
    }
};


 
// 自底向上
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();

        // 定义dp数组并初始化
        vector<int> dp(triangle[n - 1]);

        // 递推;
        for (int i = n - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }

        return dp[0];
    }
};
// 自底向上的优势是  1.可以规避边界问题，2. 出口dp[0]就是最终答案，而不用再在数组中寻找最小值