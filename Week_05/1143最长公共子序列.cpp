// 方法一。二维dp
// 时间复杂度 O(mn) 空间复杂度 O(mn)
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        // 递推方程
        // if (text1[i] == text2[j]) dp[i][j] = dp[i-1][j-1] + 1;
        // else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
         
        // 初始值设定
        if (text1[0] == text2[0]) dp[0][0] = 1;
        for (int i = 1; i < m; ++i) {
            if (text2[0] == text1[i]) dp[i][0] = 1;
            else dp[i][0] = dp[i - 1][0];
        }
        for (int i = 1; i < n; ++i) {
            if (text1[0] == text2[i]) dp[0][i] = 1;
            else dp[0][i] = dp[0][i - 1];
        }

        // 开始递推
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (text1[i] == text2[j]) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);                
            }
        }

        return dp[m - 1][n - 1];
    }
};

// 方法二。二维dp，代码简约版
// 通过增加一小部分内存占用，来化简代码
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        // 与方法一的区别在于数组开得更大一些
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // 开始递推
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // 注意此处要使用 i-1 与 j-1
                if (text1[i - 1] == text2[j - 1]) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);                
            }
        }

        return dp[m][n];
    }
};

// 方法三。对方法二的内存进行优化，一维dp，代码与内存简约版
// 每个位置的值只与其左边位置、上方位置与左上方位置的值相关，所以可以用一个一位数组加一个变量值来进行
// 从一维数组可以得知左边位置与上方位置的值，再通过常量保存左上方位置的值即可
// 同时令 text2 的长度要小于 text1 的长度
// 达到空间复杂度为 O(min(m,n))
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.size() < text2.size()) swap(text1, text2);
        int m = text1.size(), n = text2.size();
        vector<int> dp(n + 1, 0);

        // 开始递推
        for (int i = 1; i <= m; ++i) {
            int value = 0; // 存储原二维数组每个位置的左上方位置的值
            for (int j = 1; j <= n; ++j) {
                int tmp = dp[j]; // 存储当前位置的原值作为下一次循环的左上方值
                if (text1[i - 1] == text2[j - 1]) dp[j] = value + 1;
                else dp[j] = max(dp[j], dp[j-1]);    
                value = tmp;            
            }
        }

        return dp[n];
    }
};