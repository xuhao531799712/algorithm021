class Solution {
public:
    vector<string> als = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ans;
    string str = "";

    vector<string> letterCombinations(string digits) {
        dfs(digits, 0);
        return ans.size() == 1 ? vector<string>() : ans;
    }

    void dfs(string& digits, int index) {
        if (index == digits.size()) {
            ans.push_back(str);
            return ;
        }

        for (auto c : als[digits[index] - '2']) {
            str.push_back(c);
            dfs(digits, index + 1);
            str.pop_back();
        }
    }
};