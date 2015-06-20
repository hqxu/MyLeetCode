/*
Combinations

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
For example,
If n = 4 and k = 2, a solution is:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

题目链接: https://leetcode.com/problems/combinations/

一句话总结:  给定n个无重复的数字，求出它的K-Combination.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

//方法: 利用dfs, backtracking递归得到序列的子集树, 记录下K-Combinations.
//      利用depth这个变量记录层次数; 利用startIndex指定每次起始的元素，逐层+1, 达到了控制序的目标
//      优化: 每递归一次，可以让k-1, 从而省掉depth这个变量.
// 20ms
class Solution
{
public:
    vector<vector<int>> combine(int n, int k)
    {
        oneCombination.resize(k);
        dfs(0, 1, n, k);

        return ret;
    }

    void dfs(int depth, int startIndex, int n, int k)
    {
        if (depth == k)
        {
            // one combination
            ret.push_back( oneCombination );
            return;
        }

        for (int i = startIndex; i <= n; i++)
        {
            oneCombination[depth] = i;
            dfs(depth + 1, i + 1, n, k);
        }
    }

private:
    vector<vector<int>> ret;
    vector<int> oneCombination;
};

int main(int argc, char *argv[])
{
    //input section
    int n = 4;
    int k = 2;

    //
    Solution solution;
    clock_t start_time = clock();

    //
    vector<vector<int> > ans = solution.combine(n, k);

    cout << ans.size() << endl;

    clock_t end_time = clock();

    //输出运行时间
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;

    return 0;
}
