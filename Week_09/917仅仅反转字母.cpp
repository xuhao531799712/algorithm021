class Solution {
public:
    string reverseOnlyLetters(string S) {
        int left = 0, right = S.size() - 1;
        while (left < right) {
            while (left < right && !(S[left] >= 'a' && S[left] <= 'z' || S[left] >= 'A' && S[left] <= 'Z')) ++left;
            while (left < right && !(S[right] >= 'a' && S[right] <= 'z' || S[right] >= 'A' && S[right] <= 'Z')) --right;
            swap(S[left], S[right]);
            ++left;
            --right;
        }
        return S;
    }
};