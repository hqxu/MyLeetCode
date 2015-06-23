/*
Triangle

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
For example, given the following triangle
[
    [2],
   [3,4],
  [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
=======================================================
题目链接:  https://leetcode.com/problems/triangle/
题目意思: 从上到下，每一次移动，只能移到下层的 相邻元素 ---- adjacent numbers定义( 第i层的第j个数，走到第i+1层，只能选择第j个数，第j+1个数 )

一句话总结:  DP(2D/0D).  f[i,j] = min(f[i-1, j] , f[i-1,j-1]) + t[i,j];   注意每一层的第1个数和最后一个数。Then, 求最后一层的最小值即可。
*/
#include <iostream>

#include <vector>
#include <string>

#include <algorithm>

#include <ctime>
using namespace std;

// 方法一:  Time Complexity: O(N^2); Space Compexity: O(N^2)
class Solution
{
public:
    int minimumTotal(vector<vector<int>>& triangle)
    {
        if (triangle.empty()) return 0;

        int i, j;
        int n = triangle.size();
        vector<vector<int>> f(n, vector<int>());

        f[0].resize(1);
        f[0][0] = triangle[0][0];
        for (i = 1; i < n; i++)
        {
            f[i].resize(i+1);

            f[i][0] = f[i - 1][0] + triangle[i][0];
            f[i][i] = f[i - 1][i - 1] + triangle[i][i];

            for (j = 1; j <= i - 1; j++)
                f[i][j] = min(f[i - 1][j - 1], f[i - 1][j]) + triangle[i][j];
        }

        int ret = f[n - 1][0];
        for (j = 1; j < n; j++)
            ret = min(ret, f[n - 1][j]);

        return ret;
    }
};

// 方法2: DP思路同上。内存优化。 每次迭代只需要保存两行的信息即可, 利用Ping-Pong mode to save memory.
// Time Complexity: O(N^2); Space Compexity: O(N)
class Solution2
{
public:
    int minimumTotal(vector<vector<int>>& triangle)
    {
        if (triangle.empty()) return 0;

        int i, j;
        int n = triangle.size();
        vector<vector<int>> f(2, vector<int>(n, 0));  // just two rows memory
        int first = 0, second = 1;

        f[first][0] = triangle[0][0];
        for (i = 1; i < n; i++)
        {
            f[second][0] = f[first][0] + triangle[i][0];
            f[second][i] = f[first][i - 1] + triangle[i][i];

            for (j = 1; j <= i - 1; j++)
                f[second][j] = min(f[first][j - 1], f[first][j]) + triangle[i][j];

            // swap first and second rows (logically)
            first = 1 - first;            //  first ^ 1
            second = 1 - second;  // second ^ 1
        }

        int row = ( (n&1) == 0);  // find proper row index
        int ret = f[row][0];
        for (j = 1; j < n; j++)
            ret = min(ret, f[row][j]);

        return ret;
    }
};

int main(int argc, char *argv[])
{
    //input section
    vector<vector<int>> triangle = { {2}, {3,4}, {6,5,7}, {4,1,8,3}};

    //
    Solution2 solution;
    clock_t start_time = clock();

    //
    int ans = solution.minimumTotal(triangle);
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
