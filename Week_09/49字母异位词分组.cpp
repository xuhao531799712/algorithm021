// 承接自简单题 242

// 方法一：使用排序后的字符串作为哈希表的键
// 时间复杂度 O(nklogk) 空间复杂度 O(nk)
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, int> mm; // 值是在 ans 中的序列
        vector<vector<string>> ans;
        for (auto& str: strs) {
            string tmp = str;
            sort(tmp.begin(), tmp.end());
            if (mm.count(tmp)) {
                ans[mm[tmp]].push_back(str);
            } else {
                mm[tmp] = ans.size();
                ans.push_back(vector<string>(1, str));
            }
        }
        return ans;
    }
};

// 方法二：使用代表计数的字符串作为哈希表的键
// 时间复杂度 O(nk) 空间复杂度 O(nk)

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, int> mm; // 值是在 ans 中的序列
        vector<vector<string>> ans;
        for (auto& str: strs) {
            vector<int> alp(26, 0);
            for (auto c : str) {
                ++alp[c - 'a'];
            }
            string tmp = count(alp);
            if (mm.count(tmp)) {
                ans[mm[tmp]].push_back(str);
            } else {
                mm[tmp] = ans.size();
                ans.push_back(vector<string>(1, str));
            }
        }
        return ans;
    }

    string count(vector<int>& alp) {
        string res = "";
        for (int i = 0; i < 26; ++i) {
            res += to_string(alp[i]) + '.';
        }
        return res;
    }
};