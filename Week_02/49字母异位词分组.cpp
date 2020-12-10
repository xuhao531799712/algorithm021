// 49字母异位词分组
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, int> hashmap;
        for (string str : strs) {
            string tmp = str;
            sort(tmp.begin(), tmp.end());
            if (hashmap.find(tmp) != hashmap.end()) {
                res[hashmap[tmp]].push_back(str);
            } else {
                vector<string> vec;
                vec.push_back(str);
                hashmap[tmp] = res.size();
                res.push_back(vec);
            }
        }
        return res;
    }
};