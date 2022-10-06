//
// Created by YU on 2022/10/6.
//
#include "string"
#include "iostream"
#include "vector"

using namespace std;

class ValidNumber65 {
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

class PlusOne66 {
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

class TextJustification {
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        vector<int> length = {};
        int sumL = 0, count = 0, minL = -1;
        for (const auto &w: words) {
            sumL += w.length();
            minL += w.length();
            minL++;
            count++;
            if (minL <= maxWidth) {
                count++;
                continue;
            } else {
                length.push_back(sumL);
                length.push_back(count);
                sumL = 0;
                count = 0;
                minL = -1;
            }
        }

        vector<string> res = {};
        string oneLine = "";

        for (int i = 0, j = 0; i < length.size() / 2; i += 2) {
            oneLine +=
        }

    }
};

int main() {
    auto solution = new PlusOne66();
    vector<int> num = {9, 9, 9};
    for (auto n: solution->plusOne(num))
        cout << n << endl;
}