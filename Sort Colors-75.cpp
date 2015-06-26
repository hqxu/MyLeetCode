/*
Sort Colors   (荷兰国旗问题: 红0-蓝1-白2)
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
Note:
You are not suppose to use the library's sort function for this problem.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
=======================================================
题目链接:  https://leetcode.com/problems/sort-colors/

一句话总结:   1) 直接用STL sort轻松AC. 时间复杂度为O(NlogN)
              2) 计数排序(Counting sort) -- 两遍扫描 O(N)

              3) 一遍扫描法（利用quickSort中partition的想法. 多个指针)  O(N)
                 3.1) 前面两个指针red, blue, 后面一个指针white. 处理逻辑相对来说简单一些。 但外层循环i要注意写正确
                 3.2) 前面三个指针red, blue, white, 指向相应元素 安放的位置。  要注意的是 red-0元素时交换到前面时，可能把1弄到后面来了
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

void printVector(vector<int> intVec)
{
    for (size_t i = 0; i < intVec.size(); i++)
        cout << intVec[i] << "  ";
    cout << endl;
}

// 简化版本的计数排序 -- Count完后，直接赋值(大多数情况的是不能直接做么做的。此处因为元素不是Object，而是一个简单的int元素)
class Solution
{
public:
    void sortColors(vector<int>& nums)
    {
        if (nums.size() < 1) return;
        int n = nums.size();

        // input element is an integer in the range 0 to k
        const int k = 2;
        //auxiliary array
        vector<int> C(k+1, 0);

        // counting
        for (size_t i = 0; i < nums.size(); i++)
            C[ nums[i] ]++;

        // 算导上面 计数排序的简化版本. 没有用到累加和数组 C[i] += C[i-1];
        int j = 0;
        for (int i = 0; i <= k; i++)
            for ( ; j<n && C[i]>0; j++)
            {
                nums[j] = i;   // 因为int型比较简单，所以直接放key值咯。 如果每个key还对应着许多卫星数据的话，就没办法这么赋值咯.
                C[i]--;
            }
    }
};

// 算导上面标准的计数排序(Counting Sort)，考虑到了卫星数据
// C-累加和数组； 以及额外用了一个辅助数组来保存数据 （ 直接修改原数组会有问题）
// 时间复杂度O(N+K),  空间复杂度 O(N)
class Solution2
{
public:
    void sortColors(vector<int>& nums)
    {
        if (nums.size() < 1) return;
        int n = nums.size();

        // input element is an integer in the range 0 to k
        const int k = 2;
        //auxiliary array
        vector<int> C(k + 1, 0);
        vector<int> B(n, 0);

        // counting
        // C[i] now contains the number of elements equal to i
        for (size_t i = 0; i < nums.size(); i++)
            C[nums[i]]++;

        // cumulative sum
        // C[i] now contains the number of elements less than or equal to i
        for (int i = 1; i <= k; i++)
            C[i] += C[i - 1];

        //
        for (int j = n - 1; j >= 0; j--)
        {
            B[C[nums[j]] -1] = nums[j];   // notice index from 0 but counting number from 1
            C[nums[j]]--;
        }

        nums = B;
    }
};

//方法3： 根据快速排序的partition思想, 设置几个指针，各种具有自己的含义. (本题想考察的方法. 一遍扫描)
class Solution3
{
public:
    void sortColors(vector<int>& nums)
    {
        if (nums.size() < 1) return;
        int n = nums.size();

        //
        int red = 0, blue = 0;
        int white = n-1;

        for (int i = 0; i <=white; )
        {
            // red
            if (0 == nums[i])
            {
                swap(nums[i], nums[red]);
                red++;
                i++;
            }
            else if (1 == nums[i])  // blue
            {
                swap(nums[i], nums[red + blue]);
                blue++;
                i++;
            }
            else  // white
            {
                swap(nums[i], nums[white]);
                white--;
            }
        }
    }
};

// 类似方法3. 最先想出来的版本， 与方面的不同，这3个指针记录的都是 各自元素的个数。 red,  red+blue, red+blue+white是正确的安放位置。
// 需额外注意的是red的放置时，可能将blue元素丢到后面去了
class Solution4
{
public:
    void sortColors(vector<int>& nums)
    {
        if (nums.size() < 1) return;
        int n = nums.size();

        //  three pointer.  red pointer the last position to place red-0 element, etc.
        int red = 0, blue = 0, white=0;
        for (int i = 0; i < n; i++)
        {
            // red
            if (0 == nums[i])
            {
                swap(nums[i], nums[red]);             // nums[i] 0  <---> nums[red] current number, may be 1

                if (1 == nums[i])                             // if it is 1, then swap it with possible 2 or itself.
                    swap(nums[i], nums[red+blue]);

                red++;
            }
            else if (1 == nums[i])  // blue
            {
                swap(nums[i], nums[red + blue]);
                blue++;
            }
            else  // white
            {
                //swap(nums[i], nums[red+blue+white]);
                white++;
            }
        }
    }
};

int main(int argc, char *argv[])
{
    //input section
    //vector<int> nums = { 0, 1, 2, 0, 2, 2, 1, 0, 1, 0 };
    //vector<int> nums = {2, 0 };
    vector<int> nums = { 1, 0 };

    //
    Solution4 solution;
    clock_t start_time = clock();


    //
    solution.sortColors(nums);
    printVector(nums);

    clock_t end_time = clock();

    // Print Running Time
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;

    return 0;
}
