/*
Contains Duplicate III

Given an array of integers, find out whether there are two distinct indices i and j in the array
such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.

即‘Deplicate’定义:   两个数nums[i]与nums[j],   它们的下标i,j的距离小于等于k;   而且 nums[i]与nums[j]的差小于等于t

题目链接:  https://leetcode.com/problems/contains-duplicate-iii/


一句话总结:  思路同Contains Duplicate II,  仍是动态维护一个k+1大小的Windows(窗口内元素之间的最大距离为K)
             该题特别之处是修改了'相等’的定义， 利用STL中set容器的第2个参数: predicate   (定义两个数字的距离大于t才被判为不相等;否则相等) 可方便实现.
             如果不用C++STL, 用C语言写的话， 那么自己手写一个Binary Search Tree, 改变 判断两元素 是否相等 "==" 的含义也是一样。

收获:  进一步掌握了对STL中 set/map容器的使用，可以提供第2个参数，进行自定义 比较；  类似 BST的灵活使用

Further:   目前最好的Solution的时间复杂度是O(NlogN), 空间复杂度是O(N)。
           是否有O(N)的时间复杂度 或 O(1)的空间复杂度的方法?


坑(Special Case)
1.  [-1, 2147483647] 两个数一相减，int型溢出 -- long long
2.  t<0的情形  --- 应提前想到。类似k<0, nums.size()<2等边界条件。
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


// 方法1:  对于原序列[1....n], 动态 维护 一个k+1大小的窗口[a0, a1, a2,...ak], 距离最大为K.
//         新元素来的时候，只需要看下它是否 在 这个窗口中有'相似'元素。
//         用set/map, STL底层实现的BST, 修改'相等'的定义。

// 恩，用的还是Contains DuplicateII中的维护k大小的窗口的思路，只是改变了'相等'的含义

// Time Complexity: O(NlogN); Space Complexity: O(N)
// 40ms
class Solution
{
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
    {
        if (nums.size() < 2 || k < 1 || t < 0) return false;

        bound = t;  // static data member to record t

        // 哈，还以为需要自己实现一个BST呢，想不到可以直接在这里通过CmpObject修改'相等' 含义,   STL的开放做的果然不错。
        // 可惜的是, set的predicate参数, 与sort, count_if等算法的predicate参数不一样，无法利用函数对象的灵活性 ( 参见C++ Primer中的P532)
        set<int, CmpObject> numSet;
        for (int i = 0; i != nums.size(); i++)
        {
            // 维护k+1大小的窗口(保证里面只存k+1个数字). eg. 当第k+2个数字到来的时候, 它的index=k+1. 此时应该在k+1大小的窗口中剔除nums[0]
            if (i > k) numSet.erase(nums[i - (k + 1)]);

            // 如果numSet里面已经存在于nums[i]相似的元素( 根据CmpObject中的函数返回值判断, false则存在相似的元素 ), 则插入失败返回false; 否则，插入成功，返回true;
            // 插入失败 means 在k+1大小的窗口中，已存在'相似'元素 -- 它们的差不大于t
            if (!numSet.insert(nums[i]).second) return true;
        }

        return false;
    }

private:
    static int bound;   // 由于set的predicate参数，与sort等不同。无法利用函数对象的灵活性(直接在CmpObject中定义bound). 此处采取列的静态变量
    struct CmpObject
    {
        bool operator() (long long a, long long b)
        {
            // 如果 dis(a,b) 大于t, 视为两元素不相同  (当t<0时，a==b时会有错误。该solution预先判断了t是否小于0, 所以在此认为t>=0即可)
            if (llabs(a - b) > bound)
            {
                return a < b;
            }
            // a == b
            return false;
        }
    };
};
int Solution::bound = 0;



// 方法2:  暴力枚举，根据要求，check所有可能的情况
// Time Complexity: O(N*k); Space Complexity: O(1)
// Time Limit Exceeded
class Solution2
{
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
    {
        if (nums.size() < 2 || k < 1) return false;

        int n = nums.size();
        for (int i = 0; i<n; i++)
        for (int j = i + 1; j <= i + k && j < n; j++)
        {
            long long a = nums[i];
            long long b = nums[j];

            if (a > b)
                swap(a, b);

            if (b - a <= t)  // If dis(a, b) is not greater than t, it mean a '==' b
                return true;
        }
        return false;
    }
};


// 方法3: 排序 + 线性扫描
//        首先对nums进行多关键字排序( (nums[i], i)), 如此，保证有多个相同元素时，它们的下标也是递增的.
//        此时，线性扫描一遍，   判断 相邻的两个差值<=t的元素 且 下标之间距离是否小于<=k
// Time Complexity: O(NlogN); Space Complexity: O(N)

//  Error. 该方法不适用于这个问题。 例如: nums = { 1,3,6,2 }, k=1, t=2;  此时存在(1,3)是解~ 但按照方案2相似的思路去解(相邻两元素), 会漏掉情况。
class Solution3
{
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
    {
        if (nums.size() < 2 || k<1) return false;

        s_value_interval = t;

        vector<Node> nodeVec;
        for (size_t i = 0; i != nums.size(); i++)
            nodeVec.push_back(Node(nums[i], i));

        // stable sort by multi-key compare
        sort(nodeVec.begin(), nodeVec.end(), CmpObject());
        // sort(nodeVec.begin(), nodeVec.end());

        for (size_t i = 1; i != nodeVec.size(); i++)
        {
            // check 当前元素 与 前一个元素的差值是否小于等于t； 如果符合条件，它们原先的下标距离 是否 不大于k
            if ((abs(nodeVec[i].value - nodeVec[i - 1].value) <= t) && (abs(nodeVec[i].index - nodeVec[i - 1].index) <= k))
                return true;
        }

        return false;
    }

private:
    static int s_value_interval;
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
            // 当两个元素'不同'时，按照值排序
            if (abs(a.value - b.value) > s_value_interval)
                return a.value < b.value;

            // 否则，按照下标排序.   例如;  当t=2, 则认为 4与2是相同的. 所以按照下标排的话，2,4,2... 就会产生这样的序列
            return a.index < b.index;
        }
    };
};
int Solution3::s_value_interval = 0;


// 方法4:  对于原序列[1....n], 动态 维护 一个k+1大小的窗口[a0, a1, a2,...ak], 距离最大为K.
//            新元素来的时候，只需要看下它是否 在 这个窗口中有'相似'元素。
//            思路同方法1), 但走了一些弯路，做了一些不必要的事情~~ （方法1为优化后的最终版本)
// Time Complexity: O(NlogN); Space Complexity: O(N)
// 44ms
class Solution4
{
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
    {
        // 没有考虑到 t < 0 时的特殊情况
        if (nums.size() < 2 || k < 1) return false;

        vector<Node> nodeVec;
        for (size_t i = 0; i != nums.size(); i++)
            nodeVec.push_back(Node(nums[i], t, i));

        set<Node, CmpObject> numSet;
        for (int i = 0; i != nums.size(); i++)
        {
            if (i > k) numSet.erase(nodeVec[i - (k + 1)]);
            if (!numSet.insert(nodeVec[i]).second) return true;
        }

        return false;
    }

private:
    struct Node
    {
        long long value;
        int t_same_interval;
        int idx;
        Node(int x, int t, int index) : value(x), t_same_interval(t), idx(index) {}
    };

   // 对于set/map, 两个元素是否相等，需深刻体会下面这句话:
   // The set object uses this expression to determine both the order the elements follow in the container and whether two element keys are equivalent
   // by comparing them reflexively: they are equivalent if !comp(a,b) && !comp(b,a)). No two elements in a set container can be equivalent.
    // http://www.cplusplus.com/reference/set/set/
    struct CmpObject
    {
        bool operator() (Node a, Node b)
        {
            // 当t<0时，尽管 a.value == b.value (此时也要认为是不等的)
            if (llabs(a.value - b.value) > a.t_same_interval)
            {
                // 对于两个元素相等……此时它的序是随机的?   会出错。不相等的时候 ( strict weak ordering)
                // 额……想复杂了。 恩，t<0属于特殊情况，边界条件!  当然，我这么一写，也是可以的. (永远没有元素' 相同'咯)
                // 也的确是。 尽管上面写了限制，但 两元素相等的时候，就是会有这个问题。
                // 说明自己考虑的还不够仔细，简单的使用 return a.value < b.value;
                if (a.value == b.value)
                {
                    return a.idx < b.idx;
                }

                // 需要有一个序的关系
                return a.value < b.value;
            }

            return false;
        }
    };
};


// 方法5：  想利用unordered_set,  STL底层实现的Hash, 修改'相等'的定义 --- 恩，用的还是Contains DuplicateII中的维护k大小的窗口的方法
//              如此，时间复杂度为 O(N), 空间复杂度O(N)
// 待实现……了解unordered_set底层 --- 自定义 比较函数。
// 该思路不可行，因为hashMap，对于不同的数据会映射到不同的桶中……然后才是利用predicate进行比较。
class Solution5
{
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
    {
        // 恩，hashSet想修改 '相等'的含义的话，不能这么简单的修改…… 体会hashSet是如何判断元素相等的。
        // 与set/map不一样。 ( 先hash到一个桶里面，然后再到对应的链表里面一一去比)
    }
};


int main(int argc, char *argv[])
{
    // input section

    // vector<int> nums = { 5, 3, 1, 3, 4 };

    // 下面两例 针对 (方法3: 排序 + 线性扫描), 说明方法3的思路不行
    // vector<int> nums = { 2, 6, 75, 85, 95, 4, 990, 968, 917, 896, 844, 2, 10000, 20000, 30000, 40000, 50000, 2, 199, 298, 397, 495, 594, 2};
    // int k = 5;
    // int t = 2;
    // vector<int> nums = { 1,3,6,2 };
    // k = 1;
    //  t = 2;

    vector<int> nums = { -1, 2147483647 };
    int k = 1;
    int t = 2147483647;

//     vector<int> nums = { -1, -1 };
//     k = 1;
//     t = -1;

    //
    Solution solution;
    clock_t start_time = clock();

    //
    bool ret = solution.containsNearbyAlmostDuplicate(nums, k, t);

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
