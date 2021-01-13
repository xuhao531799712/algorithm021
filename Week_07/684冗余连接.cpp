class unionset {
public:
    unionset(int _size) {
        point.resize(_size);
        for (int i = 0; i < _size; ++i) {
            point[i] = i;
        }
    }

    int find(int i) {
        while (point[i] != i) {
            point[i] = point[point[i]];
            i = point[i];
        }
        return i;
    }

    int connect(int i, int j) {
        int fa_i = find(i), fa_j = find(j);
        if (fa_i == fa_j) return 0;
        else {
            point[fa_j] = fa_i;
            return 1;
        }
    }

    vector<int> point;
};
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> ans;
        int size = edges.size() + 1;
        unionset uni(size);
        for (auto edge : edges) {
            if (uni.connect(edge[0], edge[1]) == 0) {
                ans = edge;
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};