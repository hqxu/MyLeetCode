/*
Combination Sum III

Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
Ensure that numbers within the set are sorted in ascending order.

Example 1:
Input: k = 3, n = 7
Output:
[[1,2,4]]

Example 2:
Input: k = 3, n = 9
Output:
[[1,2,6], [1,3,5], [2,3,4]]

题目链接: https://leetcode.com/problems/combination-sum-iii/

一句话总结:  C(9, k) -- 即求序列的K组合，对于这些K-Combination, 挑出sum等于n(target)的组合。
        此题不错, 考察了两个知识点。  该题将K-Combinations 与 子集和问题统一了起来
      （在写dfs的时候能体会到。 需要用到k组合的depth控制深度,  以及子集合用到的curSum)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

// 方法1: dfs生成K-Combination, 同时保存curSum信息--子集和
class Solution
{
public:
    vector<vector<int>> combinationSum3(int k, int n)
    {
        ret.clear();
        if (n > 45) return ret;

        oneSolution.clear();
        oneSolution.resize(k);

        // find all unique combinations in {1,2,...9} where the candidate numbers sums to N
        dfs(0, k, 1, 0, n);

        return ret;
    }

    void dfs(int depth, int k, int startNum, int curSum, int target)
    {
        if (curSum > target) return;

        // All k subset
        if (depth == k)
        {
            // proper k subset -- Sum equals to target
            if (curSum == target)
                ret.push_back(oneSolution);

            return;
        }

        for (int i = startNum; i <= 9; i++)
        {
            oneSolution[depth] = i;
            curSum += i;

            dfs(depth+1, k, i+1, curSum, target);

            curSum -= i;
        }
    }
private:
    vector<vector<int> > ret;
    vector<int> oneSolution;
};


int main(int argc, char *argv[])
{
    //input section
    int k = 3, n = 9;

    //
    Solution solution;
    clock_t start_time = clock();

    //
    vector<vector<int>> ans = solution.combinationSum3(k, n);

    cout << ans.size() << endl;

    clock_t end_time = clock();

    //输出运行时间
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;

    return 0;
}

