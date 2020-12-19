class Solution {
 public:
  vector<vector<int>> combine(int n, int k) {
    backtracking(1, n, k);
    return ans;
  }

  void backtracking(int startIndex, int n, int k) {
    if (k == 0) {
      ans.push_back(vec);
      return;
    }
    for (int i = startIndex; i <= n - k + 1; ++i) {
      vec.push_back(i);
      backtracking(i + 1, n, k - 1);
      vec.pop_back();
    }
  }

 private:
  vector<vector<int>> ans;
  vector<int> vec;
};