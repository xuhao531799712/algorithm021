// 利用 vector 的 == 运算符重载可直接判断两个 vector 对象是否相等
// 采用窗口匹配
// 时间复杂度 O(m+n) 空间复杂度O(1) 数组大小是常量值，比较大小的操作时间复杂度也是常量值

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        // charvec 为 p 对应的计数数组， window 为在 s 上进行移动的窗口中的计数数组
        vector<int> charvec(26, 0), window(26, 0);
        vector<int> ans;
        int ps = p.size(), ss = s.size();

        // 异常值判断
        if (ps > ss) return ans;

        // p 对应的计数数组构建
        for (auto c : p) ++charvec[c - 'a'];

        // window 的初始化
        for (int i = 0; i < ps; ++i) ++window[s[i] - 'a'];
        if (window == charvec) ans.push_back(0);

        // 开始遍历
        for (int i = ps; i < ss; ++i) {
            --window[s[i - ps] - 'a'];
            ++window[s[i] - 'a'];
            if (window == charvec) ans.push_back(i - ps + 1);
        }

        return ans;
    }
};