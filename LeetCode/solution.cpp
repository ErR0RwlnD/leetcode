//
// Created by YU on 2022/10/6.
//
#include <unordered_set>
#include "string"
#include "iostream"
#include "vector"
#include "map"
#include "unordered_map"
#include "stack"
#include "cstring"
#include "algorithm"
#include "queue"
#include "set"

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

class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
            : val(_val), left(_left), right(_right), next(_next) {}
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
        if (dots == 3) {
            if (validIP(s.substr(start))) {
                res.push_back(cur + s.substr(start));
            }
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
                if (s1[i - 1] == s3[i + j - 1] && s2[j - 1] == s3[i + j - 1]) {
                    dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]);
                } else if (s1[i - 1] == s3[i + j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else if (s2[j - 1] == s3[i + j - 1]) {
                    dp[i][j] = dp[i][j - 1];
                } else {
                    dp[i][j] = false;
                }
            }
        }

        return dp[s1.length()][s2.length()];
    }
};

//99
class RecoverBinarySearchTree {
public:
    void recoverTree(TreeNode *root) {
        inorder(root);
        swap(r1->val, r2->val);
    }

private:
    TreeNode *r1 = nullptr, *r2 = nullptr, *pre = new TreeNode(INT_MIN);

    void inorder(TreeNode *root) {
        if (root == nullptr) {
            return;
        }

        inorder(root->left);
        if (r1 == nullptr && root->val < pre->val) {
            r1 = pre;
        }
        if (r1 != nullptr && root->val < pre->val) {
            r2 = root;
        }
        pre = root;
        inorder(root->right);
    }
};

//103
class BinaryTreeZigzagLevelOrderTraversal {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
        if (root == nullptr) {
            return {};
        }

        bool right = true;
        vector<vector<int>> res;
        queue<TreeNode *> layer;
        layer.push(root);
        while (!layer.empty()) {
            int size = layer.size();
            vector<int> temp(size, 0);
            for (int i = 0; i < size; i++) {
                auto f = layer.front();
                layer.pop();
                if (f->left != nullptr) {
                    layer.push(f->left);
                }
                if (f->right != nullptr) {
                    layer.push(f->right);
                }
                if (right) {
                    temp[i] = f->val;
                } else {
                    temp[size - i - 1] = f->val;
                }
            }
            res.push_back(temp);
            right = !right;
        }

        return res;
    }
};

//105
class ConstructBinaryTreefromPreorderandInorderTraversal {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return creatTree(preorder, inorder, 0, inorder.size() - 1);
    }

private:
    int preIdx = 0;

    TreeNode *creatTree(vector<int> &preorder, vector<int> &inorder, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        auto node = new TreeNode(preorder[preIdx++]);
        int pos = 0;
        for (int i = start; i <= end; i++) {
            if (inorder[i] == node->val) {
                pos = i;
                break;
            }
        }

        node->left = creatTree(preorder, inorder, start, pos - 1);
        node->right = creatTree(preorder, inorder, pos + 1, end);
        return node;
    }
};

//106
class ConstructBinaryTreefromInorderandPostorderTraversal {
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        postIdx = postorder.size() - 1;
        return creatTree(inorder, postorder, 0, inorder.size() - 1);
    }

private:
    int postIdx = 0;

    TreeNode *creatTree(vector<int> &inorder, vector<int> &postorder, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        auto node = new TreeNode(postorder[postIdx--]);
        int pos = 0;
        for (int i = start; i <= end; i++) {
            if (inorder[i] == node->val) {
                pos = i;
                break;
            }
        }

        node->right = creatTree(inorder, postorder, pos + 1, end);
        node->left = creatTree(inorder, postorder, start, pos - 1);
        return node;
    }
};

//334
class IncreasingTripletSubsequence {
    bool increasingTriplet(vector<int> &nums) {
        if (nums.size() < 3)
            return false;
        int left = INT_MAX, mid = INT_MAX;
        for (auto n: nums) {
            if (n > mid) {
                return true;
            }
            if (n < mid && n > left) {
                mid = n;
            }
            if (n < left) {
                left = n;
            }
        }
        return false;
    }
};

//109
class ConvertSortedListtoBinarySearchTree {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }

        auto p = findMid(head);
        auto root = new TreeNode(p.second->val);

        if (p.first != nullptr) {
            p.first->next = nullptr;
            root->left = sortedListToBST(head);
        }

        root->right = sortedListToBST(p.second->next);
        return root;
    }

private:
    pair<ListNode *, ListNode *> findMid(ListNode *head) {
        if (head == nullptr, head->next == nullptr) {
            return {nullptr, head};
        }

        ListNode *slow = head;
        ListNode *fast = head->next;
        ListNode *pre = nullptr;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            pre = slow;
            slow = slow->next;
        }

        return {pre, slow};
    }
};

//113
class PathSumII {
public:
    vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
        vector<int> path;
        dfs(root, path, 0, targetSum);
        return res;
    }

private:
    void dfs(TreeNode *root, vector<int> &path, int current, const int &target) {
        if (root == nullptr) {
            return;
        }

        current += root->val;
        path.push_back(root->val);
        if (target == current && root->left == nullptr && root->right == nullptr) {
            res.push_back(path);
            path.pop_back();
            return;
        }

        dfs(root->left, path, current, target);
        dfs(root->right, path, current, target);
        path.pop_back();
    }

    vector<vector<int>> res;
};

//114
class FlattenBinaryTreetoLinkedList {
public:
    void flatten(TreeNode *root) {
        TreeNode *cur = root;
        while (cur != nullptr) {
            if (cur->left != nullptr) {
                TreeNode *runner = cur->left;
                while (runner->right != nullptr) {
                    runner = runner->right;
                }
                runner->right = cur->right;
                cur->right = cur->left;
                cur->left = nullptr;
            }
            cur = cur->right;
        }
    }
};

//115
class DistinctSubsequences {
public:
    int numDistinct(string s, string t) {
        vector<unsigned int> dp(t.length() + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < s.length(); i++) {
            for (int j = t.length(); j > 0; j--) {
                if (s[i] == t[j - 1]) {
                    dp[j] = dp[j] + dp[j - 1];
                }
            }
        }
        return dp[t.length()];
    }
};

//116
class PopulatingNextRightPointersinEachNode {
public:
    Node *connect(Node *root) {
        if (root == nullptr) {
            return nullptr;
        }

        if (root->left != nullptr) {
            root->left->next = root->right;
        }
        if (root->right != nullptr && root->next != nullptr) {
            root->right->next = root->next->left;
        }
        connect(root->left);
        connect(root->right);
        return root;
    }
};

//117
class PopulatingNextRightPointersinEachNodeII {
public:
    Node *connect(Node *root) {
        if (root == nullptr) {
            return nullptr;
        }

        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto node = q.front();
                q.pop();
                if (i == n - 1) {
                    node->next = nullptr;
                } else {
                    node->next = q.front();
                }

                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
        }

        return root;
    }
};

//122
class BestTimetoBuyandSellStockII {
    int maxProfit(vector<int> &prices) {
        int balance = 0, hold = INT_MIN;
        for (auto p: prices) {
            balance = max(balance, hold + p);
            hold = max(hold, balance - p);
        }
        return balance;
    }

    int maxProfit2(vector<int> &prices) {
        int profit = 0;
        for (int i = 0; i < prices.size() - 1; i++) {
            if (prices[i] < prices[i + 1]) {
                profit += (prices[i + 1] - prices[i]);
            }
        }
        return profit;
    }
};

//123
class BestTimetoBuyandSellStockIII {
    int maxProfit(vector<int> &prices) {
        if (prices.size() <= 1)
            return 0;
        vector<int> left(prices.size(), 0);
        vector<int> right(prices.size(), 0);
        int n = prices.size();
        int leftMin = prices[0], rightMax = prices[n - 1];
        for (int i = 1; i < n; i++) {
            leftMin = min(prices[i], leftMin);
            left[i] = max(left[i - 1], prices[i] - leftMin);
            rightMax = max(prices[n - i - 1], rightMax);
            right[n - i - 1] = max(right[n - i], rightMax - prices[n - i - 1]);
        }
        int profit = INT_MIN;
        for (int i = 0; i < n; i++) {
            profit = max(profit, left[i] + right[i]);
        }
        return profit;
    }

    int maxProfit2(vector<int> &prices) {
        int buy1 = INT_MAX, profit1 = INT_MIN;
        int buy2 = INT_MAX, profit2 = INT_MIN;
        for (auto p: prices) {
            buy1 = min(buy1, p);
            profit1 = max(profit1, p - buy1);
            buy2 = min(buy2, p - profit1);
            profit2 = max(profit2, p - buy2);
        }
        return profit2;
    }
};

//124
class BinaryTreeMaximumPathSum {
public:
    int maxPathSum(TreeNode *root) {
        maxGain(root);
        return maxSum;
    }

private:
    int maxGain(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        int left = max(maxGain(root->left), 0);
        int right = max(maxGain(root->right), 0);
        maxSum = max(maxSum, left + right + root->val);
        return root->val + max(left, right);
    }

    int maxSum = INT_MIN;
};

//127
class WordLadder {
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        if (std::find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
            return 0;
        }
        queue<string> q;
        q.push(endWord);
        wordList.erase(std::find(wordList.begin(), wordList.end(), endWord));
        wordList.push_back(beginWord);
        int len = 0;

        while (!q.empty()) {
            len++;
            int n = q.size();
            for (int i = 0; i < n; i++) {
                string cur = q.front();
                q.pop();
                auto it = wordList.begin();
                while (it != wordList.end()) {
                    if (differOne(*it, cur)) {
                        if (*it == beginWord) {
                            return len + 1;
                        }
                        q.push(*it);
                        it = wordList.erase(it);
                    } else {
                        it++;
                    }
                }
            }
        }

        return 0;
    }

private:
    bool differOne(const string &s1, const string &s2) {
        int dif = 0;
        for (int i = 0; i < s1.length(); i++) {
            if (dif >= 2) {
                return false;
            }
            if (s1[i] != s2[i]) {
                dif++;
            }
        }

        return dif == 1;
    }
};

//126
class WordLadderII {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        if (std::find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
            return {};
        }
        vector<vector<string>> nodes;
        queue<string> forward;
        forward.push(beginWord);
        bool end = false;
        while (!forward.empty()) {
            int n = forward.size();
            vector<string> temp;
            for (int i = 0; i < n; i++) {
                string top = forward.front();
                forward.pop();
                auto it = wordList.begin();
                while (it != wordList.end()) {
                    if (differOne(*it, top)) {
                        if (*it == endWord) {
                            end = true;
                            break;
                        }
                        temp.push_back(*it);
                        forward.push(*it);
                        it = wordList.erase(it);
                    } else {
                        it++;
                    }
                }
                if (end) {
                    break;
                }
            }
            if (end) {
                break;
            }
            nodes.push_back(temp);
        }

        if (!end) {
            return {};
        }
        if (nodes.empty()) {
            return {{beginWord, endWord}};
        }
        deque<string> path = {endWord};
        DFS(nodes, 1, path, beginWord);
        return res;
    }

private:
    vector<vector<string>> res;

    void DFS(vector<vector<string>> &nodes, int level, deque<string> &path, const string &beginWord) {
        int n = nodes.size();
        if (level == n + 1) {
            if (differOne(beginWord, path.front())) {
                path.push_front(beginWord);
                res.emplace_back(path.begin(), path.end());
                path.pop_front();
            }
        } else {
            for (const auto &w: nodes[n - level]) {
                if (differOne(w, path.front())) {
                    path.push_front(w);
                    DFS(nodes, level + 1, path, beginWord);
                    path.pop_front();
                }
            }
        }
    }

    bool differOne(const string &s1, const string &s2) {
        int dif = 0;
        for (int i = 0; i < s1.length(); i++) {
            if (dif >= 2) {
                return false;
            }
            if (s1[i] != s2[i]) {
                dif++;
            }
        }

        return dif == 1;
    }
};

//129
class SumRoottoLeafNumbers {
public:
    int sumNumbers(TreeNode *root) {
        passN(root, 0);
        return sumN;
    }

private:
    int sumN;

    void passN(TreeNode *root, int n) {
        if (root->left == nullptr && root->right == nullptr) {
            sumN += (root->val + n * 10);
        } else {
            if (root->left != nullptr) {
                passN(root->left, root->val + n * 10);
            }
            if (root->right != nullptr) {
                passN(root->right, root->val + n * 10);
            }
        }
    }
};

//131
class PalindromePartitioning {
public:
    vector<vector<string>> partition(string s) {
        vector<string> path;
        rec(s, path, 0);
        return res;
    }

private:
    vector<vector<string>> res;

    void rec(const string &s, vector<string> &path, int start) {
        if (start == s.length()) {
            res.push_back(path);
            return;
        }

        for (int i = start; i < s.length(); i++) {
            if (ispalindrome(s, start, i)) {
                path.push_back(s.substr(start, i - start + 1));
                rec(s, path, i + 1);
                path.pop_back();
            }
        }
    }

    bool ispalindrome(const string &s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end]) {
                return false;
            }
            start++;
            end--;
        }
        return true;
    }
};

//132
class PalindromePartitioningII {
public:
    int minCut(string s) {
        vector<int> dp(s.length(), -1);
        return partCut(s, 0, dp);
    }

private:
    int partCut(const string &s, int start, vector<int> &dp) {
        if (start >= s.length() - 1 || ispalindrome(s, start, s.length() - 1)) {
            return 0;
        }
        if (dp[start] != -1) {
            return dp[start];
        }

        int res = INT_MAX;
        for (int i = start; i < s.length(); i++) {
            if (ispalindrome(s, start, i)) {
                res = min(res, partCut(s, i + 1, dp) + 1);
            }
        }

        return dp[start] = res;
    }

    bool ispalindrome(const string &s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end]) {
                return false;
            }
            start++;
            end--;
        }
        return true;
    }
};

//133
class CloneGraph {
public:
    class Node {
    public:
        int val;
        vector<Node *> neighbors;

        Node() {
            val = 0;
            neighbors = vector<Node *>();
        }

        Node(int _val) {
            val = _val;
            neighbors = vector<Node *>();
        }

        Node(int _val, vector<Node *> _neighbors) {
            val = _val;
            neighbors = _neighbors;
        }
    };

    Node *cloneGraph(Node *node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->neighbors.size() == 0) {
            return new Node(node->val);
        }
        return DFS(node);
    }

private:
    unordered_map<Node *, Node *> mp;

    Node *DFS(Node *root) {
        vector<Node *> neighbour;
        Node *clone = new Node(root->val);
        mp[root] = clone;
        for (auto n: root->neighbors) {
            if (mp.find(n) != mp.end()) {
                neighbour.push_back(mp[n]);
            } else {
                neighbour.push_back(DFS(n));
            }
        }
        clone->neighbors = neighbour;
        return clone;
    }
};

//237
class DeleteNodeinaLinkedList {
public:
    void deleteNode(ListNode *node) {
        ListNode *n = node->next;
        *node = *n;
        delete n;
    }
};

//134
class GasStation {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int diff = 0, cur = 0, total = 0, start = 0;
        for (int i = 0; i < gas.size(); i++) {
            diff = gas[i] - cost[i];
            cur += diff;
            total += diff;
            if (cur < 0) {
                start = i + 1;
                cur = 0;
            }
        }
        if (total < 0) {
            return -1;
        }
        return start;
    }
};

//135
class Candy {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size();
        vector<int> up(n, 1), down(n, 1);
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                up[i] = up[i - 1] + 1;
            }
            if (ratings[n - i - 1] > ratings[n - i]) {
                down[n - i - 1] = down[n - i] + 1;
            }
        }

        int total = 0;
        for (int i = 0; i < n; i++) {
            total += max(up[i], down[i]);
        }

        return total;
    }
};

//137
class SignleNumberII {
public:
    int singleNumber(vector<int> &nums) {
        int single = 0;
        for (int i = 0; i < 32; i++) {
            int sum = 0;
            for (auto n: nums) {
                if (n & (1 << i)) {
                    sum++;
                }
            }
            if (sum % 3 == 1) {
                single = (single | (1 << i));
            }
        }
        return single;
    }
};

//139
class WordBreak {
public:
    bool wordBreak(string s, vector<string> &wordDict) {
        vector<bool> dp(s.length(), false);
        for (int i = 0; i < s.length(); i++) {
            if (i > 0 && !dp[i - 1]) {
                continue;
            }

            string temp;
            for (int j = i; j < s.length(); j++) {
                temp += s[j];
                if (find(wordDict.begin(), wordDict.end(), temp) != wordDict.end()) {
                    dp[j] = true;
                }
            }
        }

        return dp.back();
    }
};

//1531
class StringCompressionII {
public:
    int getLengthOfOptimalCompression(string s, int k) {
        memset(dp, -1, sizeof(dp));
        return DFS(s, 0, k);
    }

private:
    int dp[101][101];

    int DFS(string &s, int left, int k) {
        int n = k;
        if (s.size() <= left + n) {
            return 0;
        }
        if (dp[left][n] >= 0) {
            return dp[left][n];
        }
        int res = n ? DFS(s, left + 1, n - 1) : INT_MAX / 2;
        int count = 1;
        for (int i = left + 1; i <= s.size(); i++) {
            res = min(res, DFS(s, i, n) + 1 + (count >= 100 ? 3 : (count >= 10 ? 2 : (count > 1 ? 1 : 0))));
            if (i == s.size()) {
                break;
            }
            if (s[i] == s[left]) {
                count++;
            } else if (--n < 0) {
                break;
            }
        }
        return dp[left][k] = res;
    }
};

//140
class WordBreakII {
public:
    vector<string> wordBreak(string s, vector<string> &wordDict) {
        int n = s.size();
        unordered_set<string> wd(wordDict.begin(), wordDict.end());
        vector<vector<string>> dp(n);

        for (int i = 0; i < n; i++) {
            for (int j = i; j >= 0; j--) {
                string temp = s.substr(j, i - j + 1);
                if (wd.find(temp) != wd.end()) {
                    if (j == 0) {
                        dp[i].push_back(temp);
                    } else {
                        for (const auto &item: dp[j - 1]) {
                            dp[i].push_back(item + " " + temp);
                        }
                    }
                }
            }
        }

        return dp[n - 1];
    }
};

//142
class LinkedListCycleII {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }
        auto slow = head, fast = head;
        bool found = false;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) {
                found = true;
                break;
            }
        }
        if (found != true) {
            return nullptr;
        }

        auto temp = head;
        while (temp != slow) {
            temp = temp->next;
            slow = slow->next;
        }

        return temp;
    }
};

int main() {
    auto solution = new StringCompressionII;
    string s = "aaabcccd";
    solution->getLengthOfOptimalCompression(s, 2);
}