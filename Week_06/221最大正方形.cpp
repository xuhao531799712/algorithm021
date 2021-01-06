// 动态规划
// 状态定义 dp[i][j] 以 matirx[i][j] 为右下角的最大正方形边长大小
// 递推公式 if(matrix[i][j] == 1) dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
 class Solution {
 public:
     int maximalSquare(vector<vector<char>>& matrix) {
         if (!matrix.size() || !matrix[0].size()) return 0;
         int m = matrix.size(), n = matrix[0].size();
         int maxlen = 0;
         vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
         for (int i = 1; i <= m; ++i) {
             for (int j = 1; j <= n; ++j) {
                 if (matrix[i - 1][j - 1] == '1') {
                     dp[i][j] = min(min(dp[i - 1][j], dp[i - 1][j - 1]), dp[i][j - 1]) + 1;
                     maxlen = max(maxlen, dp[i][j]);
                 }
             }
         }
         return maxlen * maxlen;
     }
 };

// 每个位置只有另外三个位置的值进行推导，由此进行内存优化
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (!matrix.size() || !matrix[0].size()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        int maxlen = 0;
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            int leftup = 0;
            for (int j = 1; j <= n; ++j) {
                int tmp = dp[j]; // 存 [i-1][j] 位置的值作为下一次 [i][j+1] 处的左上方的值
                if (matrix[i - 1][j - 1] == '1') {
                    dp[j] = min(min(dp[j], leftup), dp[j - 1]) + 1;
                    maxlen = max(maxlen, dp[j]);
                } else {
                    dp[j] = 0; // 注意此处要比二维dp数组多一步处理，多进行一步清零操作
                }
                leftup = tmp;
            }
        }
        return maxlen * maxlen;
    }
};