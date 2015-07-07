/*
Merge Sorted Array

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2.
The number of elements initialized in nums1 and nums2 are m and n respectively.
======================================
题目链接: https://leetcode.com/problems/merge-sorted-array/

一句话总结: 合并两个有序数组~Merge Sort中的基本操作。不管是Linked list, 还是vector, 思路都差不多。
            鉴于这个题目的特殊性(nums1数组的size大于等于合并后的数组的size), 所以可以不使用额外的辅助空间. 见Solution2
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

// 方法一: 归并操作. 借用一个辅助数组，暂存合并后的结果
// 时间复杂度: O(m+n); 空间复杂度: O(m+n)
class Solution
{
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        if (m <= 0 && n <= 0) return;

        vector<int> nums3(m + n, 0);

        int i, j, k;
        i = j = k =0;
        while (i < m && j < n)
        {
            if (nums1[i] < nums2[j])
            {
                nums3[k++] = nums1[i];
                i++;
            }
            else
            {
                nums3[k++] = nums2[j];
                j++;
            }
        }

        while (i < m) nums3[k++] = nums1[i++];
        while (j < n) nums3[k++] = nums2[j++];

        for (i = 0; i < m + n; i++)
            nums1[i] = nums3[i];
    }
};

// 方法2: 利用nums1的特殊性(size大于合并后的数组), 不依靠辅助数组做合并 -- 先将m个元素后移
//        注意一下 元素覆盖 问题即可
// 时间复杂度: O(m+n); 空间复杂度: O(1)
class Solution2
{
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        if (m <= 0 && n <= 0) return;

        // 题目保证nums1的size大于等于n+m
        // nums1.resize(n + m);

        // nums1整体后移n个位置 nums1[ 0,1,2,3,....n-1, n, n+1, ...., n+m-1]
        for (int i = m - 1; i >= 0; i--)
            nums1[n + i] = nums1[i];

        int totalNum = n + m;
        int pointer1 = n;
        int pointer2 = 0;
        int pointer3 = 0;
        while (pointer1 < totalNum && pointer2 < n)
        {
            if (nums1[pointer1] < nums2[pointer2])
            {
                nums1[pointer3++] = nums1[pointer1];
                pointer1++;
            }
            else
            {
                nums1[pointer3++] = nums2[pointer2];
                pointer2++;
            }
        }

        //while (pointer1 < totalNum) nums1[pointer3++] = nums1[pointer1++];
        while (pointer2 < n) nums1[pointer3++] = nums2[pointer2++];
    }
};

int main(int argc, char *argv[])
{
    //input section
    vector<int> nums1 = { 1, 5, 6,9 };
    vector<int> nums2 = { 2, 4, 5 };

    //
    Solution2 solution;
    clock_t start_time = clock();

    //
    solution.merge(nums1, nums1.size(), nums2, nums2.size());
    clock_t end_time = clock();

    // Print Running Time
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;

    return 0;
}
