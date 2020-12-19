class Solution {
 public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<int> path(nums.size(), 0);  // 0 表示未使用
    backtracking(nums, path);
    return ans;
  }

  void backtracking(vector<int>& nums, vector<int>& path) {
    if (vec.size() == nums.size()) {
      ans.push_back(vec);
      return;
    }

    for (int i = 0; i < path.size(); ++i) {
      if (path[i] == 0) {
        path[i] = 1;
        vec.push_back(nums[i]);
        backtracking(nums, path);
        vec.pop_back();
        path[i] = 0;
      }
    }
  }

 private:
  vector<vector<int>> ans;
  vector<int> vec;
};