//
// Created by YU on 2022/10/6.
//
#include "string"
#include "iostream"
#include "vector"
#include "map"
#include "unordered_map"
#include "stack"
#include "cstring"
#include "algorithm"

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//65
class ValidNumber {
public:
    bool isNumber(string s) {
        return checkSinged(s);
    }

private:
    bool checkSinged(string s) {
        if (s.empty())
            return false;
        if (s[0] == '+' || s[0] == '-') {
            if (s.length() == 1)
                return false;
            return checkExponent(s.substr(1), 'e') || checkExponent(s.substr(1), 'E');
        }
        return checkExponent(s, 'e') || checkExponent(s, 'E');
    }

    bool checkExponent(string s, char e) {
        if (s.empty())
            return false;
        size_t find = s.find(e);
        if (find != string::npos) {
            return isDecimal(s.substr(0, find)) && isInteger(s.substr(find + 1));
        } else
            return isDecimal(s);
    }

    bool isDecimal(string s) {
        if (s.empty())
            return false;
        size_t find = s.find('.');
        if (find != string::npos) {
            if (s.substr(find + 1).find('.') != string::npos)
                return false;
            else {
                if (find == 0)
                    return isDigitsStar(s.substr(1));
                else if (find == (s.length() - 1))
                    return isDigitsStar(s.substr(0, find));
                else
                    return isDigitsStar(s.substr(0, find)) && isDigitsStar(s.substr(find + 1));
            }
        }
        return isDigitsStar(s);
    }

    bool isInteger(string s) {
        if (s.empty())
            return false;
        if (s[0] == '+' || s[0] == '-') {
            return isDigitsStar(s.substr(1));
        }
        return isDigitsStar(s);
    }

    bool isDigitsStar(string s) {
        if (s.empty())
            return false;
        for (auto c: s) {
            if (c > '9' || c < '0')
                return false;
        }
        return true;
    }
};

//66
class PlusOne {
public:
    vector<int> plusOne(vector<int> &digits) {
        bool plusOne = true;
        for (auto it = digits.rbegin(); it != digits.rend(); it++) {
            if (*it == 9) {
                if (plusOne) {
                    *it = 0;
                    plusOne = true;
                } else {
                    plusOne = false;
                }
            } else {
                if (plusOne) {
                    *it += 1;
                }
                plusOne = false;
            }
        }

        if (plusOne) {
            digits.insert(digits.begin(), 1);
        }

        return digits;
    }
};

//68
class TextJustification {
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        vector<int> length = {};
        int sumL = 0, count = 0, minL = -1;
        for (const auto &w: words) {
            minL += (w.length() + 1);
            if (minL <= maxWidth) {
                sumL += w.length();
                count++;
                continue;
            } else {
                if (count == 0) {
                    length.push_back(w.length());
                    length.push_back(0);
                    sumL = 0;
                    count = 0;
                    minL = -1;
                } else {
                    length.push_back(sumL);
                    length.push_back(count - 1);
                    sumL = w.length();
                    count = 1;
                    minL = w.length();
                }

            }
        }
        length.push_back(sumL);
        length.push_back(count - 1);

        vector<string> res = {};
        string oneLine = "";

        int j = 0;
        for (int i = 0; i < length.size() - 2; i += 2) {
            if (length[i + 1] == 0) {
                string white(maxWidth - length[i], ' ');
                res.push_back(words[j] + white);
                j++;
                continue;
            }

            oneLine += words[j];
            j++;
            int resL = maxWidth - length[i];
            int space = resL / length[i + 1];

            int m = resL - space * length[i + 1];
            for (int k = 0; k < m; k++) {
                string white(space + 1, ' ');
                oneLine += white;
                oneLine += words[j];
                j++;
            }
            for (int k = 0; k < length[i + 1] - m; k++) {
                string white(space, ' ');
                oneLine += white;
                oneLine += words[j];
                j++;
            }
            res.push_back(oneLine);
            oneLine = "";
        }
        oneLine += words[j];
        for (int k = j + 1; k < words.size(); k++) {
            oneLine += " ";
            oneLine += words[k];
        }
        int whiteRes = maxWidth - oneLine.length();
        if (whiteRes > 0) {
            string white(whiteRes, ' ');
            oneLine += white;
        }
        res.push_back(oneLine);

        return res;
    }
};

//732
class MyCalendarThree {
public:
    MyCalendarThree() {
        calendar.clear();
        maxCount = -1;
    }

    int book(int start, int end) {
        calendar[start]++;
        calendar[end]--;
        int count = 0;
        for (auto m: calendar) {
            count += m.second;
            maxCount = max(count, maxCount);
        }

        return maxCount;
    }

private:
    map<int, int> calendar;
    int maxCount = -1;
};

//69
class Sqrt {
public:
    int mySqrt(int x) {
        long long int left = 0, right = x, temp = 0;
        while (left <= right) {
            long long int m = (left + right) / 2;
            if (m * m == x)
                return (int) m;
            else if (m * m < x) {
                temp = m;
                left = m + 1;
            } else {
                right = m - 1;
            }
        }
        return (int) temp;
    }
};

//71
class SimplifyPath {
public:
    string simplifyPath(string path) {
        stack<string> st;
        for (auto c = path.begin(); c < path.end(); c++) {
            if (*c == '/')
                continue;
            string temp;
            while (c != path.end() && *c != '/') {
                temp += *c;
                c++;
            }

            if (temp == ".")
                continue;
            else if (temp == "..") {
                if (!st.empty()) {
                    st.pop();
                }
            } else {
                st.push(temp);
            }
        }

        string res;
        while (!st.empty()) {
            res = "/" + st.top() + res;
            st.pop();
        }

        if (res.length() == 0)
            return "/";
        return res;
    }
};

//72
class EditDistance {
public:
    int minDistance(string word1, string word2) {
        memset(dp, -1, sizeof(dp));
        return rec(word1, word2, 0, 0);
    }

private:
    int dp[501][501];

    int rec(string &word1, string &word2, int id1, int id2) {
        if (id1 >= word1.length())
            return word2.length() - id2;
        if (id2 >= word2.length())
            return word1.length() - id1;
        if (word1[id1] == word2[id2])
            return rec(word1, word2, id1 + 1, id2 + 1);

        if (dp[id1][id2] != -1)
            return dp[id1][id2];

        int op0 = 0, op1 = 0, op2 = 0;
        op0 = 1 + rec(word1, word2, id1 + 1, id2 + 1);
        op1 = 1 + rec(word1, word2, id1 + 1, id2);
        op2 = 1 + rec(word1, word2, id1, id2 + 1);
        dp[id1][id2] = min({op0, op1, op2});
        return dp[id1][id2];
    }
};

//73
class SetMatrixZeros {
public:
    void setZeroes(vector<vector<int>> &matrix) {
        bool col0 = false;
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i][0] == 0) {
                col0 = true;
            }
            for (int j = 1; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for (int i = matrix.size() - 1; i >= 0; i--) {
            for (int j = 1; j < matrix[0].size(); j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (col0) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

//74
class Searcha2DMatrix {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int row = 0, col = matrix[0].size() - 1;
        while (row < matrix.size() && col >= 0) {
            int cur = matrix[row][col];
            if (cur > target) {
                col--;
            } else if (cur < target) {
                row++;
            } else {
                return true;
            }
        }

        return false;
    }
};

//75
class SortColor {
public:
    void sortColors(vector<int> &nums) {
        int left = 0, mid = 0, right = nums.size() - 1;
        while (mid <= right) {
            if (nums[mid] == 0) {
                swap(nums[left], nums[mid]);
                left++;
                mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                swap(nums[mid], nums[right]);
                mid++;
                right--;
            }
        }
    }
};

//76
class MinimumWindowSubstring {
public:
    string minWindow(string s, string t) {
        int m = s.length(), n = t.length();
        unordered_map<char, int> mp;
        int res = INT_MAX, start = 0;
        for (auto c: t) {
            mp[c]++;
        }

        int count = mp.size();
        int i = 0, j = 0;
        while (j < m) {
            mp[s[j]]--;
            if (mp[s[j]] == 0) {
                count--;
            }
            while (count == 0) {
                if (res > j - i + 1) {
                    res = j - i + 1;
                    start = i;
                }
                mp[s[i]]++;
                if (mp[s[i]] > 0) {
                    count++;
                }
                i++;
            }
            j++;
        }

        if (res == INT_MAX)
            return "";
        else
            return s.substr(start, res);
    }
};


//16
class _3SumCloest {
public:
    int threeSumClosest(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        int res = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < nums.size() - 2; i++) {
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int sum3 = nums[i] + nums[left] + nums[right];
                if (abs(target - sum3) < abs(target - res)) {
                    res = sum3;
                }
                if (sum3 == target)
                    return sum3;
                else if (sum3 < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return res;
    }
};

//77
class Combinations {
public:
    vector<vector<int>> combine(int n, int k) {
        res.clear();
        vector<int> v = {};
        rec(1, v, n, k);
        return res;
    }

private:
    vector<vector<int>> res;

    void rec(int start, vector<int> &v, int n, int k) {
        if (v.size() == k) {
            res.push_back(v);
            return;
        }

        for (int i = start; i <= n; i++) {
            v.push_back(i);
            rec(i + 1, v, n, k);
            v.pop_back();
        }
    }
};

//79
class WordSearch {
public:
    bool exist(vector<vector<char>> &board, const string &word) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == word[0] && DFS(board, word, 0, i, j))
                    return true;
            }
        }
        return false;
    }

private:
    bool DFS(vector<vector<char>> &board, const string &word, int n, int i, int j) {
        if (n == word.length())
            return true;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[n])
            return false;

        board[i][j] = '0';
        bool status = DFS(board, word, n + 1, i + 1, j) ||
                      DFS(board, word, n + 1, i - 1, j) ||
                      DFS(board, word, n + 1, i, j + 1) ||
                      DFS(board, word, n + 1, i, j - 1);
        board[i][j] = word[n];
        return status;
    }
};

//84
class LargestRetangleInHistogram {
public:
    int largestRectangleArea(vector<int> &heights) {
        stack<int> st;
        int res = 0;
        for (int i = 0; i <= heights.size(); i++) {
            int curHeight = (i == heights.size() ? 0 : heights[i]);
            while (!st.empty() && curHeight < heights[st.top()]) {
                int top = st.top();
                st.pop();
                int width = (st.empty() ? i : i - (st.top() + 1));
                res = max(res, width * heights[top]);
            }
            st.push(i);
        }

        return res;
    }
};

//87
class ScrambleString {
public:
    bool isScramble(string s1, string s2) {
        int n = s1.size();
        if (n != s2.size())
            return false;
        if (s1 == s2)
            return true;
        if (n == 1)
            return false;

        string key = s1 + " " + s2;
        if (mp.find(key) != mp.end())
            return mp[key];

        for (int i = 1; i < n; i++) {
            bool withoutSwap = (isScramble(s1.substr(0, i), s2.substr(0, i)) &&
                                isScramble(s1.substr(i), s2.substr(i)));
            if (withoutSwap)
                return true;

            bool withSwap = (isScramble(s1.substr(0, i), s2.substr(n - i)) &&
                             isScramble(s1.substr(i), s2.substr(0, n - i)));
            if (withSwap)
                return true;
        }

        return mp[key] = false;
    }

private:
    unordered_map<string, bool> mp;
};

//88
class MergeSortedArray {
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                k--;
                i--;
            } else {
                nums1[k] = nums2[j];
                k--;
                j--;
            }
        }

        while (i >= 0) {
            nums1[k] = nums1[i];
            i--;
            k--;
        }
        while (j >= 0) {
            nums1[k] = nums2[j];
            j--;
            k--;
        }
    }
};

//89
class GrayCode {
public:
    vector<int> grayCode(int n) {
        vector<int> v;
        for (int i = 0; i < (1 << n); i++) {
            v.push_back(i ^ (i / 2));
        }

        return v;
    }
};

//90
class SubsetsII {
public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<int> cur;
        vector<vector<int>> res;
        rec(nums, cur, res, 0);
        return res;
    }

private:
    void rec(const vector<int> &nums, vector<int> &cur, vector<vector<int>> &res, int idx) {
        res.push_back(cur);
        for (int i = idx; i < nums.size(); i++) {
            if (i > idx && nums[i] == nums[i - 1])
                continue;
            cur.push_back(nums[i]);
            rec(nums, cur, res, i + 1);
            cur.pop_back();
        }
    }
};

//91
class DecodeWays {
public:
    int numDecodings(string s) {
        int res = 1, last = 1;
        for (int i = s.length() - 1; i >= 0; i--) {
            int cur = (s[i] == '0' ? 0 : res);
            if (i < s.length() - 1 && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
                cur += last;
            }
            last = res;
            res = cur;
        }

        return s.empty() ? 0 : res;
    }
};

//92
class ReverseLinkedListII {
public:
    ListNode *reverseBetween(ListNode *head, int left, int right) {
        if (left == right)
            return head;
        auto newHead = new ListNode(0, head);
        ListNode *pre = newHead, *cur = newHead;
        int i = 1;
        while (i < left) {
            pre = pre->next;
            i++;
        }

        cur = pre->next;
        while (i < right) {
            ListNode *temp = pre->next;
            pre->next = cur->next;
            cur->next = cur->next->next;
            pre->next->next = temp;
            i++;
        }

        return newHead->next;
    }
};

//653
class TwoSumIV {
public:
    bool findTarget(TreeNode *root, int k) {
        if (root->left == nullptr && root->right == nullptr)
            return false;

        inorder(root);
        int left = 0, right = v.size() - 1;
        while (left < right) {
            if (v[left] + v[right] == k)
                return true;
            else if (v[left] + v[right] > k) {
                right--;
            } else {
                left++;
            }
        }

        return false;
    }

private:
    void inorder(TreeNode *root) {
        if (root == nullptr)
            return;

        inorder(root->left);
        v.push_back(root->val);
        inorder(root->right);
    }

    vector<int> v;
};

//1328
class BreakaPalindrome {
public:
    string breakPalindrome(string palindrome) {
        int n = palindrome.length();
        for (int i = 0; i < n / 2; i++) {
            if (palindrome[i] != 'a') {
                palindrome[i] = 'a';
                return palindrome;
            }
        }
        if (n >= 2) {
            palindrome[n - 1] = 'b';
            return palindrome;
        }

        return "";
    }
};

//93
class RestoreIPAddresses {
public:
    vector<string> restoreIpAddresses(string s) {
        string cur;
        rec(s, cur, 0, 0);
        return res;
    }

private:
    vector<string> res;

    void rec(const string &s, string cur, int start, int dots) {
        if (dots == 3 && validIP(s.substr(start))) {
            res.push_back(cur + s.substr(start));
            return;
        }

        for (int i = start; i < s.length() && i < start + 4; i++) {
            if (validIP(s.substr(start, i - start + 1))) {
                cur.push_back(s[i]);
                cur.push_back('.');
                rec(s, cur, i + 1, dots + 1);
                cur.pop_back();
            }
        }
    }

    bool validIP(const string &s) {
        if (s.length() > 3 || s.size() == 0)
            return false;
        if (s[0] == '0' && s.size() > 1)
            return false;
        if (0 <= stoi(s) && stoi(s) <= 255)
            return true;
        return false;
    }
};

//95
class UniqueBinarySearchTreesII {
public:
    vector<TreeNode *> generateTrees(int n) {
        return rec(1, n);
    }

private:
    vector<TreeNode *> rec(int start, int end) {
        if (start > end)
            return {nullptr};
        if (start == end)
            return {new TreeNode(start)};

        vector<TreeNode *> res;
        for (int i = start; i <= end; i++) {
            vector<TreeNode *> left = rec(start, i - 1), right = rec(i + 1, end);
            for (auto l: left) {
                for (auto r: right) {
                    res.push_back(new TreeNode(i, l, r));
                }
            }
        }

        return res;
    }
};

//97
class InterleavingString {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.length() + s2.length() != s3.length()) {
            return false;
        }

        vector<vector<bool>> dp(s1.length() + 1, vector<bool>(s2.length() + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= s1.length(); i++) {
            if (s1[i - 1] == s3[i - 1]) {
                dp[i][0] = dp[i - 1][0];
            } else {
                dp[i][0] = false;
            }
        }
        for (int j = 1; j <= s2.length(); j++) {
            if (s2[j - 1] == s3[j - 1]) {
                dp[0][j] = dp[0][j - 1];
            } else {
                dp[0][j] = false;
            }
        }

        for (int i = 1; i <= s1.length(); i++) {
            for (int j = 1; j <= s2.length(); j++) {
                if (s1[i - 1] == s3[i + j - 1]) {
                    dp[i][j] = (dp[i][j] || dp[i - 1][j]);
                } else if (s2[j - 1] == s3[i + j - 1]) {
                    dp[i][j] = (dp[i][j] || dp[i][j - 1]);
                } else {
                    dp[i][j] = false;
                }
            }
        }

        return dp[s1.length()][s2.length()];
    }
};

int main() {
    auto solution = new InterleavingString;
    cout << solution->isInterleave("ab", "bc", "bbac");
}