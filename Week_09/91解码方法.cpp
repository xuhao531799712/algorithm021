// 动态规划
// 状态定义 dp[i] 表示 s 的前 i 位字符的子串的解码方法总数
class Solution {
 public:
     int numDecodings(string s) {
         int n = s.size();
         vector<int> dp(n + 1, 0);
         dp[0] = 1;
         if (s[0] != '0') dp[1] = 1;
         for (int i = 2; i <= n; ++i) {
             // 判断是否可以和前一个位置作为一个数字
             if (s[i - 2] == '1' || s[i - 2] == '2' && s[i - 1] <= '6') dp[i] += dp[i - 2];

             // 判断本位置是否可以作为一个单独的数字
             if (s[i - 1] != '0') dp[i] += dp[i - 1];
         }
         return dp[n];
     }
 };


// 优化内存
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        int dp0 = 1, dp2 = 0, dp1 = (s[0] != '0' ? 1 : 0);
        for (int i = 2; i <= n; ++i) {
            // 判断是否可以和前一个位置作为一个数字
            if (s[i - 2] == '1' || s[i - 2] == '2' && s[i - 1] <= '6') dp2 += dp0;

            // 判断本位置是否可以作为一个单独的数字
            if (s[i - 1] != '0') dp2 += dp1;

            dp0 = dp1;
            dp1 = dp2;
            dp2 = 0;
        }
        return dp1;
    }
};