/*
Contains Duplicate

Given an array of integers, find if the array contains any duplicates.
Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

https://leetcode.com/problems/contains-duplicate/

一句话小结:  该题让我体会了C++ STL中几个容器(set/map, unordered_set/unordered_map)的异同点~  加深了对它们的了解，使用
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


// 方法1: 首先排序sort, 然后线性扫描，找到相同的元素直接返回true
// Time Complexity: O(NlogN); Space Complexity: O(1)
// 44ms
class Solution
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        if (nums.size() < 2) return false;

        sort(nums.begin(), nums.end());

        int preElem = nums[0];
        for (int i = 1; i != nums.size(); i++)
        {
            if (preElem == nums[i])
                return true;

            preElem = nums[i];
        }

        return false;
    }
};


// 方法2: 利用set容器, 直接判断是否有重复元素
// Time Complexity: O(NlogN); Space Complexity: O(N)
// 96ms
class Solution2
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        if (nums.size() < 2) return false;

        set<int> numSet;
        for (auto x : nums)
        {
            if (numSet.find(x) != numSet.end())
                return true;

            numSet.insert(x);
        }

        return false;
    }
};


// 方法3: 还是利用set, 两行代码更简洁~ 恩，尽管复杂度同方法2, 但是执行更快噢 (体会代码简洁性, 带来的效率提升)
// 48ms
class Solution3
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        set<int> iset(nums.begin(), nums.end());
        return iset.size() < nums.size();
    }
};

// 方法4: 利用map容器, 直接判断是否有重复元素
// Time Complexity: O(NlogN); Space Complexity: O(N)
// 96ms

// 小结: 和方法2运行时间是一样的哇!  恩~ set和map底层实现都是红黑树(Red-Black Tree), 复杂度是一样的。
//       不是相对来说，对于这类问题,set更合适一些。map需保存key-value, 此处没必要value.
class Solution4
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        if (nums.size() < 2) return false;

        map<int, bool> numMap;
        for (auto x : nums)
        {
            if (numMap.find(x) != numMap.end())
                return true;

            numMap.insert(make_pair(x, true));
        }

        return false;
    }
};


// 方法5: 利用unordered_set, 直接判断是否有重复元素 - 底层为HashMap
// Time Complexity: O(N); Space Complexity: O(N)
// 48ms
class Solution5
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        if (nums.size() < 2) return false;

        unordered_set<int> numHashSet;
        for (auto x : nums)
        {
            if (numHashSet.find(x) != numHashSet.end())
                return true;

            numHashSet.insert(x);
        }

        return false;
    }
};


// 方法6: 利用unordered_map, 直接判断是否有重复元素
// Time Complexity: O(N); Space Complexity: O(N)
// 56ms

// 小结:  方法5和6时间差不多哈!  恩~ 复杂度是一样的。实现细节.
//        Up to now, 体会set/map, unordered_set/unordered_map之间的区别。以及STL容器和算法设计的一致性! 方便修改.
class Solution6
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        if (nums.size() < 2) return false;

        unordered_map<int, bool> numHashMap;
        for (auto x : nums)
        {
            if (numHashMap.find(x) != numHashMap.end())
                return true;

            numHashMap.insert(make_pair(x, true));
        }

        return false;
    }
};


// 解法7: 朋友的代码, 类似方法4，也是利用的map.  体会为什么执行时间慢一些?  map的[]操作!
// Time Complexity: O(NlogN); Space Complexity: O(N)
// 104ms
class Solution7
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        map<int, int> myMap;
        for (int i = 0; i<nums.size(); i++)
        {
            myMap[nums[i]]++;
            if (myMap[nums[i]]>1)
                return true;
        }
        return false;
    }
};


int main(int argc, char *argv[])
{
    //input section
    vector<int> nums = { 5, 3 , 1, 3, 4};

    //
    Solution solution;
    clock_t start_time = clock();

    //
    bool ret =  solution.containsDuplicate(nums);

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



/*
// C语言，自己实现了一个简单的hashSet，挺不错的，值得借鉴^^
// unordered_set底层 -- hash 链表法

struct Node
{
    int val;
    struct Node *next;
};

struct Set
{
    int bucketSize;
    struct Node **table;
};

void initSet(struct Set *set, int bucketSize)
{
    set->bucketSize = bucketSize;
    set->table = malloc(sizeof(struct Node*) * bucketSize);
    memset(set->table, 0, sizeof(struct Node*) * bucketSize);
}

bool addValue(struct Set *s, int val)
{
    int idx = val > 0 ? val : -val;
    idx %= s->bucketSize;                // 自定义的简单的hash函数 (不一定好，即可能导致大量的冲突，但实用~)
    struct Node *ptr = s->table[idx];

    while(ptr != NULL)
    {
        if(ptr->val == val)
        {
            return false;
        }

        ptr = ptr->next;
    }

    ptr = malloc(sizeof(struct Node));
    ptr->val = val;
    ptr->next = s->table[idx];
    s->table[idx] = ptr;
    return true;
}

//不错，模块结束时，正确的释放了内存.
void releaseSet(struct Set *s)
{
    struct Node *ptr, *tmp;
    for(int i = 0; i < s->bucketSize; ++i)
    {
        ptr = s->table[i];
        while(ptr != NULL)
        {
            tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }

    free(s->table);
    s->table = NULL;
    s->bucketSize = 0;
}

bool containsDuplicate(int* nums, int numsSize)
{
    if(numsSize < 2)
    {
        return false;
    }

    struct Set set;
    initSet(&set, numsSize / 2);

    for(int i = 0; i < numsSize; ++i)
    {
        if( !addValue(&set, nums[i]) )
        {
            releaseSet(&set);
            return true;
        }
    }

    releaseSet(&set);
    return false;
}

*/
