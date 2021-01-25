// 初始版本，采用递归
// 左右指针，当遇到左右字符不相同时，分成两个支路继续递归
// 缺点：会有 O(n) 的栈空间使用
class Solution {
public:
    bool validPalindrome(string s) {
        return dfs(s, 0, s.size() - 1, false);
    }

    bool dfs(string& s, int left, int right, bool flag) {
        if (left >= right) return true;
        if (s[left] == s[right]) {
            return dfs(s, left + 1, right - 1, flag);
        } else {
            if (flag) return false;
            return dfs(s, left + 1, right, true) || dfs(s, left, right - 1, true);
        }
    }
};

// 优化版本
// 采用递归，优化空间
class Solution {
public:
    bool validPalindrome(string s) {
        for (int left = 0, right = s.size() - 1; left < right; left++, right--) {
            if (s[left] != s[right]) {
                return checkhelper(s, left + 1, right) || checkhelper(s, left, right - 1);
            }
        }
        return true;
    }

    bool checkhelper(string& s, int left, int right) {
        for (; left < right; left++, right--) {
            if (s[left] != s[right]) {
                return false;
            }
        }
        return true;
    }
};