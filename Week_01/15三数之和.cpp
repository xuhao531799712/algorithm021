// 15.三数之和
class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    if (nums.size() < 3) return {};
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    for (int i = 0; i < nums.size() - 2; i++) {
      if (nums[i] > 0) break;
      if (i > 0 && nums[i] == nums[i - 1]) continue;
      int left = i + 1, right = nums.size() - 1;
      while (left < right) {
        int sum = nums[i] + nums[left] + nums[right];
        if (sum < 0) {
          while (left < right && nums[left] == nums[++left])
            ;
        } else if (sum > 0) {
          while (left < right && nums[right] == nums[--right])
            ;
        } else {
          res.push_back({nums[i], nums[left], nums[right]});
          while (left < right && nums[left] == nums[++left])
            ;
          while (left < right && nums[right] == nums[--right])
            ;
        }
      }
    }
    return res;
  }
};