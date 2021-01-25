class Solution {
public:
    string reverseWords(string s) {
        string res = "";
        int index = 0;
        while (s[index] == ' ') ++index;
        for (; index < s.size(); ) {
            if (s[index] == ' ') {
                // 多个空格只加一个空格
                while (index < s.size() && s[index] == ' ') ++index;
                res += ' ';
            }
            else {
                int left = index;
                while (index < s.size() && s[index] != ' ') ++index;
                int right = index - 1;
                res += reverse(s, left, right);
            }
        }
        if (res[res.size() - 1] == ' ') {
            res = reverse(res, 0, res.size() - 2);
        } else {
            res = reverse(res, 0, res.size() - 1);
        }
        return res;
    }

    string reverse(string s, int left, int right) {
        int half = left + ((right - left) >> 1);
        for (int i = left; i <= half; ++i) {
            swap(s[i], s[right + left - i]);
        }
        return s.substr(left, right - left + 1);
    }
};

// 优化后
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());

        int n = s.size();
        int idx = 0;
        for (int start = 0; start < n; ++start) {
            if (s[start] != ' ') {
                // 填一个空白字符然后将idx移动到下一个单词的开头位置
                if (idx != 0) s[idx++] = ' ';

                // 循环遍历至单词的末尾
                int end = start;
                while (end < n && s[end] != ' ') s[idx++] = s[end++];

                // 反转整个单词
                reverse(s.begin() + idx - (end - start), s.begin() + idx);

                // 更新start，去找下一个单词
                start = end;
            }
        }
        s.erase(s.begin() + idx, s.end());
        return s;
    }
};