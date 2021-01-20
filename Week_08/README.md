# 第八周笔记

## 排序模板

### 归并排序

```cpp
void mergesort(vector<int>& nums, int left = 0, int right = nums.size() - 1) {
    if (right == left) return;
    int mid = left + (right - left) >> 1;
    mergesort(nums, left, mid);
    mergesort(nums, mid + 1, right);
    
    merge(nums, left, mid, right);
}

void merge(vector<int>& nums, int left, int mid, int right) {
    vector<int> tmp(right - left + 1);
    int i = left, j = mid + 1, index = 0;
    while (i <= mid && j <= right) {
        tmp[index++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
    }
    while (i <= mid) tmp[index++] = nums[i++];
    while (j <= right) tmp[index++] = nums[j++];

    for (i = left, index = 0; i <= right;) nums[i++] = tmp[index++];
}
```