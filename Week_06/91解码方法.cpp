// 动态规划，dp[i] 为到第 i 个字符位置，可以编码的总数
// 递归方程： if (s[i-1]==1 || s[i-1]==2 && s[i]<=6) dp[i] += dp[i-2]
//            if (s[i]!=0) dp[i] += dp[i-1]
// 在实现的时候，dp 数组在最开始多申请一位出来，方便处理
class Solution {
public:
    int numDecodings(string s) {
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        for (int i = 1 ; i <= s.size(); ++i) {
            if (i >= 2 && (s[i - 2] == '1' || s[i - 2] == '2' && s[i - 1] <= '6')) dp[i] += dp[i - 2];
            if (s[i - 1] != '0') dp[i] += dp[i - 1];
        }
        return dp[s.size()];
    }
};

// 优化内存
class Solution {
public:
    int numDecodings(string s) {
        vector<int> dp(3, 0);
        dp[0] = 1;
        if (s[0] != '0') dp[1] = 1;
        for (int i = 2 ; i <= s.size(); ++i) {
            if (s[i - 2] == '1' || s[i - 2] == '2' && s[i - 1] <= '6') {
                dp[2] += dp[0];
            }
            if (s[i - 1] != '0') {
                dp[2] += dp[1];
            }
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = 0;
        }
        return dp[1];
    }
};
