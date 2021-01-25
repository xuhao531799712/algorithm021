class Solution {
public:
    string reverseStr(string s, int k) {
        int index = 0, size = s.size();
        for (; index < size; ) {
            // 找到本次反转的右边界，如果本次剩余不够k个，就将剩余都反转
            int end = min(index + k, size) - 1;

            // 进行翻转
            int half = index + ((end - index) >> 1);
            for (int i = index; i <= half; ++i) {
                swap(s[i], s[end + index - i]);
            }

            // 移到下个位置
            index += 2 * k;
        }
        return s;
    }
};