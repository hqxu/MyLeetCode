/*
Combination Sum II

Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 10,1,2,7,6,1,5 and target 8,
A solution set is:
[1, 7]
[1, 2, 5]
[2, 6]
[1, 1, 6]

题目链接: https://leetcode.com/problems/combination-sum-ii/

一句话小结:  经典的子集和问题。每个元素只可用1次. 哈，代码与Combination Sum几乎一模一样哈，差别只有一个"+1", dfs递归的时候用下一个元素，而不是本身.


收获:   正是通过这到题，体会到了对于生成一个序列的All K-Permutation(排列), All K-Combination(组合)，可以先排序、再用while循环跳过重复数字的办法解决去重问题(unique)
======================================================================
        sort(inputVec.begin(), inputVec.end());
        // skip possible duplicate combination
        while (i < n - 1 && inputVec[i + 1] == inputVec[i]) i++;
======================================================================
        第一次用的笨方法是枚举出所有的Combination, 然后对于生成的每个解，都利用set去判重……额……相比线性比较判重好一些。。不过最终学到了不生成重复序列的办法才是最好的^^


注: 1. dfs时可用curSum值与target比较，如果curSum大于了，剪枝
    2. 对于生成全部子集(Combination)，去重的通用办法:  while循环跳过相同数字.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

// 方法2: dfs求得序列的子集树(所有可能的子集)，记录该子集的和等于Sum的子集合.  做了一个简单的剪枝优化 by comparing curSum with target value
//        该方法的优点:  先对序列进行排序，然后利用while循环跳过重复，使得生成的解都是unique的, 避免了 大量的判断重复操作 (对比方法2)
// Time Complexity: O(2^n)?  Space Complexity: O( ** )?
// 20ms
class Solution2
{
public:
    //
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
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

            dfs(i+1, curSum, target, n);

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


//===========================
// 方法1: 刚做leetcode遇到的题……复习了backtracking, AC的时候还是很开心的^^  不过当时对于"重复解的判断"处理的不是很好, 不知道sort+while. 方法2)为改进
//       该方法的dfs采用的是0-1背包的 选与不选 for 每个元素。  而不是采用生成Combination的那种方式噢，注意对比区分。
// 83ms
class Solution
{
public:
    Solution();
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target);
private:
    void init();
    void findAllCombination(int i, int curVal);
    bool hadSameCombination(vector<int> oneCombination);
private:
    int targetNum;
    int n;
    vector<int> newCandidates;
    vector<bool> numStates;  // flag for number choosed or not

    int retVecNum;
    vector< vector<int> > ret;
};

Solution::Solution()
{
    targetNum = 0;

    newCandidates.clear();
    numStates.clear();
    n = 0;

    retVecNum = 0;
    ret.clear();
}

vector<vector<int>> Solution::combinationSum2(vector<int>& candidates, int target)
{
    // step1. pre-processing the candidates and saving data in class member
    for (auto number : candidates)
    {
        if (number <= target)
        {
            newCandidates.push_back(number);
            numStates.push_back(false);
        }
    }
    targetNum = target;
    n = numStates.size();

    // Ascend-Order of newCandidates
    sort(newCandidates.begin(), newCandidates.end());
//     for (auto val : newCandidates)
//         cout << val << "  ";
//     cout << endl << endl;

    // step2. To find all unique combinations recursively and save them to ret
    findAllCombination( 0, 0 );

    return ret;
}

bool Solution::hadSameCombination(vector<int> newCombination)
{
    int i, j;
    for (i = 0; i < retVecNum; i++)
    {
        vector<int> oldCombination = ret[i];
        int count = oldCombination.size();

        if (count == newCombination.size())
        {
            // 只要有1个数字不同，即新的组合  与 当前组合就不一样，开始下一组判断
            for (j = 0; j < count && oldCombination[j] == newCombination[j]; j++);

            // 之前已经有相同的组合了
            if (j == count) return true;
        }
    }

    return false;
}

void Solution::findAllCombination(int i, int curVal)
{
    // found a combination, then save it
    if (targetNum == curVal)
    {
        vector<int> oneCombination;

        for (size_t index = 0; index < numStates.size(); index++)
        {
            if (numStates[index])
                oneCombination.push_back(newCandidates[index]);
        }

        if ( !hadSameCombination(oneCombination) )
        {
            retVecNum++;
            ret.push_back(oneCombination);
        }

        return;
    }

    if (i < n && curVal<targetNum)
    {

        // 若curVal + newCandidates[i] 超过target时，那么curVal+newCandidates[i+1] 也肯定超过target, 没有必要试了
        if (curVal + newCandidates[i] > targetNum) return ;

        // choose the element of newCandidates[i]
        {
            numStates[i] = true;
            curVal += newCandidates[i];

            findAllCombination(i + 1, curVal);

            curVal -= newCandidates[i];
            numStates[i] = false;
        }


        // do not choose the element of newCandidates[i]
        findAllCombination(i + 1, curVal);
    }
}
//===========================================================

int main(int argc, char *argv[])
{
    //input section
    vector<int> candidates = { 10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    //
    Solution solution;
    clock_t start_time = clock();


    //
    vector<vector<int> > ans = solution.combinationSum2(candidates, target);

    cout << ans.size() << endl;

    clock_t end_time = clock();

    //输出运行时间
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;

    return 0;
}
