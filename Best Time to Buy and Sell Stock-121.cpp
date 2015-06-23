/*
Best Time to Buy and Sell Stock

Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock),
design an algorithm to find the maximum profit.

=======================================================
题目链接:  https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

一句话总结:  DP( 1D/1D-->1D/0D)  f[i] = max(f[i-1], a[i]-minI);  第i天卖出股票(Greedy Choice), 或不在第i天卖出(子问题的最优解). minI为第1天到第i天的股票最小价格
*/
#include <iostream>

#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int>& prices)
    {
        if (prices.size() <= 1) return 0;

        int maxProfit = 0;
        int minI = prices[0];
        for (size_t i= 1; i != prices.size(); i++)
        {
            maxProfit = max(maxProfit, prices[i] - minI);
            minI = min(minI, prices[i]);
        }

        return maxProfit;
    }
};

int main(int argc, char *argv[])
{
    //input section
    vector<int> prices = { 5, 2, 3, 1, 10 };

    //
    Solution solution;
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
