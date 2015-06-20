/*
Combination Sum

Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 2,3,6,7 and target 7,
A solution set is:
[7]
[2, 2, 3]

题目链接: https://leetcode.com/problems/combination-sum/


一句话总结:  子集和问题的扩展， 每个元素可使用无限次.
             同Combination Sum2的区别(每个元素只能使用一次), dfs实现的时候index下标保持i，不需要加1

注: 1. dfs时可用curSum值与target比较，如果curSum大于了，剪枝
    2. 对于生成全部子集(Combination)，去重的通用办法:  while循环跳过相同数字.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

// 方法1: dfs求得序列的子集树(所有可能的子集)，记录该子集的和等于Sum的子集合.  做了一个简单的剪枝优化 by comparing curSum with target value
// Time Complexity: O(2^n)?  Space Complexity: O( ** )?
// 28ms
class Solution
{
public:
    //
    vector<vector<int> > combinationSum(vector<int>& candidates, int target)
    {
        inputVec.clear();
        oneSolution.clear();
        ret.clear();

        inputVec = candidates;
        sort(inputVec.begin(), inputVec.end());

        // find all unique combinations in C where the candidate numbers sums to T
        dfs(0, 0, target, inputVec.size());

        return ret;
    }

    void dfs(int startIdx, int curSum, int target, int n)
    {
        // prune this branch. because the number is positive integer
        if (curSum > target)
            return;

        if (curSum == target)
        {
            ret.push_back(oneSolution);
            return;
        }

        for (int i = startIdx; i < n; i++)
        {
            oneSolution.push_back(inputVec[i]);
            curSum += inputVec[i];

            // !!!
            dfs(i, curSum, target, n);     // write curSum+inputVec[i] as the second parameter would make easier.

            // backtracking
            curSum -= inputVec[i];
            oneSolution.pop_back();

            // skip possible duplicate combination
            while (i < n - 1 && inputVec[i + 1] == inputVec[i]) i++;
        }
    }

private:
    vector<int> inputVec;
    vector<vector<int> > ret;
    vector<int> oneSolution;
};

int main(int argc, char *argv[])
{
    //input section
    vector<int> candidates = { 2, 3, 6, 7 };
    int target = 7;


    //
    Solution solution;
    clock_t start_time = clock();


    //
    vector<vector<int> > ans = solution.combinationSum(candidates, target);

    cout << ans.size() << endl;

    clock_t end_time = clock();
    //输出运行时间
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;

    return 0;
}
