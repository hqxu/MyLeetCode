/*
Maximum Product Subarray (最大子段和的扩展：乘积)

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
=======================================================
题目链接:  https://leetcode.com/problems/maximum-product-subarray/

一句话总结:  相比最大子段和，乘积需要考虑负数的情况。 g[i]的含义是： 以nums[i]结尾的最小连续子乘积.

扩展题： 对于全是正的浮点数，可以考虑用对数，转换成最大子段和的问题噢。

Reference:
1.  状态转移方程写的不错.
http://blog.csdn.net/wzy_1988/article/details/9319897
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Solution
{
public:
    int maxProduct(vector<int>& nums)
    {
        if (nums.empty()) return 0;

        int n = nums.size();
        int maxSofar = nums[0];
        vector<int> f(n, 0);           // 以nums[i]结尾的 最大连续子序列乘积
        vector<int> g(n, 0);           // 以nums[i]结尾的 最小连续子序列乘积

        f[0] = nums[0];
        g[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            if (nums[i] >= 0)
            {
                f[i] = max(nums[i], nums[i] * f[i - 1]);
                g[i] = min(nums[i], nums[i] * g[i - 1]);
            }
            else // 负负得正
            {
                f[i] = max(nums[i], nums[i] * g[i - 1]);
                g[i] = min(nums[i], nums[i] * f[i - 1]);
            }

            maxSofar = max(maxSofar, f[i]);
        }

        return maxSofar;
    }
};

class Solution2
{
public:
    int maxProduct(vector<int>& nums)
    {
        if (nums.empty()) return 0;

        int maxSofar = nums[0];
        int f = nums[0];           // 以nums[i]结尾的 最大连续子序列乘积
        int g = nums[0];           // 以nums[i]结尾的 最小连续子序列乘积

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] >= 0)
            {
                f = max(nums[i], nums[i] * f);
                g = min(nums[i], nums[i] * g);
            }
            else // 负负得正
            {
                int lastF = f;  // 注意下面的计算. g需要用到上一次的f值.

                f = max(nums[i], nums[i] * g);
                g = min(nums[i], nums[i] * lastF);

            }

            maxSofar = max(maxSofar, f);
        }

        return maxSofar;
    }
};

int main(int argc, char *argv[])
{
    //input section
    //vector<int> nums = { -2, 3, -4 };
    vector<int> nums = { -4, -3, -2 };

    //
    Solution2 solution;
    clock_t start_time = clock();

    //
    int ans = solution.maxProduct(nums);
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
