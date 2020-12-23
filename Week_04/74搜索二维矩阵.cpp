// 直接把整个二维矩阵看做一个一维矩阵，在比较值大小的时候做一下坐标转换
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (!matrix.size() || !matrix[0].size()) return false;
        int m = matrix.size(), n = matrix[0].size();
        int left = 0, right = m * n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            // i,j 即 mid 对应的点在二维矩阵中的位置
            int i = mid / n, j = mid % n;
            if (matrix[i][j] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return matrix[left / n][left % n] == target;
    }
};

// 本题还可以使用从右上角或者左下角的元素开始逐个搜索的方法
// 但是最适用于上下两行间具有不严格的大小关系时
// 本次大小关系强烈，使用二分法最好