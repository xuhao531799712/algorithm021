class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        for (int start = 0; start < n; ++start) {
            if (s[start] != ' ') {
                // 循环遍历至单词的末尾
                int end = start;
                while (end < n && s[end] != ' ') end++;

                // 反转整个单词
                reverse(s.begin() + start, s.begin() + end);

                // 更新start，去找下一个单词
                start = end;
            }
        }
        return s;
    }
};