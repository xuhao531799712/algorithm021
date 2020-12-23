class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                // 翻转点发生在本点或右侧
                left = mid + 1;
            } else {
                // 注意，当 nums[mid] < nums[right] 时， nums[mid] 有可能是最小的值，所以不可以用 right = mid - 1 来更新
                right = mid;
            }
        }
        return nums[left];
    }
};