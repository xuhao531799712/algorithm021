// 动态规划
// 定义状态 dp[i][j] 表示 word1 前 i 位字符组成的字符串和 word2 前 j 位字符组成的字符串的最小编辑距离
// 递推方程分析：  如果 word1[i] == word2[j] 那么 dp[i][j]=dp[i-1][j-1] 而不需要多余的其他步骤
//              而如果 word1[i] != word2[j]， 那么就需要对两个字符子串的最后一位进行处理才可以进行匹配
//              如果采用插入一个字符的操作，在 word2[j] 位置插入和 word1[i]相同的字符，那么 dp[i][j]=dp[i-1][j] + 1；
//              如果采用删除一个字符的操作，删除 word1[i] 第 i 位的字符，那么 dp[i][j]=dp[i][j-1] + 1；
//              如果采用替换一个字符的操作，把 word2[j] 替换为和 word1[i]相同的字符，那么 dp[i][j]=dp[i-1][j-1] + 1；
//      以上取最小者即可。
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        for (int i = 1; i <= word1.size(); ++i) dp[i][0] = i;
        for (int i = 1; i <= word2.size(); ++i) dp[0][i] = i;
        for (int i = 1; i <= word1.size(); ++i) {
            for (int j = 1; j <= word2.size(); ++j) {
                if (word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                else dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
            }
        }
        return dp[word1.size()][word2.size()];
    }
};