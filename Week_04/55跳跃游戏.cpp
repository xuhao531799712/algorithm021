class Solution {
public:
    bool canJump(vector<int>& nums) {
        int farestpos = 0;
        for (int i = 0; i < nums.size() && i <= farestpos; ++i) {
            farestpos = max(farestpos, i + nums[i]);
        }
        return farestpos >= nums.size() - 1;
    }
};
///////////////////////////////////////////////////
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int farestpos = 0;
        for (int i = 0; i < nums.size() && i <= farestpos; ++i) {
            farestpos = max(farestpos, i + nums[i]);
            if (farestpos >= nums.size() - 1) return true;
        }
        return false;
    }
};