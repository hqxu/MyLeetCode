/*
Maximum Subarray  (最大子段和)

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

More practice:  (思考用分治法来解O(NlogN)--最近点对问题)
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
=======================================================
题目链接:  https://leetcode.com/problems/maximum-subarray/

一句话总结: f[i] = max( nums[i], nums[i] + f[i-1] );   f[0] = nums[0].  f[i]的含义是： 以i结尾的子序列最大可能的和 ( ending at nums[i])
                  ^^ 明白了上面的递推式，节约空间，从而有了 王晓东书上那种简单的版本(参见Solution2)

========
不愧是经典题
O(N^3) ---> O(N^2) 累加和数组--辅助的数据结构  ---> O(NlogN) 分治法 (合并起来不容易)  ---> O(N) DP线性扫描.

还有许多相应的扩展: 1) 二维 2)乘积
========

Reference:
1.  这哥门写的状态转移方程写的挺好的，很清晰!
http://blog.csdn.net/wzy_1988/article/details/9319897

2.  总结的很全面 (-.- 自己对于写blog老偷懒呀...学习!)
http://www.cnblogs.com/wuyuegb2312/p/3139925.html#title4
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int>& nums)
    {
        if (nums.empty()) return 0;

        int n = nums.size();
        int maxSofar = nums[0];
        vector<int> f(n, 0);

        f[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            f[i] = max(nums[i], nums[i] + f[i - 1]);
            maxSofar = max(maxSofar, f[i]);
        }

        return maxSofar;
    }
};


// 自己记忆中，王晓东书上的应该是这个版本噢…… 简化了。 说明当时的自己没有掌握好DP噢。f的含义.
class Solution2
{
public:
    int maxSubArray(vector<int>& nums)
    {
        if (nums.empty()) return 0;

        int f = nums[0];
        int maxSofar = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            // f[i] = max( nums[i],  f[i-1] + nums[i] )
            if (f > 0)
                f += nums[i];
            else
                f = nums[i];

            maxSofar = max(maxSofar, f);
        }

        return maxSofar;
    }
};


int main(int argc, char *argv[])
{
    //input section
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4 };

    //
    Solution solution;
    clock_t start_time = clock();

    //
    int ans = solution.maxSubArray(nums);
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
