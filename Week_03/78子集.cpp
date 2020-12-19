// 递归解法
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> vec;
        dfs(nums, ans, vec, 0);
        return ans;
    }
    // 递归栈的空间复杂度为 O(n)，时间复杂度为 O(2^n)
    // 临时数组的空间复杂度也为 O(n)
    void dfs(vector<int>& nums, vector<vector<int>>& ans, vector<int>& vec, int index) {
        if (index == nums.size()) {
            ans.push_back(vec);
            return ;
        }

        dfs(nums, ans, vec, index + 1); // 不加入本位置元素

        vec.push_back(nums[index]);
        dfs(nums, ans, vec, index + 1); // 加入本位置元素
        vec.pop_back(); // 恢复 vec
    }
};

// 迭代解法
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        ans.push_back({});

        // 外循环时间复杂度为 O(n)
        for (auto num : nums) {
            vector<vector<int>> newans = ans;
            // 内循环遍历时间复杂度为 O(2^n)
            // 临时数组的空间复杂度为 O(n)
            for (auto vec : ans) {
                vec.push_back(num);
                newans.push_back(vec);
            }
            ans = newans;
        }

        return ans;
    }
};

// 此题的时空复杂度还有一些疑惑