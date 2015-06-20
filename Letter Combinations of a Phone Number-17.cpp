/*
Letter Combinations of a Phone Number

Given a digit string, return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below.
1:     2:   abc    3:   def    4:  ghi    5: jkl    6: mno    7: pqrs

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.

题目链接: https://leetcode.com/problems/letter-combinations-of-a-phone-number/

一句话总结:  这道题挺不错的!   虽然说还是Combinations (靠depth控制dfs深度), 但这题特殊在k=N.  所以不在需要循环!   而是每一次都有3种选择  O(3^n)

                   方法有多种，可以用出dfs写出N重循环;  也可以直接用循环……
                   比如“234”这个字符串，我可以先将0...1的所有排列找到-->{"a", "b", "c"}。
                   再进一步将0...2的所有排列找到-->{"ad", "ae","af", "bd", "be", "bf", "cd", "ce", "cf"}. 如此循环...直到字符串末尾。

坑
1. 不要忘记在开头,  判断 digits是否为empty
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;


// 方法1： dfs N次循环，每层循环3-4次。
// Time Complexity: O(3^n)
// 0ms
class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        ret.clear();
        if (digits.empty()) return ret;

        vector<string> mapping = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };   // 数字2-9的映射, 01为空
        letterMap = mapping;

        dfs(0, digits.length(), digits);

        return ret;
    }

    void dfs(int depth, int n, string digits)
    {
        if (depth == n)
        {
            ret.push_back(oneSolution);
            return;
        }

        // 第depth层对应的  数字
        size_t idx = digits[depth] - '0';
        if (letterMap[idx].length() == 0)  // just skip this digit, eg: 1
        {
            dfs(depth + 1, n, digits);
        }
        else
        {
            for (size_t j = 0; j < letterMap[idx].length(); j++)
            {
                oneSolution.push_back(letterMap[idx][j]);
                dfs(depth + 1, n, digits);
                oneSolution.pop_back();     // backtracking
            }
        }
    }

private:
    vector<string> letterMap;    // 数字2-9  对应的 字符, 01为空
    vector<string> ret;
    string oneSolution;
};


// 方法2： 直接循环，枚举出所有的解.
//   思路: 比如“234”这个字符串，我可以先将0...1的所有排列找到-->{"a", "b", "c"}
//         再进一步将0...2的所有排列找到-->{"ad", "ae","af", "bd", "be", "bf", "cd", "ce", "cf"}. 如此循环...直到字符串末尾。
class Solution2
{
public:
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty()) return vector<string>();

        vector<string> res;
        string charmap[10] = { "0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

        res.push_back("");
        for (int i = 0; i < digits.size(); i++)
        {
            vector<string> tempres;
            string chars = charmap[digits[i] - '0'];

            // 妙!
            for (int c = 0; c < chars.size(); c++)       // 测试用例，输入的digit没有01噢。 恩，上面的charmap用""表示也能通过。(其实是会有问题的)
            for (int j = 0; j < res.size(); j++)
                tempres.push_back(res[j] + chars[c]);

            res = tempres;
        }

        return res;
    }
};

// 与方法2类似，但写的更'优雅一些'
class Solution3
{
public:
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty()) return vector<string>();

        const string letters[] = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

        vector<string> ret(1, "");
        for (int i = 0; i < digits.size(); ++i)
        for (int j = ret.size() - 1; j >= 0; --j)
        {
            const string &s = letters[digits[i] - '2'];
            for (int k = s.size() - 1; k >= 0; --k)
            if (k)
                ret.push_back(ret[j] + s[k]);
            else
                ret[j] += s[k];
        }

        return ret;
    }
};

int main(int argc, char *argv[])
{
    //input section
    string digit = "23";

    //
    Solution solution;
    clock_t start_time = clock();

    //
    vector<string> ans = solution.letterCombinations(digit);

    cout << ans.size() << endl;

    clock_t end_time = clock();

    //输出运行时间
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;

    return 0;
}

