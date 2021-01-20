class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        mergesort(nums, 0, nums.size() - 1);
        return ret;
    }

    void mergesort(vector<int>& nums, int left, int right) {
        if (right == left) return;
        int mid = left + ((right - left) >> 1);
        mergesort(nums, left, mid);
        mergesort(nums, mid + 1, right);

        // 遍历找翻转对的个数
        // 注意此处找个数是 O(n) 的时间复杂度
        int i = left;
        int j = mid + 1;
        while (i <= mid) {
            while (j <= right && (long long)nums[i] > 2 * (long long)nums[j]) j++;
            ret += (j - mid - 1);
            i++;
        }

        merge(nums, left, mid, right);
    }

    void merge(vector<int>& nums, int left, int mid, int right) {
        vector<int> tmp(right - left + 1);
        int i = left, j = mid + 1, index = 0;
        while (i <= mid && j <= right) {
            if (nums[i] <= nums[j]) {
                tmp[index++] = nums[i++];
            } else {
                tmp[index++] = nums[j++];
            }
        }
        while (i <= mid) tmp[index++] = nums[i++];
        while (j <= right) tmp[index++] = nums[j++];

        for (i = left, index = 0; i <= right;) nums[i++] = tmp[index++];
    }

private:
    int ret = 0;
};

