class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            // 此处先判断区间类型，然后再进行值的判断
            if (nums[mid] > nums[right]) {
                // 翻转点发身在本点或右边
                if (nums[mid] > target && nums[left] <= target) { // 本处的条件设定中 <= 还是 < 与下方的 right 和 left 更新方式对应就可
                // 保证不会把目标点排出搜索空间即可
                    right = mid - 1;
                } else {
                    left = mid;
                }
            } else {
                // 翻转点发生在左侧或没有翻转点
                if (nums[mid] <= target && nums[right] >= target) { 
                    left = mid;
                } else {
                    right = mid - 1;
                }
            }     
        }
        return nums[left] == target ? left : -1;
    }
};