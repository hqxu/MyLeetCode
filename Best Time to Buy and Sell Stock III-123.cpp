/*
Best Time to Buy and Sell Stock III

Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most two transactions.
Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
=======================================================
题目链接:  https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
题目意思:  相比Stock1的中能买卖一次, 该题是 至多能买卖两次!  ( 必须先卖出，再买进)

一句话总结: DP(1D/0D). 可找到一个划分点K, 将原问题划分成两个不重叠的子区间， 从而
                           maxProfit = max(maxProfit, maxProfitInRange(prices, 0, k) + maxProfitInRange(prices, k + 1, n - 1));

亮点:  有着矩阵链乘和word break那样的DP找划分点K的需求， 特殊之处在于划分后的两个子问题 可以特殊求得f[i], g[i]，而不是算出所有的子区间f[i,j]
       子问题的特殊性:  prices[0...i],  prices[i...n-1]    从0开头 或 以n-1结尾，  不需要针对prices[i...j]来求出所有, 因为大部分用不到。

       从正反两方面入手， 令f[i]= prices[0...i]买卖1次最大利润，  g[i]=prices[i...n-1]买卖1次最大利润。 避免重复计算。

*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;


// 方法1: 想到了将原问题 分成两个不重叠区间的子问题的思路。但忽略了重复计算，导致TLE……f[0..k],  f[0..k+1]重复计算了。
// Time Complexity: O(N^2);  Space Complexity: O(1)
// Time Limit Exceeded
class Solution
{
public:
    int maxProfit(vector<int>& prices)
    {
        if (prices.size() <= 1) return 0;

        int n = prices.size();
        // 只买卖1次
        int maxProfit = maxProfitInRange(prices, 0, n - 1);

        // 股票买卖2次。 由于买第2次之前必须卖出第1次的股票
        // 所以[0...k], [k+1...n-1] 肯定在k天会被划为成两个不重叠的子区间。 ( 0<= k <=n-1 )
        for (int k= 0; k< n-1; k++)
        {
            maxProfit = max(maxProfit, maxProfitInRange(prices, 0, k) + maxProfitInRange(prices, k + 1, n - 1));
        }

        return maxProfit;
    }

    // prices[s....e] 买卖1次股票可能的最大利润。 闭区间[ ]
    int maxProfitInRange(const vector<int>& prices, int start, int end)
    {
        int maxProfit = 0;
        int minI = prices[start];
        for (int i = start+1; i<=end; i++)
        {
            maxProfit = max(maxProfit, prices[i] - minI);
            minI = min(minI, prices[i]);
        }

        return maxProfit;
    }
};

// 方法2:  思路同上，但利用了DP保存子问题的解 （即找到f[0, k] 与 f[0, k+1]的关系，节省了重复计算)
//            本来是朝着矩阵链乘那样的思路找k的。但由于方法1的TLE, 说明时间复杂度不能为平方级 ( 矩阵链乘的子问题都是2D了)
//            从而想到正反两面求解， f[i]表示prices[0..i]的最优解，  g[i]表示prices[i....n-1]的买卖1次股票的最优解
// Time Complexity: O(N);  Space Complexity: O(N)
// 12ms
class Solution2
{
public:
    int maxProfit(vector<int>& prices)
    {
        if (prices.size() <= 1) return 0;

        int n = prices.size();

        // 从前往后  f[i]的含义: 从 prices[0...i]中买卖一次，最大的利润。
        vector<int> f(n, 0);
        int minS = prices[0];
        f[0] = 0;
        for (int i = 1; i <n; i++)
        {
            f[i] = max(f[i-1], prices[i] - minS);   // 第i天卖出的话，可能的最大利润  与 f[i-1]比较， 保存利润更大者
            minS = min(minS, prices[i]);
        }

        // 从后往前  g[i]的含义:  从 prices[i...n-1]中买卖一次，最大的利润。
        vector<int> g(n, 0);
        int maxE = prices[n - 1];
        g[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--)
        {
            g[i] = max(g[i + 1], maxE - prices[i]);  // 第i天买入的话，可能的最大利润 与 g[i+1]比较， 保存利润更大者
            maxE = max(maxE, prices[i]);
        }

        // 只买卖1次
        int maxProfit = f[n - 1];  // == g[0]
        // 股票买卖2次。 由于买第2次之前必须卖出第1次的股票，所以[0...k], [k+1...n-1] 肯定在k天会被划为成两个不重叠的子区间。 ( 0<= k <=n-1 )
        for (int k =0; k < n-1; k++)
            maxProfit = max(maxProfit, f[k] + g[k+1]);

        return maxProfit;
    }
};


int main(int argc, char *argv[])
{
    //input section
    vector<int> prices = { 5, 2, 3, 1, 10 };

    //
    Solution2 solution;
    clock_t start_time = clock();

    //
    int ans = solution.maxProfit(prices);
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
