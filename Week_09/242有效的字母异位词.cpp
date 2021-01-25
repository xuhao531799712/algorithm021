// 方法一：排序后比较
// 时间复杂度 O(mlogm+nlogn) 空间复杂度 O(1)
class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

// 方法二：利用数组（哈希表）来记录每个字母出现的次数，对两个字符串都是一次遍历即可得到结果
// 时间复杂度 O(m+n) 空间复杂度 O(1)
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        vector<int> count(26, 0);
        for (auto c : s) ++count[c - 'a'];
        for (auto c : t) {
            if (count[c - 'a'] <= 0) return false;
            --count[c - 'a'];
        }
        return true;
    }
};