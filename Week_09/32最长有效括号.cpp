// 本次只使用了动态规划做法
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        int res = 0;
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] == ')') {
                if (i > 1 && s[i - 2] == '(') dp[i] += dp[i - 2] + 2;
                else if (i - dp[i - 1] - 2 >= 0 && s[i - dp[i - 1] - 2] == '(') dp[i] += dp[i - 1] + 2 + dp[i - dp[i - 1] - 2];
                res = max(res, dp[i]);
            }
        }
        return res;
    }
};