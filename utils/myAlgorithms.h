//
// Created by 李洪良 on 2022/11/23.
//

#ifndef DAILY_PRACTICE_MYALGORITHMS_H
#define DAILY_PRACTICE_MYALGORITHMS_H
#include <vector>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <set>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;


class Solution {
public:
    // 二分查找
    /*
     * 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
     * */
    int search(vector<int> &nums, int target) {
        int left = -1, right = nums.size();
        while (left + 1 != right) {
            int mid = (left + right) >> 1;
            if (nums.at(mid) == target) {
                return mid;
            } else if (nums.at(mid) < target) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return -1;
    }

    int search2(vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums.at(mid) == target) {
                return mid;
            } else if (nums.at(mid) > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }

    bool isBadVersion(int mid) {
        int i = mid - 1;
        if (mid < 0 || mid >= str.size()) {
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
            int mid = left + ((right - left) >> 1);
            if (isBadVersion(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return right;
    }

    /*
     * 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
     * */
    int searchInsert(vector<int> &nums, int target) {
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
    vector<int> sortedSquares(vector<int> &nums) {
        int n = nums.size();
        int left = 0, right = n - 1, pos = n - 1;
        vector<int> res(n);
        while (left <= right) {
            if (pow(nums.at(left), 2) < pow(nums.at(right), 2)) {
                res.at(pos) = pow(nums.at(right), 2);
                --right;
            } else {
                res.at(pos) = pow(nums.at(left), 2);
                ++left;
            }
            --pos;
        }
        return res;
    }

    // 给你一个数组，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
    void rotate(vector<int> &nums, int k) {
        int n = nums.size();
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            int pos = (i + k) % n;
            res.at(pos) = nums.at(i);
        }
        nums.assign(res.begin(), res.end());
        return;
    }

    void rotate2(vector<int> &nums, int k) {
        int n = nums.size();
        int m = k % n;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + m);
        reverse(nums.begin() + m, nums.end());
    }

    // 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序
    void moveZeroes(vector<int> &nums) {
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
    vector<int> twoSum(vector<int> &numbers, int target) {
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
        return vector<int>{left + 1, right + 1};
    }

    /*
     * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
    */
    std::vector<int> twoSum2(std::vector<int> &nums, int target) {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            auto res = map.find(target - nums.at(i));
            if (res != map.end()) {
                return {res->second, i};
            }
            map.emplace(nums.at(i), i);
        }
        return {};
    }

    // 编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 s 的形式给出。
    void reverseString(vector<char> &s) {
        int num = s.size();
        int n = num / 2;
        for (int i = 0; i < n; ++i) {
            swap(s.at(i), s.at(num - i - 1));
        }
    }

    // 给定一个字符串 s ，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。
    string reverseWords(string s) {
        int num = s.size();
        int i = 0;
        while (i < num) {
            int start = i;
            while (i < num && s.at(i) != ' ') {
                i++;
            }
            int left = start, right = i - 1;
            while (left < right) {
                swap(s.at(left), s.at(right));
                left++;
                right--;
            }
            while (i < num && s.at(i) == ' ') {
                i++;
            }
        }
        return s;
    }

    struct ListNode {
        int val;
        ListNode *next;

        ListNode() : val(0), next(nullptr) {}

        ListNode(int x) : val(x), next(nullptr) {}

        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *head = nullptr, *cur = nullptr;
        int carry = 0;
        while (l1 || l2) {
            int n1 = l1 ? l1->val : 0;
            int n2 = l2 ? l2->val : 0;
            int sum = n1 + n2 + carry;
            if (!head) {
                head = cur = new ListNode(sum % 10);
            } else {
                cur->next = new ListNode(sum % 10);
                cur = cur->next;
            }
            carry = sum / 10;
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        if (carry > 0) {
            cur->next = new ListNode(carry);
        }
        return head;
    }


    // 给定一个头结点为 head 的非空单链表，返回链表的中间结点。
    ListNode *middleNode(ListNode *head) {
        ListNode *slow = head;
        ListNode *quick = head;
        while (quick != nullptr && quick->next != nullptr) {
            slow = slow->next;
            quick = quick->next->next;
        }
        return slow;
    }

    // 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *fast = head;
        ListNode *dummy = new ListNode(0, head);
        ListNode *slow = dummy;
        while (n-- != 0) {
            fast = fast->next;
        }
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        head = dummy->next;
        delete dummy;
        return head;
    }

    void bucktrack(vector<int> nums, vector<vector<int>> &res, vector<bool> &used, vector<int> &path) {
        if (path.size() == nums.size()) {
            res.emplace_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) {
                continue;
            }

            used[i]=true;
            path.emplace_back(nums.at(i));
            bucktrack(nums, res, used,path);
            path.pop_back();
            used[i]=false;
        }
    }

    // 全排列
    vector<vector<int>> permute(vector<int> nums) {
        vector<vector<int>> res;
        vector<bool> used(nums.size(), false);
        vector<int> path;
        bucktrack(nums, res, used,path);
        return res;
    }

    // 合并区间
    vector<vector<int>> mergeRange(vector<vector<int>>intervals) {
        if (intervals.empty()) {
            return intervals;
        }
        std::sort(intervals.begin(), intervals.end());

        vector<vector<int>> res;
        res.emplace_back(intervals[0]);
        for (auto &item:intervals) {
            if (item[0] <= res.back()[1]) {
                res.back()[1] = std::max(item[1], res.back()[1]);
            } else {
                res.emplace_back(item);
            }
        }
        return res;
    }

    // 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> occ;
        int right = 0; //  右指针，相当于在字符串左侧，还未移动
        int n = s.size();
        int ans = 0;    //  最长度
        for (int i = 0; i < n; ++i) {
            if (i != 0) {
                // 左指针向右移动一位，移除一个字符
                occ.erase(s.at(i - 1));
            }
            while (right  < n && occ.count(s.at(right )) == 0) {
                occ.insert(s.at(right ));
                right++;
            }
            ans = std::max(ans, (int) occ.size());
        }
        return ans;
    }

    // 给你两个字符串 s1 和 s2 ，写一个函数来判断 s2 是否包含 s1 的排列。如果是，返回 true ；否则，返回 false 。
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) {
            return false;
        }
        int n = s1.length();
        int feq1[26] = {0};
        int feq2[26] = {0};
        for (int i = 0; i < n; ++i) {
            feq1[s1.at(i) - 'a']++;
            feq2[s2.at(i) - 'a']++;
        }
        for (int i = n; i < s2.length(); ++i) {
            if (memcmp(feq1, feq2, sizeof feq1) == 0) {
                return true;
            }
            feq2[s2.at(i - n) - 'a']--;
            feq2[s2.at(i) - 'a']++;
        }
        return memcmp(feq1, feq2, sizeof feq1) == 0;
    }

    //
    pair<int, int> expandAroundCenter(const string &s, int left, int right) {
        while (left >= 0 && right < s.size() && s.at(right) == s.at(left)) {
            --left;
            ++right;
        }
        return {++left, --right};
    }

    // 最长回文子串
    string longestPalindrome(string s) {
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); ++i) {
            auto[left1, right1] = expandAroundCenter(s, i, i);
            auto[left2, right2] = expandAroundCenter(s, i, i + 1);

            if ((right1 - left1) > (end - start)) {
                start = left1;
                end = right1;
            }
            if ((right2 - left2) > (end - start)) {
                start = left2;
                end = right2;
            }
        }
        return s.substr(start, end - start + 1);
    }

    // 最长递增子序列
    int lengthOfLis(vector<int> nums) {
        vector<int> Lis;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = lower_bound(Lis.begin(), Lis.end(), nums.at(i));
            if (it==Lis.end()) {
                Lis.emplace_back(nums.at(i));
            } else{
                *it= nums.at(i);
            }
        }
        return Lis.size();
    }
    // 最大数 给定一组非负整数 nums，重新排列每个数的顺序（每个数不可拆分）使之组成一个最大的整数。
    string  largestNum(vector<int> nums){
        vector<string> num_string;
        for (auto &num:nums) {
            num_string.emplace_back(std::to_string(num));
        }
        std::sort(num_string.begin(), num_string.end(), [](string s1, string s2){
            return s1+s2>s2+s1;
        });
        if (num_string.at(0) == "0") {
            return "0";
        }
        string res= "";
        for (auto & item:num_string) {
            res+=item;
        }
        return res;
    }

    // 图像渲染
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color) {
        int oldColor = image[sr][sc];
        if (oldColor != color) {
            fill(image, sr, sc, oldColor, color);
        }

        return image;
    }

    const vector<pair<int, int>> label{{0,  1},
                                       {1,  0},
                                       {-1, 0},
                                       {0,  -1}};

    void fill(vector<vector<int>> &image, int sr, int sc, int oldColor, int NewColor) {
        if (sr < 0 || sr >= image.size() || sc < 0 || sc >= image[0].size() || image[sr][sc] != oldColor) {
            return;
        }

        image[sr][sc] = NewColor;
        for (const auto &item: label) {
            fill(image, sr + item.first, sc + item.second, oldColor, NewColor);
        }
    }

    // 岛屿最大值
    int maxAreaOfIsland(vector<vector<int>> &grid) {
        int ans = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                queue<pair<int, int>> myQueue;
                myQueue.emplace(i, j);
                int cur = 0;
                while (!myQueue.empty()) {
                    auto pos = myQueue.front();
                    myQueue.pop();
                    if (pos.first < 0 || pos.first >= grid.size() || pos.second < 0 || pos.second >= grid[0].size() ||
                        grid[pos.first][pos.second] != 1) {
                        continue;
                    }
                    ++cur;
                    grid[pos.first][pos.second] = 0;
                    for (const auto &item: label) {
                        myQueue.emplace(pos.first + item.first, pos.second + item.second);
                    }
                }
                ans = max(ans, cur);
            }
        }
        return ans;
    }


    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode() : val(0), left(nullptr), right(nullptr) {}

        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    // 合并两个二叉树
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        if (!root1) {
            return root2;
        }
        if (!root2) {
            return root2;
        }
        TreeNode *merge = new TreeNode(root2->val + root1->val);
        merge->left = mergeTrees(root1->left, root2->left);
        merge->right = mergeTrees(root1->right, root2->right);
        return merge;
    }

    class Node {
    public:
        int val;
        Node *left;
        Node *right;
        Node *next;

        Node() : val(0), left(NULL), right(NULL), next(NULL) {}

        Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

        Node(int _val, Node *_left, Node *_right, Node *_next)
                : val(_val), left(_left), right(_right), next(_next) {}
    };

    // 充每个节点的下一个右侧节点指针  层次遍历
    Node *connect(Node *root) {
        if (!root) {
            return root;
        }
        queue<Node *> myQueue;
        myQueue.emplace(root);
        while (!myQueue.empty()) {
            int n = myQueue.size();
            for (int i = 0; i < n; ++i) {
                Node *curNode = myQueue.front();
                myQueue.pop();
                if (i < n - 1) {
                    curNode->next = myQueue.front();
                }
                if (curNode->left != nullptr) {
                    myQueue.emplace(curNode->left);
                }
                if (curNode->right != nullptr) {
                    myQueue.emplace(curNode->right);
                }
            }
        }
        return root;
    }

    // 01矩阵
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> myQueue;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) {
                    dis[i][j] = 0;
                    myQueue.emplace(i, j);
                }
            }
        }
        while (!myQueue.empty()) {
            auto pos = myQueue.front();
            myQueue.pop();
            for (const auto &item: label) {
                int curI = pos.first + item.first, curJ = pos.second + item.second;
                if (curI < 0 || curJ < 0 ||
                    curI >= m || curJ >= n || dis[curI][curJ] <= dis[pos.first][pos.second] + 1) {
                    continue;
                }
                dis[curI][curJ] = dis[pos.first][pos.second] + 1;
                myQueue.emplace(curI, curJ);
            }
        }
        return dis;
    }

    // 腐烂的橘子
    int orangesRotting(vector<vector<int>> &grid) {
        int m = grid.size();
        int n = grid[0].size();
        int refresh = 0;
        queue<pair<int, int>> myQueue;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    myQueue.emplace(i, j);
                } else if (grid[i][j] == 1) {
                    refresh++;
                }
            }
        }

        int time = 0;
        while (!myQueue.empty()) {
            int queueSize = myQueue.size();
            for (int i = 0; i < queueSize; ++i) {
                auto pos = myQueue.front();
                myQueue.pop();
                for (const auto &item: label) {
                    int curI = pos.first + item.first, curJ = pos.second + item.second;
                    if (curI < 0 || curJ < 0 || curI >= m || curJ >= n || grid[curI][curJ] != 1) {
                        continue;
                    }
                    grid[curI][curJ] = 2;
                    myQueue.emplace(curI, curJ);
                    refresh--;
                }
            }
            if (!myQueue.empty()) {
                ++time;
            }
        }
        return refresh == 0 ? time : -1;
    }

    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        if (list1 == nullptr) {
            return list2;
        }
        if (list2 == nullptr) {
            return list1;
        }
        if (list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }

    ListNode *mergeTwoLists2(ListNode *list1, ListNode *list2) {
        ListNode *newHead = new ListNode(0);
        ListNode *tail = newHead;
        while (list2 && list1) {
            if (list1->val < list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        if (list1) {
            tail->next = list1;
        }
        if (list2) {
            tail->next = list2;
        }
        return newHead->next;
    }

    ListNode *reverseList(ListNode *head) {
        ListNode *pre = nullptr;
        ListNode *cur = head;
        while (cur) {
            ListNode *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }

        return pre;
    }

    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> item;
        dfs(ans, item, n, k, 1);
        return ans;
    }

    void dfs(vector<vector<int>> &ans, vector<int> &item, int n, int k, int start) {
        if (item.size() == k) {
            ans.emplace_back(item);
            return;
        }
        for (int i = start; i <= n; ++i) {
            item.emplace_back(i);
            dfs(ans, item, n, k, i + 1);
            item.pop_back();
        }
        return;
    }

    // 整数除法
    // 给定两个整数 a 和 b ，求它们的除法的商 a/b ，要求不得使用乘号 '*'、除号 '/' 以及求余符号 '%' 。
    int divide(int a, int b) {
        if (a == INT_MIN && b == -1) return INT_MAX;
        if (a == INT_MIN && b == 1) return INT_MIN;
        int sign = (a > 0) ^ (b > 0) ? -1 : 1;

        if (a > 0) a = -a;
        if (b > 0) b = -b;//换成负数运算，因为都换成正数INT_MIN会溢出

        unsigned int res = 0;
        while (a <= b) {
            int d = b, c = 1; // d为当前除数，c为当前商
            while (d >= INT_MIN - d && d >= a - d) { // 通过第一个条件防止d + d溢出
                d += d;
                c += c;
            }
            a -= d;
            res += c;
        }
        return sign == 1 ? res : -res;
    }

    // 找到重复数字
    int findRepeatNumber(vector<int> &nums) {
        int i = 0;
        while (i < nums.size()) {
            if (nums[i] == i) {
                i++;
                continue;
            }
            if (nums[nums[i]] == nums[i])
                return nums[i];
            swap(nums[i], nums[nums[i]]);
        }
        return -1;
    }

    // 二进制加法
    string addBinary(string a, string b) {
        string ans;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        int n = max(a.size(), b.size()), carry = 0;
        for (size_t i = 0; i < n; ++i) {
            carry += i < a.size() ? (a.at(i) == '1') : 0;
            carry += i < b.size() ? (b.at(i) == '1') : 0;
            ans.push_back((carry % 2) ? '1' : '0');
            carry /= 2;
        }

        if (carry) {
            ans.push_back('1');
        }
        reverse(ans.begin(), ans.end());

        return ans;
    }

    string replaceSpace(string s) {
        int space = 0;
        for (const auto &item: s) {
            if (item == ' ') {
                ++space;
            }
        }
        int oldIndex = s.size() - 1;
        int newSize = s.size() + 2 * space;
        s.resize(newSize);
        int newIndex = newSize - 1;
        while (oldIndex >= 0 && newIndex >= 0) {
            if (s.at(oldIndex) == ' ') {
                s.at(newIndex--) = '0';
                s.at(newIndex--) = '2';
                s.at(newIndex--) = '%';
            } else {
                s.at(newIndex--) = s.at(oldIndex);
            }
            oldIndex--;
        }
        return s;
    }

    string reverseLeftWords(string s, int n) {
        std::reverse(s.begin(), s.begin() + n);
        std::reverse(s.begin() + n, s.end());
        std::reverse(s.begin(), s.end());
        return s;
    }

    bool unsignedInteger(const string &s, int &index) {
        int temp = index;
        while (index < s.size() && s.at(index) >= '0' && s.at(index) <= '9') {
            ++index;
        }
        return index > temp;
    }

    bool integer(const string &s, int &index) {
        if (s.at(index) == '+' || s.at(index) == '-') {
            ++index;
        }
        return unsignedInteger(s, index);

    }

    bool isNumber(string s) {
        // 空串
        if (s.empty()) {
            return false;
        }
        int index = 0;
        // 去除前面空格
        while (index < s.size() && s.at(index) == ' ') {
            ++index;
        }

        int endIndex = s.size() - 1;
        // 去除后面空格
        while (endIndex >= 0 && s.at(endIndex) == ' ') {
            --endIndex;
        }

        ++endIndex;
        bool flag = integer(s, index);
        if (s.at(index) == '.') {
            ++index;
            flag = unsignedInteger(s, index) || flag;
        }
        if (s.at(index) == 'e' || s.at(index) == 'E') {
            ++index;
            flag = integer(s, index) && flag;
        }

        return flag && (index == endIndex);
    }

    vector<int> reversePrint(ListNode *head) {
        int n = 0;
        ListNode *curNode = head;
        while (curNode != nullptr) {
            curNode = curNode->next;
            ++n;
        }
        vector<int> arr(n);
        curNode = head;
        for (int i = n - 1; i >= 0; --i) {
            arr.at(i) = curNode->val;
            curNode = curNode->next;
        }
        return arr;
    }

    ListNode *deleteNode(ListNode *head, int val) {
        ListNode *myhead = new ListNode(0);
        myhead->next = head;
        ListNode *curNode = head, *pre = myhead;

        while (curNode != nullptr) {
            if (curNode->val == val) {
                curNode = curNode->next;
                pre->next = curNode;
                break;
            } else {
                curNode = curNode->next;
                pre = pre->next;
            }
        }
        return myhead->next;
    }

    ListNode *getKthFromEnd(ListNode *head, int k) {
        ListNode *curNode = head;
        while (k > 0) {
            if (curNode->next == nullptr) {
                return head;
            }
            curNode = curNode->next;
            --k;
        }
        while (curNode != nullptr) {
            curNode = curNode->next;
            head = head->next;
        }
        return head;
    }

    int getListNodeLength(ListNode *node) {
        int n = 0;
        while (node != nullptr) {
            node = node->next;
            ++n;
        }
        return n;
    }

    // 获取公共节点
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lengthA = getListNodeLength(headA);
        int lengthB = getListNodeLength(headB);

        ListNode *lengthNode = lengthA > lengthB ? headA : headB;
        ListNode *shortNode = lengthA <= lengthB ? headA : headB;

        int absValue = std::abs(lengthA - lengthB);
        while (absValue > 0) {
            lengthNode = lengthNode->next;
            --absValue;
        }

        while (lengthNode != nullptr && shortNode != nullptr) {
            if (lengthNode == shortNode) {
                return lengthNode;
            }
            lengthNode = lengthNode->next;
            shortNode = shortNode->next;
        }
        return nullptr;
    }

    vector<int> exchange(vector<int> &nums) {
        vector<int> res(nums.size());
        int left = 0, right = nums.size() - 1;
        for (const auto &item: nums) {
            if (item % 2 == 0) {
                res.at(right--) = item;
            } else {
                res.at(left++) = item;
            }
        }
        return res;
    }

    string reverseWords2(string s) {
        std::reverse(s.begin(), s.end());

        int index = 0;  //  实际的index
        for (int start = 0; start < s.size(); ++start) {
            if (s.at(start) == ' ') {
                continue;
            }
            if (index != 0) {
                s.at(index++) = ' ';
            }
            int end = start;
            while (end < s.size() && s.at(end) != ' ') {
                s.at(index++) = s.at(end++);
            }
            std::reverse(s.begin() + index - (end - start), s.begin() + index);
            start = end;
        }
        s.erase(s.begin() + index, s.end());
        return s;
    }

    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        vector<int> ans;
        if (matrix.empty()) {
            return ans;
        }
        int lengthF = matrix.at(0).size() - 1;
        int widthF = matrix.size() - 1;

        int indexLeft = 0, indexRight = lengthF, indexUp = 0, indexDown = widthF;

        while (true) {
            for (int i = indexLeft; i <= indexRight; ++i) {
                ans.emplace_back(matrix.at(indexUp).at(i));
            }

            if (++indexUp > indexDown) {
                break;
            }

            for (int i = indexUp; i <= indexDown; ++i) {
                ans.emplace_back(matrix.at(i).at(indexRight));
            }

            if (--indexRight < indexLeft) {
                break;
            }

            for (int i = indexRight; i >= indexLeft; --i) {
                ans.emplace_back(matrix.at(indexDown).at(i));
            }
            if (--indexDown < indexUp) {
                break;
            }
            for (int i = indexDown; i >= indexUp; --i) {
                ans.emplace_back(matrix.at(i).at(indexLeft));
            }
            if (++indexLeft > indexRight) {
                break;
            }
        }
        return ans;
    }

    // 统计一个数字在排序数组中出现的次数。
    int search3(vector<int> &nums, int target) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }
        int index1 = -1, index2 = -1;
        int right = n - 1, left = 0;
        while (left <= right) {
            int mid = (right + left) >> 1;
            if (nums.at(mid) == target) {
                index1 = mid;
                right = mid - 1;
            } else if (nums.at(mid) > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (index1 == -1) {
            return 0;
        }
        left = 0, right = n - 1;
        while (left <= right) {
            int mid = (right + left) >> 1;
            if (nums.at(mid) == target) {
                index2 = mid;
                left = mid + 1;
            } else if (nums.at(mid) > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return index2 - index1;

    }

    int missingNumber(vector<int> &nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums.at(i) != i) {
                return i;
            }
        }
        return n;
    }

    // 旋转数组的最小数字
    int findMin(vector<int> &numbers) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (numbers.at(mid) < numbers.at(right)) {
                right = mid;
            } else if (numbers.at(mid) > numbers.at(right)) {
                left = mid + 1;
            } else {
                --right;
            }
        }
        return numbers.at(left);
    }

    char firstUniqChar(string s) {
        unordered_map<int, int> hashTab;
        for (const auto &item: s) {
            ++hashTab[item];
        }
        for (const auto &item: s) {
            if (hashTab[item] == 1) {
                return item;
            }
        }
        return ' ';

    }

    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> res;
        if (root == nullptr) {
            return res;
        }
        queue<TreeNode *> nodeQueue;
        nodeQueue.emplace(root);
        while (!nodeQueue.empty()) {
            int n = nodeQueue.size();
            vector<int> tempLevel;
            for (int i = 0; i < n; ++i) {
                TreeNode *temp = nodeQueue.front();
                nodeQueue.pop();
                tempLevel.emplace_back(temp->val);
                if (temp->left != nullptr) { nodeQueue.emplace(temp->left); }
                if (temp->right != nullptr) { nodeQueue.emplace(temp->right); }
            }
            res.push_back(tempLevel);
        }
        return res;
    }

    TreeNode *mirrorTree(TreeNode *root) {
        if (root == nullptr) {
            return nullptr;
        }
        queue<TreeNode *> myQueue;
        myQueue.emplace(root);
        while (!myQueue.empty()) {
            int n = myQueue.size();
            for (int i = 0; i < n; ++i) {
                TreeNode *temp = myQueue.front();
                myQueue.pop();
                std::swap(temp->right, temp->left);
                if (temp->right != nullptr) {
                    myQueue.emplace(temp->right);
                }
                if (temp->left != nullptr) {
                    myQueue.emplace(temp->left);
                }
            }
        }
        return root;
    }

    bool checkSameNTree(TreeNode *root1, TreeNode *root2) {
        queue<TreeNode *> myQueue;
        myQueue.emplace(root1);
        myQueue.emplace(root2);
        while (!myQueue.empty()) {
            TreeNode *temp1 = myQueue.front();
            myQueue.pop();
            TreeNode *temp2 = myQueue.front();
            myQueue.pop();

            if (temp1 == nullptr && temp2 == nullptr) {
                continue;
            }

            if (temp1 == nullptr || temp2 == nullptr || temp1->val != temp2->val) {
                return false;
            }
            myQueue.emplace(temp1->left);
            myQueue.emplace(temp2->right);

            myQueue.emplace(temp1->right);
            myQueue.emplace(temp2->left);
        }

        return true;
    }

    bool isSymmetric(TreeNode *root) {
        return checkSameNTree(root, root);
    }

    // 中序遍历
    int kthLargest(TreeNode* root, int k) {
        if (root== nullptr) {
            return -1;
        }
        stack<TreeNode*> myStack;
        TreeNode *curNode = root;
        vector<int> ans;
        while (curNode!= nullptr||!myStack.empty()) {
            if (curNode!= nullptr) {
                myStack.emplace(curNode);
                curNode = curNode->left;
            } else {
                curNode = myStack.top();
                myStack.pop();
                ans.emplace_back(curNode->val);
                curNode = curNode->right;
            }
        }
        return ans[k-1];
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root== nullptr) {
            return false;
        }
        if (root->right== nullptr&&root->left== nullptr) {
            return targetSum == root->val;
        }

        return hasPathSum(root->left, targetSum-root->val) || hasPathSum(root->right, targetSum-root->val);
    }

    int maxDepth(TreeNode* root) {
        if (root== nullptr) {
            return 0;
        }
        queue<TreeNode*> myQueue;
        myQueue.emplace(root);
        int depth = 0;
        while (!myQueue.empty()) {
            int n = myQueue.size();
            for (int i = 0; i < n; ++i) {
                TreeNode* temp = myQueue.front();
                myQueue.pop();
                if (temp->left!= nullptr) {
                    myQueue.emplace(temp->left);
                }
                if (temp->right!= nullptr) {
                    myQueue.emplace(temp->right);
                }
            }
            ++depth;
        }
        return depth;
    }
    int treeHigh(TreeNode* root) {
        if (root== nullptr) {
            return 0;
        }
        return std::max(treeHigh(root->right), treeHigh(root->left))+1;
    }
    // 自顶向下
    bool isBalanced(TreeNode* root) {
        if (root== nullptr) {
            return true;
        }
        return std::abs(treeHigh(root->left)- treeHigh(root->right))<=1 && isBalanced(root->right)&& isBalanced(root->left);
    }

    int sumNums(int n) {
        n&&(n+= sumNums(n-1));
        return n;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

    }

    // 在排序数组中查找元素的第一个和最后一个位置
    vector<int> searchRange(vector<int> nums, int target) {
        int n=nums.size();
        int left = 0, right = n-1;
        int ans_left = -1, ans_right=-1;
        while (left<=right) {
            int mid = left+(right-left)/2;
            if (nums.at(mid) == target) {
                ans_left = mid;
                right = mid-1;
            } else if (nums.at(mid) > target) {
                right = mid-1;
            } else {
                left=mid+1;
            }
        }

        left = 0,right=n-1;
        while (left<=right) {
            int mid=left+(right-left)/2;
            if (nums.at(mid) == target) {
                ans_right=mid;
                left = mid+1;
            } else if(nums.at(mid) > target) {
                right = mid-1;
            } else {
                left=mid+1;
            }
        }

        return {left,right};
    }

    bool hasCycle(ListNode *head) {
        if (head== nullptr||head->next== nullptr){
            return true;
        }
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast!= nullptr&&fast->next!= nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow==fast) {
                return true;
            }
        }
        return false;
    }
    
public:
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

        vector<int> nums = {2,7,11,15};
        vector<int> res = twoSum(nums, 9);
        std::copy(res.begin(),res.end(), std::ostream_iterator<int>(std::cout, " "));

        vector<char> s = {'h', 'e', 'l', 'l', 'o'};
        reverseString(s);
        std::copy(s.begin(), s.end(), std::ostream_iterator<char>(std::cout, " "));

        string s = "pwwkew";
        cout << lengthOfLongestSubstring(s) << endl;
        */
        //cout << checkInclusion("abc", "dcda") << endl;
        vector<vector<int>> image;
        image.push_back(vector<int>{1, 1, 1});
        image.push_back(vector<int>{1, 1, 0});
        image.push_back(vector<int>{1, 0, 1});

        floodFill(image, 1, 1, 2);

    }

private:
    string str;
};

#include <stack>

class CQueue {
public:
    CQueue() {

    }

    void appendTail(int value) {
        inStack.push(value);

    }

    int deleteHead() {
        if (outStack.empty()) {
            if (inStack.empty()) {
                return -1;
            }
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        int value = outStack.top();
        outStack.pop();
        return value;

    }

private:
    stack<int> inStack, outStack;

};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */

class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;
public:
    MinStack() {
        min_stack.push(INT_MAX);
    }

    void push(int x) {
        x_stack.push(x);
        min_stack.push(std::min(min_stack.top(), x));
    }

    void pop() {
        x_stack.pop();
        min_stack.pop();
    }

    int top() {
        return x_stack.top();
    }

    int min() {
        return min_stack.top();
    }
};

#endif //DAILY_PRACTICE_MYALGORITHMS_H
