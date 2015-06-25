/*
Insertion Sort List
Sort a linked list using insertion sort.

======================================
题目链接: https://leetcode.com/problems/insertion-sort-list/

一句话总结:  链表的插入排序。 用到4个指针~ 名字取的好，思路会更清晰( last_sorted, first_unsorted, current, preceding)
             Solution2,3是插入排序的数组实现，供参考
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    // Time Complexity: O(N^2); Space Complexity: O(1)
    ListNode* insertionSortList(ListNode* head)
    {
        ListNode *first_unsorted; // the first unsorted node to be inserted
        ListNode *last_sorted;    // tail of the sorted sublist
        ListNode *current;        // used to traverse the sorted sublist
        ListNode *preceding;      // one position before current

        if ( NULL != head )
        {
            last_sorted = head;
            while ( NULL != last_sorted->next )
            {
                first_unsorted = last_sorted->next;

                // consider two special situations
                // this node insert before head
                if (first_unsorted->val < head->val)
                {
                    last_sorted->next = first_unsorted->next;
                    first_unsorted->next = head;
                    head = first_unsorted;
                }
                else if ( first_unsorted->val >= last_sorted->val )
                {
                    // this node could just add to the end of sorted sublist
                    last_sorted = first_unsorted;
                }
                else
                {
                    preceding = head;
                    current = preceding->next;

                    while (first_unsorted->val >= current->val)
                    {
                        preceding = current;
                        current = preceding->next;
                    }

                    // Guarantee before current equals to first_unsored, the above while loop must be terminated.
                    // insert first_unsorted node between preceding and current
                    last_sorted->next = first_unsorted->next;
                    first_unsorted->next = current;
                    preceding->next = first_unsorted;
                }
            }
        }

        return head;
    }
};


// For Reference: 插入排序的数组实现
class Solution2
{
public:
    // Time Complexity: O(N^2); Space Complexity: O(1)
    void insertionSort(vector<int>& nums)
    {
        // no need to sort
        if (nums.size() < 1) return;

        int n = nums.size();
        int first_unsorted;   // position of first unsorted entry
        int position;         // searches sorted part of list
        int current;          // holds the entry temporarily removed from list

        for (first_unsorted=1; first_unsorted < n; first_unsorted++)
            if ( nums[first_unsorted] < nums[first_unsorted-1])
            {
                position = first_unsorted;
                // pull unsorted entry out of the list
                current = nums[first_unsorted];
                do
                {
                    // shift all entries until the proper entry position is found.
                    nums[position] = nums[position-1];
                    position--;
                    // consider the situtaion that current belongs in the first position of the list.
                }while (position>0 && nums[position-1]>current);  // no sentinel

                nums[position] = current;
            }
    }
};

// 写的很简洁哈，也没有用哨兵。
// 效率的话，用到的是交换两个数字而不是赋值移动。可能慢一点点~
class Solution3
{
public:
    void insertionSort(vector<int>& nums)
    {
        int n = nums.size();
        for (int i=1; i<n; i++)
            for (int j=i; j>0 && nums[j]<nums[j-1]; j--)  // insert nums[i] among nums[i-1], nums[i-2], nums[i-3] ...
                swap(nums[j], nums[j-1]);
    }
};

int main(int argc, char *argv[])
{
    //input section
    int a[] = { 5, 3, 2 };

    struct ListNode *head = new ListNode(5, NULL);
    head->next = new ListNode(3, NULL);
    head->next->next = new ListNode(2, NULL);

    //
    Solution solution;
    clock_t start_time = clock();

    //
    head = solution.insertionSortList(head);

    // output
    struct ListNode *current = head;
    while (current)
    {
        cout << current->val << "  ";
        current = current->next;
    }
    cout << endl;

    current = head;
    while (current)
    {
        struct ListNode *temp = current->next;
        delete current;
        current = temp;
    }
    current = NULL;
    head = NULL;


    clock_t end_time = clock();

    // Print Running Time
    cout << "Running time: ";
    cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    char x;
    cin >> x;

    return 0;
}
