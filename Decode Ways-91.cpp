/*
Decode Ways

A message containing letters from A-Z is being encoded to numbers using the following mapping:
'A' -> 1
'B' -> 2
...
'Z' -> 26

Given an encoded message containing digits, determine the total number of ways to decode it.
For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
The number of ways decoding "12" is 2.
=======================================================
题目链接:  https://leetcode.com/problems/decode-ways/

一句话总结:  DP(1D/0D).  f[i] = (s[i-1]!='0' ? f[i - 1]:0)+ { 当前最后两个字符可以组成合法的映射? f[i-2] : 0};   边界: f[0]=f[1]=1;
坑:
1. 输入"",    要输出0，而不是1
2. 关于'0'的输入各种情况:   "0", "10", “101", "10012"
*/
#include <iostream>

#include <vector>
#include <string>

#include <algorithm>

#include <ctime>
using namespace std;

class Solution
{
public:
    int numDecodings(string s)
    {
        int n = s.length();

        // exception input
        if (n<=0 || (s[0]=='0')) return 0;

        vector<int> f(n+1, 0);
        // boundary value
        f[0] = 1;
        f[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            // Note:  f[1...n]  correspond to s[0...n-1]
            // Deal with '0' carefully
            f[i] = (s[i-1]!='0' ? f[i - 1]:0) + ( check( s.substr(i - 2, 2) ) ? f[i - 2] : 0);
            if (0 == f[i]) return 0;
        }

        return f[n];
    }

    bool check(string s)
    {
        // invalid mapping "05"
        if (s[0] == '0') return false;

        int num = 0;
        for (size_t i = 0; i != s.size(); i++)
            num = num * 10 + (s[i] - '0');

        if (num <= 26) return true;

        return false;
    }
};

int main(int argc, char *argv[])
{
    //input section
    string s = "10012";

    //
    Solution solution;
    clock_t start_time = clock();

    //
    int ans = solution.numDecodings(s);
    cout << ans << endl;

    //
    clock_t end_time = clock();


    // Print Running Time
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;

    return 0;
}
