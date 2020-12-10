// 200岛屿数量
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        // 正常深度搜索就可以，注意的是图的遍历需要有visited数组
        // 此处不建立专门的visited数组，而在原数组中直接做标记
        if (!grid.size() || !grid[0].size()) return 0;
        int res = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j<grid[0].size(); ++j) {
                if(dfs(i, j, grid)) ++res;
            }
        }
        return res;
    }

    bool dfs(int i, int j, vector<vector<char>>& grid) {
        // 深度搜索遍历函数
        if (grid[i][j] == '0') return false;
        grid[i][j] = '0';
        if (i-1 >= 0) dfs(i-1, j, grid);
        if (j-1 >= 0) dfs(i, j-1, grid);
        if (i+1 < grid.size()) dfs(i+1, j, grid);
        if (j+1 < grid[0].size()) dfs(i, j+1, grid);
        return true;
    }
};