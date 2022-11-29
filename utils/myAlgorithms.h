//
// Created by 李洪良 on 2022/11/23.
//

#ifndef DAILY_PRACTICE_MYALGORITHMS_H
#define DAILY_PRACTICE_MYALGORITHMS_H
#include <vector>
#include <iostream>
#include <cmath>
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

    // 给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n - 1, pos = n - 1;
        vector<int> res(n);
        while (left <= right) {
            if (pow(nums.at(left),2) < pow(nums.at(right), 2)) {
                res.at(pos) = pow(nums.at(right),2);
                --right;
            } else {
                res.at(pos) = pow(nums.at(left),2);
                ++left;
            }
            --pos;
        }
        return res;
    }

    // 给你一个数组，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            int pos = (i+k) % n;
            res.at(pos) = nums.at(i);
        }
        nums.assign(res.begin(), res.end());
        return;
    }

    void rotate2(vector<int>& nums, int k) {
        int n = nums.size();
        int m = k % n;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+m);
        reverse(nums.begin()+m, nums.end());
    }

    // 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序
    void moveZeroes(vector<int>& nums) {
        int notZero = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums.at(i) == 0) {
                continue;
            }
            nums[notZero++] = nums.at(i);
        }

        for (int i = notZero; i < nums.size(); ++i) {
            nums[i] = 0;
        }
    }

    // 给你一个下标从 1 开始的整数数组 numbers ，该数组已按 非递减顺序排列  ，请你从数组中找出满足相加之和等于目标数 target 的两个数
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers.at(right) + numbers.at(left);
            if (sum == target) {
                break;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return vector<int>{left+1, right+1};
    }


    void myTest() {
        /*
        str = "fffftt";
        vector<int> nums = {-1,0,3,5,9,12};
        int res = search(nums, 2);
        std::cout<<res<<endl;

        vector<int> nums = {-4,-1,0,3,10};
        vector<int> res = sortedSquares(nums);

        vector<int> nums = {1,2,3,4,5,6,7};
        rotate2(nums, 3);
        std::copy(nums.begin(),nums.end(), std::ostream_iterator<int>(std::cout, " "));
         */
        vector<int> nums = {2,7,11,15};
        vector<int> res = twoSum(nums, 9);
        std::copy(res.begin(),res.end(), std::ostream_iterator<int>(std::cout, " "));


    }

private:
    string str;
};



#endif //DAILY_PRACTICE_MYALGORITHMS_H
