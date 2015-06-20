/*
Contains Duplicate II

Given an array of integers and an integer k, find out whether there there are two distinct indices i and j in the array
such that nums[i] = nums[j] and the difference between i and j is at most k.

题目链接：https://leetcode.com/problems/contains-duplicate-ii/

一句话总结:   动态维护一个K+1元素的Windows(窗口内元素之间的最大距离为K)   -- useful idea^^
*/
#include <iostream>

#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include <ctime>
using namespace std;

void printVector(vector<int> intVec)
{
    for (size_t i = 0; i < intVec.size(); i++)
        cout << intVec[i] << "  ";
    cout << endl;
}

// 方法1: 首先对nums进行多关键字排序( (nums[i], i)), 如此，保证有多个相同元素时，它们的下标也是递增的.
//        此时，线性扫描一遍 且 判断 相邻的两个相同值的元素 下标之间距离是否小于<=k
// Time Complexity: O(NlogN); Space Complexity: O(N)
// 20ms
class Solution
{
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
        if (nums.size() < 2 || k<1) return false;

        vector<Node> nodeVec;
        for (size_t i = 0; i != nums.size(); i++)
            nodeVec.push_back(Node(nums[i], i));

        // stable sort by multi-key compare
        // sort(nodeVec.begin(), nodeVec.end(), CmpObject());  // by function object
        sort(nodeVec.begin(), nodeVec.end());                  // by overloading the  Node "<"" operator

        for (size_t i = 1; i != nodeVec.size(); i++)
        {
            // check 当前元素 与 前一个元素是否相同； 如果相同，它们原先的下标距离 是否 不大于k
            if (nodeVec[i - 1].value == nodeVec[i].value && (nodeVec[i].index - nodeVec[i - 1].index <= k))
                return true;
        }

        return false;
    }

private:
    struct Node
    {
        int value;
        int index;

        Node(int x, int idx) : value(x), index(idx)  {}

        bool operator<(Node t)
        {
            if (value != t.value)
                return value < t.value;

            return index < t.index;
        }
    };

    struct CmpObject
    {
        bool operator() (Node a, Node b)
        {
            if (a.value != b.value)
                return a.value < b.value;

            return a.index < b.index;
        }
    };
};


// 方法2: 利用map, nums[i]作为key, value为当前数最大的下标。
//        当有相同元素时，判断是否当前元素的下标j 与 value(先前最大下标)之间的差是否小于等于k
// Time Complexity: O(NlogN); Space Complexity: O(N)
// 68ms
class Solution2
{
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
        if (nums.size() < 2 || k<1) return false;

        map<int, int> numMap;
        for (int i = 0; i != nums.size(); i++)
        {
            auto iter = numMap.find(nums[i]);
            if (iter != numMap.end())
            {
                // i must greater than iter->second
                if (i - iter->second <= k)
                    return true;

                // save the largest index for this number. greedy choice
                iter->second = i;
            }
            else
            {
                // this number appears firstly.
                numMap.insert( make_pair(nums[i], i) );
            }
        }

        return false;
    }
};


// 方法3: 利用unordered_map, 思路同方法。
//        再次直观体会 unordered系列，比map/set快多少 ~~ 又是接近1倍呀!
//        恩.  map/set试用的场合;   unordered_map/unordered_set使用的场合 ( I got it:) 红黑树 vs. Hash)
//        STL真好用……代码几乎没有改变哈. When we need fine-tuning to improve performance.
// Time Complexity: O(N); Space Complexity: O(N)
// 32ms
class Solution3
{
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
        if (nums.size() < 2 || k < 1) return false;

        unordered_map<int, int> numHashMap;
        for (int i = 0; i != nums.size(); i++)
        {
            auto iter = numHashMap.find(nums[i]);
            if (iter != numHashMap.end())
            {
                // i must greater than iter->second
                if (i - iter->second <= k)
                    return true;

                // save the largest index for this number. greedy choice
                iter->second = i;
            }
            else
            {
                // this number appears firstly.
                numHashMap.insert(make_pair(nums[i], i));
            }
        }

        return false;
    }
};


// 方法4:  对于原序列[1....n], 动态 维护 一个k+1大小的窗口[a0, a1, a2,...ak], 距离最大为K.
//         新元素来的时候，只需要看下它是否在这个窗口中。 如果在，则说明有重复元素(in k distance windows), 否则，将窗口中的'第一个'元素删除，添入最新的这个元素.
// Time Complexity: O(NlogN); Space Complexity: O(N)
// 56ms
class Solution4
{
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
        if (nums.size() < 2 || k < 1) return false;

        set<int> numSet;
        for (int i = 0; i != nums.size(); i++)
        {
            // 维护k+1大小的窗口(保证里面只存k+1个数字). eg. 当地k+2个数字到来的时候, 它的index=k+1. 此时应该将该窗口中的nums[0]剔除
            if (i > k) numSet.erase(nums[i - (k + 1)]);

            // 插入失败 means 在k+1大小的窗口中，已存在相同元素
            if (!numSet.insert(nums[i]).second) return true;
        }

        return false;
    }
};


// 方法5:  与方式4一样。再次体会unordered_set与set的差别.  恩，尽管有删除操作，还是有点优势呀~
// Time Complexity: O(N); Space Complexity: O(N)
// 32ms
class Solution5
{
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
        if (nums.size() < 2 || k < 1) return false;

        unordered_set<int> numHashSet;
        for (int i = 0; i != nums.size(); i++)
        {
            if (i > k) numHashSet.erase(nums[i - (k + 1)]);
            if (!numHashSet.insert(nums[i]).second) return true;
        }

        return false;
    }
};


// 方法6:  暴力解法. 循环检查所有可能情况。   如果k很小的话，接近线性噢~  k很大的话，则是O(N^2).
// Time Complexity: O(k*N); Space Complexity: O(1)
// Time Limit Exceeded
class Solution6
{
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
        if (nums.size() < 2 || k < 1) return false;

        for (size_t i=0; i!=nums.size(); i++)
        {
            for (size_t j=i+1; j<=i+k && j!=nums.size(); j++)
                if (nums[i] == nums[j])
                    return true;
        }

        return false;
    }
};


int main(int argc, char *argv[])
{
    //input section
    vector<int> nums = { 5, 3, 1, 3, 4 };
    int k = 2;

    //
    Solution solution;
    clock_t start_time = clock();

    //
    bool ret = solution.containsNearbyDuplicate(nums, k);

    cout << boolalpha;
    cout << ret << endl;

    clock_t end_time = clock();

    //输出运行时间
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;
    return 0;
}
