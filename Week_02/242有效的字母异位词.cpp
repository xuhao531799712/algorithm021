 // 242有效的字母异位词
// O(n) 解法,使用数组来加速哈希表
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        vector<int> arr(26,0);
        for (char c : s) ++arr[c - 'a'];
        for (char c : t) {
            if (arr[c - 'a'] > 0) arr[c - 'a']--;
            else return false;
        }
        return true;
    }
};

// O(nlogn) 解法，使用排序来
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};