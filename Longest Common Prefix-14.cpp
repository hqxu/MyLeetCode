/*
Longest Common Prefix

Write a function to find the longest common prefix string amongst an array of strings.
======================================
题目链接: https://leetcode.com/problems/longest-common-prefix/

一句话总结:  求N个串的最长公共前缀。 简单的字符串题目，直接线性扫描一遍比较即可。但问题本身很有趣，很容易扩展~ Trie树~

坑:
1. {"aa", "a"}  要注意第一个串的长度，可能大于后面的串!  应考虑每个串的长度限制.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

// 方法1: 取第一个串为基准，判断该串的每个字符是否存在其它所有串中(从第一个字母逐个尝试), 一旦有串不包含这个字符，则相同的前缀串得出
// Time Complexity: O( N * l串长度)
// 应该有更好的方法？ 比如说预先创建一棵Trie树 (空间复杂度高了), 但此时找到最长的公共前缀 所需要的时间只与 公共前缀的长度相关。
// 如果要验证多次，且可以插入串、删除串。预先构建一个数据结构肯定是好的。  但这里只一次的话，直接线性也是可以接受噢
class Solution
{
public:
    string longestCommonPrefix(vector<string>& strs)
    {
        if (strs.empty()) return string();
        if (strs.size() == 1) return strs[0];

        string ret;
        string pattern = strs[0];
        for (size_t i = 0; i < pattern.length() && check(pattern[i], i, strs); i++)
                ret += pattern[i];

        return ret;
    }

    bool check(char c, size_t idx, const vector<string>& strs)
    {
        for (size_t i = 1; i != strs.size(); i++)
            if (strs[i].length() <= idx || c != strs[i].at(idx))
                return false;

        return true;
    }
};

int main(int argc, char *argv[])
{
    //input section
    //vector<string> strs = {"xuha", "xuhu"};
    vector<string> strs = { "aa", "a" };

    //
    Solution solution;
    clock_t start_time = clock();

    //
    string ans = solution.longestCommonPrefix(strs);
    cout << ans << endl;

    clock_t end_time = clock();

    // Print Running Time
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;

    return 0;
}
