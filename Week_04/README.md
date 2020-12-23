# 第四周笔记

## 关于深度优先遍历与广度优先遍历

一个注意点是，如果情形是求类似于树的“最小”深度，那么这种情形层序遍历也就是广度优先遍历时优于深度优先遍历的。

因为广度优先遍历在搜索到最小深度层时就可以停止搜索，搜索的节点少；而深度优先遍历需要遍历完所有的节点才可以知道最小深度为多少，当然可以对其进行优化，使得在遍历某棵子树时，如果遍历深度超过了当前已知的最小深度，就直接停止本树子树的搜索开始下一个子树，也就是进行剪枝，但这种做法也只是会让深度优先遍历接近广度优先遍历的节点搜索量，而不会少于。

## 能用二分查找的三个条件

1.整个搜索空间上的元素具有单调性

2.搜索空间有界

3.对空间中的元素可以通过索引值直接访问

## 二分查找的模板

二分查找有很多种写法，在循环判定处有使用 ```while (left <= right)``` 和使用 ```while (left < right)``` 的区别；

在 left 和 right 更新处有使用 ```left = mid + 1; right = mid - 1;``` 以及 ```left = mid; right = mid - 1;``` 和 ```left = mid + 1; right = mid;``` 的区别；

在 mid 的求值处有使用 ``` mid = left + (right - left) / 2 ``` 和 ``` mid = left + (right - left + 1) / 2 ``` 的区别。

那么以上三处的这些不同的写法有什么优劣呢?

在循环判定处，```while (left <= right)``` 的循环退出后，left > right，此时已然要根据条件去判断搜索的 target 值时出现在 left 处还是 right 处，而 ```while (left < right)``` 的循环退出后，left == right，此时搜索空间只有一个值，便一定是所搜索的 target 值。故后者会相对前者有一定的便利性。

而在 left、right 的更新处使用的更新方式与 mid 的求值方式也是一一对应的。

此处要注意二分查找的搜索范围更新的原则：1.确保每次迭代，搜索范围都会变小；2.确保每次迭代，target 始终在搜索范围内。只要满足这两点进行迭代，最后循环一定会退出，且可以得到结果。

那么为了满足这两点，就可以得到 ``` mid = left + (right - left) / 2 ``` 就应该与 ```left = mid - 1; right = mid;``` 搭配；而 ``` mid = left + (right - left + 1) / 2 ``` 就应该与 ```left = mid + 1; right = mid;``` 搭配。而 ```left = mid + 1; right = mid - 1;``` 容易使得 right < left ，所以不便与 ```while (left < right)``` 搭配。

那么得到的我需要牢记的模板为：

```cpp
int binarySearch(const vector<int>& nums, int target) {
    int left = 0, right = (int)nums.size()-1;

    while (left < right) {
        int mid = left + (right - left + 1)/ 2;
        if (nums[mid] <= target) left = mid;
        else right = mid - 1;
    }

    return left;
}
```

上面的 ``` if (nums[mid] <= target) ``` 中的判定条件，使用 < 还是 <= 都视题目情景可以灵活变动，但也都影响了下面 left 和 right 的更新方式（为了保证 target 维持在搜索空间里），也就会影响 mid 的计算方式，所有这些都是一体的，都正确才可以得到正确的结果。

## 有关贪心算法和动态规划

贪心算法与动态规划的不同在于它对每个子问题的解决方案都做出选择，不能回退，而动态规划则会保存以前的运算结果，并根据以前的结果对当前进行选择，有回退功能。

以本周作业 leetcode 45 跳跃游戏 这一题为例：

```cpp
// 方法一： 超时做法，动态规划
// 时间复杂度 O(n^2) 空间复杂度 O(n)
class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> dp(nums.size(), INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (dp[i] == INT_MAX) continue; // 本位置不可达
            for (int j = 1; j <= nums[i]; ++j) {
                if (i + j >= nums.size()) break;
                dp[i + j] = min(dp[i + j], dp[i] + 1);
            }
        }
        return dp[nums.size() - 1];
    }
};

// 方法二：贪心做法
// 时间复杂度 O(n) 空间复杂度 O(1)
class Solution {
public:
    int jump(vector<int>& nums) {
        int farest = 0, count = 0, end = 0;
        for (int i = 0; i < nums.size() - 1; ++i) {
            farest = max(farest, i + nums[i]);
            if (i == end) {
                end = farest;
                count++;
            }
        }
        return count;
    }
};
```

以上的方法一dp做法就像课程说的那样，记录了过程中每一个步骤的值，实际上计算出了到达所有位置的最小步数，并且会不停地通过新计算的本位置之前其他位置的值来更新本位置的值，也就是有回退功能。

但本题只需要对最后一个位置的情况进行计算，所以使用此dp做法复杂度偏高。

而用贪心算法，每次只记录一个对跳到最后位置最快的值就可以了，这样就只得到了跳到最后位置的最短路径中的各个途经点它们分别的最短路径长度，省略了其他无关点。但是要确保每一步一次计算就得到最优值，即要得到局部最优值。

如果可以对贪心的正确性进行验证，那么可以使用贪心算法进行求解的问题，贪心算法将是其时间复杂度最低的解法；而如果题目没法满心贪心的正确性，就需要使用动态规划来满足解的正确性了。

## 课后作业

题目：使用二分查找，寻找一个半有序数组 [4, 5, 6, 7, 0, 1, 2] 中间无序的地方

说明：同学们可以将自己的思路、代码写在学习总结中

本作业同 leetcode 153 寻找旋转排序数组中的最小值非常类似，不同处就是本题返回索引值，而153返回元素值

```cpp
class Solution {
public:
    int findMinIndex(vector<int>& nums) {
        // 本函数的作用为返回断裂处的右索引值，也就是数组中最小的数所在的索引
        if (nums[0] < nums[nums.size() - 1]) // 判断是否有断点
            return -1; // 没有断点就返回 -1
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                // 翻转点发生在本点或右侧
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};
```
