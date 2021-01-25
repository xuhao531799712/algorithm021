class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res = "";
        int index = 0;
        if (strs.empty()) return res;
        while (true) {
            char c;
            for (int i = 0; i < strs.size(); ++i) {
                if (index == strs[i].size()) return res;
                if (i == 0) {
                    c = strs[0][index];
                    continue;
                }
                if (strs[i][index] != c) return res;
            }
            ++index;
            res += c;
        }
        return res;
    }
};