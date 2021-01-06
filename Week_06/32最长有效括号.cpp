// 有效括号题：单种类括号题、多种类括号题
// 多种类括号题用栈
// 单种类括号题可用动态规划、栈、计数，其中计数最优。单调规划有O(n)复杂度和O(n^2)复杂度两种

// 回文子串为什么一定要用二维dp，因为它需要知道子串的起始位置和终止位置，是对暴力遍历的化简
// 那能不能用一维dp呢，dp数组里存以本位置结尾的。核心区别在于题目的要求，如果要求符合条件的个数，那么就必须要两个下标挨个遍历，也就是使用二维dp来优化
// 而如果是求最长，那么就不需要遍历两个下标了，只要一个下标就可以了
// 这里的区别就是状态的定义，一维dp数组以本位置结尾的符合要求的子串的最大长度

// dp数组中状态的定义只能是与本位置严格相关的状态才可以，不然无法进行下一个位置的递推
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size(), largest = 0;
        vector<int> dp(n, 0);
        for (int i = 1; i < n; ++i) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') dp[i] = dp[i - 1] + 2 + ((i - dp[i - 1] >= 2) ? dp[i - dp[i - 1] - 2] : 0);
                largest = max(largest, dp[i]);
            }
        }
        return largest;
    }
};



// 单调栈做法
 class Solution {
 public:
     int longestValidParentheses(string s) {
         int longest = 0;
         stack<int> stc; // 只存左括号的下标，栈底是一个不合规矩的右括号下标
         // 只在 stc.size() == 1 时统计一次当前有效长度
         stc.push(-1); // 加入初始值
         for (int i = 0; i < s.size(); ++i) {
             if (s[i] == '(') stc.push(i);
             else {
                 stc.pop();
                 if (stc.size() == 0) {
                     stc.push(i); // 新的栈底
                 } else {
                     longest = max(longest, i - stc.top());
                 }
             }
         }
         return longest;
     }
 };

// 计数做法
class Solution {
public:
    int longestValidParentheses(string s) {
        int longest = 0;
        int left = 0, right = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') ++left;
            else {
                ++right;
                if (right == left) { // 此处判定条件只能为==时进行计数，否则 <= 无法处理 ()(() 这种情况
                    longest = max(longest, right * 2);
                } else if (right > left) {
                    left = right = 0;
                }
            }
        }
        // 还要再反向一遍，因为 (() 在上面循环为 0
        left = right = 0;
        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] == ')') ++right;
            else {
                ++left;
                if (right == left) {
                    longest = max(longest, right * 2);
                } else if (left > right) {
                    left = right = 0;
                }
            }
        }
        return longest;
    }
};