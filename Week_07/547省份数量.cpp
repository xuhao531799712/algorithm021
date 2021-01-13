class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<int> pro(n);
        for (int i = 0; i < n; ++i) pro[i] = i;

        int ans = n; // 省份数量一开始初始化为城市数量
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isConnected[i][j]) {
                    ans -= connect(pro, i, j);
                }
            }
        }

        return ans;
    }

    int find(vector<int>& pro, int i) {
        while (pro[i] != i) {
            pro[i] = pro[pro[i]];
            i = pro[i];
        }
        return i;
    }

    int connect(vector<int>& pro, int i, int j) {
        // 如果两城市原本相连，则返回 0
        // 如果两城市本来未相连，则将其相连，并返回 1，表示少了一个省份计数
        int fa_i = find(pro, i);
        int fa_j = find(pro, j);
        if (fa_i == fa_j) return 0;
        pro[fa_j] = fa_i;
        return 1;
    }
};