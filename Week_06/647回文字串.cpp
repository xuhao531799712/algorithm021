// 本题引出动态规划另一个我不太注意的地方
// 即在进行递推时的遍历顺序，要保证遍历过程中一直使用已得到的数值，此处要注意多重循环的先后顺序
class Solution {
public:
    int countSubstrings(string s) {
        // 状态：dp[i][j] 表示字符串s在[i,j]区间的子串是否是一个回文串。
        // 递推方程 dp[i][j] == dp[i+1][j-1] && s[i] == s[j]
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));
        for (int i = 0; i < n; ++i) dp[i][i] = true;
        int count = n;

        // 接下来是重点，涉及 i 和 j 的遍历谁在外面
        // 由于 dp[i][j] 的值与 dp[i+1][j-1] 相关，如果 i 在外循环从小到大，那么 dp[i+1] 的序列就是未来值，所以不可以
        // 而将 j 放在外循环，则 dp[i+1][j-1] 是过去值，是可以取到的
        // for (int j = 0; j < n; ++j) {
        //     for (int i = 0; i < j; ++i) {
        //         if (s[i] == s[j]) {
        //             if (i >= j - 1) dp[i][j] = true;
        //             else dp[i][j] = dp[i+1][j-1];
        //             if (dp[i][j]) count++;
        //         }
        //     }
        // }

        // 但如果采用循环递减的话，就是另一种情况如下
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    if (i >= j - 1) dp[i][j] = true;
                    else dp[i][j] = dp[i+1][j-1];
                    if (dp[i][j]) count++;
                }
            }
        }

        return count;
    }
};


// 本题还有不使用动态规划的方法，中心法，会比上面的动态规划快，因为它相当于在动态规划的过程中进行了剪枝
// 会遍历比上方解法更小的空间来得到答案
// 中心法就是遍历字符串的每个字符，并把当前字符作为子串的中心，向两边延伸探索回文字串
// 注意：字符长度为奇数的回文子串和偶数的回文子串处理不同
class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;
        for (int i = 0; i < s.size(); ++i) {
            // 两种中心，一种是以当前字符为中心，一种是以当前字符和前一个字符为中心前提是两个字符相同
            count++; // 单个字符算一个回文子串
            for (int j = 1; i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]; ++j) count++; // 奇数子串

            if (i > 0 && s[i] == s[i - 1]) {
                count++;
                for (int j = 1; i - j >= 1 && i + j < s.size() && s[i - 1 - j] == s[i + j]; ++j) count++; // 偶数子串
            }
        }
        return count;
    }
};