class Solution {
public:
    int firstUniqChar(string s) {
        vector<int> letter(26, 0);
        for (auto c : s) ++letter[c - 'a'];
        for (int i = 0; i < s.size(); ++i) {
            if (letter[s[i] - 'a'] == 1) return i;
        }
        return -1;
    }
};