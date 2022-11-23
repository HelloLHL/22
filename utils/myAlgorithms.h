//
// Created by 李洪良 on 2022/11/23.
//

#ifndef DAILY_PRACTICE_MYALGORITHMS_H
#define DAILY_PRACTICE_MYALGORITHMS_H
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    // 二分查找
    /*
     * 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
     * */
    int search(vector<int>& nums, int target) {
        int left = -1, right = nums.size();
        while (left + 1 != right) {
            int mid = (left+right) >> 1;
            if (nums.at(mid) == target) {
                return mid;
            } else if(nums.at(mid) <= target) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return -1;
    }

    int search2(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        while (left <= right) {
            int mid = left + (right - left) /2;
            if (nums.at(mid) == target) {
                return mid;
            } else if(nums.at(mid) > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }

    bool isBadVersion(int mid) {
        int i = mid - 1;
        if (mid < 0|| mid >= str.size()) {
            return false;
        }
        if (str.at(mid) == 't') {
            return true;
        } else {
            return false;
        }
    }

    // 查找第一个t
    int firstBadVersion(int n) {
        int left = 1, right = n;
        while (left < right) {
            int mid = left + ((right-left) >> 1);
            if(isBadVersion(mid)) {
                right = mid;
            } else {
                left = mid+1;
            }
        }
        return right;
    }

    /*
     * 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
     * */
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1, ans = n;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (nums.at(mid) >= target) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

    void myTest() {
        /*
        str = "fffftt";
        vector<int> nums = {-1,0,3,5,9,12};
        int res = search(nums, 2);
        std::cout<<res<<endl;
         */
        vector<int> nums = {1,3,5,6};

    }

private:
    string str;
};



#endif //DAILY_PRACTICE_MYALGORITHMS_H
