//
// Created by 李洪良 on 2023/6/5.
//

#ifndef DAILY_PRACTICE_MY_ORDER_H
#define DAILY_PRACTICE_MY_ORDER_H

#include <iostream>
#include <vector>
#include <stack>

class myQuickSort {
public:
    void quickSort(std::vector<int> &nums) {
        if (nums.empty()) {
            return;
        }
        quickSort(nums, 0, nums.size() - 1);
    }

    int topK(std::vector<int> &nums, int  k) {
        quickSelect(nums, 0, nums.size()-1, k-1);
    }


    void quickSortStack(std::vector<int> &nums) {
        std::stack<std::pair<int,int>> my_stack;
        my_stack.emplace(0, nums.size()-1);
        while (!my_stack.empty()) {
            auto [left, right] = my_stack.top();
            my_stack.pop();
            if (left >= right) {
                continue;
            }
            int mid_index = partition(nums, left, right);

            my_stack.emplace(0, mid_index-1);
            my_stack.emplace(mid_index+1, right);
        }
    }

private:
    int partition(std::vector<int> &nums, int left, int right) {
        int mid = nums.at(left);
        int i = left + 1, j = right;
        while (i <= j) {
            if (nums.at(i) <= mid) {
                ++i;
            } else if (nums.at(j) > mid) {
                --j;
            } else {
                std::swap(nums.at(i++), nums.at(j--));
            }
        }
        std::swap(nums.at(left) ,nums.at(j));
        return j;
    }

    void quickSort(std::vector<int> &nums, int left, int right) {
        if (left >= right) {
            return;
        }

        int mid_index = partition(nums, left, right);
        std::cout<<mid_index<<std::endl;
        quickSort(nums, left, mid_index - 1);
        quickSort(nums, mid_index + 1, right);
    }



    int quickSelect(std::vector<int> &nums, int left, int right, int k) {
        if (left == right) {
            return nums.at(left);
        }
        int mid = partition(nums, left, right);
        if (mid == k) {
            return nums.at(k);
        } else if (mid < k) {
            return quickSelect(nums, mid+1, right, k);
        } else {
            return quickSelect(nums, left, mid-1, k);
        }
    }
};

class binarySearch {
public:
    // 搜索旋转排序数组
    int search(std::vector<int> nums, int target) {
        int n = nums.size();
        int left = 0, right = nums.size()-1;
        while (left<right) {
            int mid = left +(right-left)/2;
            if(nums.at(mid) > nums.at(right)) {
                left=mid+1;
            } else {
                right=mid;
            }
        }

        int min_index = left;
        left =0;
        right = min_index-1;
        while (left<=right) {
            int mid = left+(right-left)/2;
            if(nums.at(mid) == target) {
                return mid;
            } else if(nums.at(mid) <= target) {
                left=mid+1;
            } else {
                right =mid-1;
            }
        }


        left = min_index;
        while (left<=right) {
            int mid=left+(right-left)/2;
            if(nums.at(mid) == target) {
                return mid;
            } else if(nums.at(mid) <= target) {
                left=mid+1;
            } else {
                right =mid-1;
            }
        }

        return -1;

    }
};

int order_test() {
    myQuickSort sort;
    std::vector<int> nums = {3, 5, 2, 6, 9, 8};
    sort.quickSortStack(nums);
    std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, " "));
}


#endif //DAILY_PRACTICE_MY_ORDER_H
