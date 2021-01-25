class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        int res = 0;
        unordered_set<char> mm(jewels.begin(), jewels.end());
        for (auto stone : stones) {
            if (mm.count(stone)) ++res;
        }
        return res;
    }
};