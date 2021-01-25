class Solution {
public:
    void reverseString(vector<char>& s) {
        int n = s.size() - 1;
        int half = (n >> 1);
        for (int i = 0; i <= half; ++i) {
            swap(s[i], s[n - i]);
        }
    }
};