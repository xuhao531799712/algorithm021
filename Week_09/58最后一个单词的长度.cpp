class Solution {
public:
    int lengthOfLastWord(string s) {
        int length = 0;
        int n = s.size();
        // 从后往前遍历
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == ' ') {
                // 终止条件
                if (i < n - 1 && s[i + 1] != ' ') break;

                // 如果是末尾的空格，就跳过
                else continue;
            }
            ++length;
        }
        return length;
    }
};