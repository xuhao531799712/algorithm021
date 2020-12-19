// 利用投票法
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res = nums[0];
        int count = 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (count == 0) res = nums[i];
            if (nums[i] == res) count++;
            else count--;
        }
        return res;
    }
};

// 利用分治算法
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        return majorityElementCru(nums, 0, nums.size() - 1);
    }

    int majorityElementCru(vector<int>& nums, int lo, int hi) {
        if (lo == hi) return nums[lo];

        int mid = lo + (hi - lo) / 2;
        int majorleft = majorityElementCru(nums, lo, mid);
        int majorright = majorityElementCru(nums, mid + 1, hi);
        
        if (majorleft == majorright) return majorright;
        if (countElement(nums, lo, hi, majorleft) > (hi - lo + 1) / 2) return majorleft;
        if (countElement(nums, lo, hi, majorright) > (hi - lo + 1) / 2) return majorright;

        return -1; // 此处可以返回任意一个数，在数组总是存在多数元素的情况下不会影响结果
    }

    int countElement(vector<int>& nums, int lo, int hi, int element) {
        int count = 0;
        for (int i = lo; i <= hi; ++i) {
            if (nums[i] == element) count++;
        }
        return count;
    }
};